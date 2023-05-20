/*
	Questions
		it's will handle double "XXXXXXXXX.EXT.EXT"? (NOT)
		it's will handle file without extension? (if so how?)
			1) it will return a empty extension (YES)
			2) it will try open the file and figure out extension (NO)
		the extension will contain . or not?
			1) .extension (NO)
			2) extension (YES)
		Need?
			to avoid memory allocation? (YES)
			to be null termined? (YES)
			to take care if filename or extension is nullptr (NO)
			
*/
void extract_file_extension(const char * filename,char * extension)
{
	char * tmp = (char*)filename;
	
	//goto end of filename
	while(*tmp++ != '\0') {}

	//go back to first occurence of dot (.) or begin of filename
	while(*tmp-- != '.')
	{
		//if tmp is on begin of filename this meaning filename has not extension
		if(filename == tmp)
		{
			extension[0] = '\0';
			return;
		}
	}
	tmp += 2; // skip a char and dot
	
	//copy from filename the extension
	while(*tmp != '\0')
	{
		*extension++ = *tmp++;
	}
	
	*extension = '\0';
}
