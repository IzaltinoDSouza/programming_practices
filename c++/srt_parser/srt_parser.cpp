/*

SRT Specification
	time
		hh:mm:ss,ms
		00:00:00,000
	srt_block
		id
		time
			time_start
			separator	'-->'
			time_end
		text
		.
		empty line
	.
	.
	.
*/

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

static float time_to_ms(int hour,int min,int secs,int ms)
{
	return (hour * 3600000.0f) + (min * 60000.0f) + (secs * 1000.0f) + ms;
}
static float time_to_ms(const char * time_str)
{
	int hour,min,secs,ms;
	
	sscanf(time_str, "%2d:%2d:%2d,%3d", &hour,
										&min,
										&secs,
										&ms);
	
	return (hour * 3600000.0f) + (min * 60000.0f) + (secs * 1000.0f) + ms;
}

struct SrtBlock
{
	size_t id;
	float time_start;
	float time_end;
	std::vector<std::string> text;
	
	void reset()
	{
		id = 0;
		time_start = float{};
		time_end = float{};
		text.clear();
	}
};
enum SrtParserState
{
	ID,
	TIME,
	TEXT,
	EMPTY_LINE
};
class SrtFileFormat
{
public:
	SrtFileFormat(const char * str_filename)
	{
		m_parser_state = SrtParserState::ID;
		
		m_srt_file_ptr = fopen(str_filename,"r");
		if(!m_srt_file_ptr) return;
		
		fseek(m_srt_file_ptr,0,SEEK_END);
		size_t size = ftell(m_srt_file_ptr);
		fseek(m_srt_file_ptr,0,SEEK_SET);
		
		char * buffer = (char *)malloc(size+1);
		char * buffer_begin = buffer;
		if(!buffer) return;
		
		buffer[size] = '\0';
		fread(buffer,size,1,m_srt_file_ptr);
		
		std::string line;
		line.reserve(255);
		
		SrtBlock block;
		while(*buffer != '\0')
		{
			while(*buffer != '\n')
			{
				line.push_back(*buffer);
				buffer++;
			}
			if(line.size() == 0)
				m_parser_state = SrtParserState::EMPTY_LINE;
			else
				line.push_back('\0');
			
			parser_srt(line.c_str(),&block);
			line.clear();
			
			buffer++;
		}
		
		free(buffer_begin);
	}
	auto begin()
	{
		return m_blocks.begin();
	}
	auto end()
	{
		return m_blocks.end();
	}
	auto cbegin() const
	{
		return m_blocks.cbegin();
	}
	auto cend() const
	{
		return m_blocks.cend();
	}
	SrtBlock get_block(float time_ms) const
	{
		for(const auto & block : m_blocks)
		{
			if(time_ms >= block.time_start && time_ms <= block.time_end)
			{
				return block;
			}
		}
		return {};
	}
	SrtBlock get_block(size_t index) const
	{
		return m_blocks[index-1];
	}
	~SrtFileFormat()
	{
		if(m_srt_file_ptr)
			fclose(m_srt_file_ptr);
	}
private:
	std::vector<SrtBlock> m_blocks;
	SrtParserState m_parser_state;
	
	FILE * m_srt_file_ptr;
	
	void parser_srt(const char * line,SrtBlock * block)
	{
		switch(m_parser_state)
		{
			case SrtParserState::ID:
			{
				sscanf(line, "%zu", &block->id);
				m_parser_state = SrtParserState::TIME;				
			}break;
			case SrtParserState::TIME:
			{
				//0..12  time start  "hh:mm:ss,mss"
				//13..16 separator   " --> "
				//17	 time end    "hh:mm:ss,mss"
				
				const char * time_start = &line[0];
				const char * time_end = &line[17];
				
				block->time_start = time_to_ms(time_start);
				block->time_end = time_to_ms(time_end);

				m_parser_state = SrtParserState::TEXT;
			}break;
			case SrtParserState::TEXT:
			{
				block->text.push_back(line);
			}break;
			case SrtParserState::EMPTY_LINE:
			{
				m_parser_state = SrtParserState::ID;
				m_blocks.push_back(*block);
				block->reset();
			}break;
		}
	}
};

int main()
{	
	SrtFileFormat srt = SrtFileFormat("sintel_en.srt");
	for(const SrtBlock & block : srt)
	{
		float delay = block.time_end - block.time_start;
		for(const std::string & text : block.text)
		{
			std::cout << text << '\n';
		}
		usleep(delay * 1000);
	}
}
