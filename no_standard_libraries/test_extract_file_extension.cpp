#include <gtest/gtest.h>
#include "extract_file_extension.h"

TEST(extract_file_extension, extract_extension)
{
	const char * filename  = "pixel_art_001.png";
	char extension[8];
	extract_file_extension(filename,extension);
	EXPECT_STREQ(extension,"png");
}

TEST(extract_file_extension, no_extension)
{
	const char * filename  = "virus";
	char extension[8] = {};
	extract_file_extension(filename,extension);
	EXPECT_STREQ(extension,"");
}

TEST(extract_file_extension, empty_filename)
{
	const char * filename  = "";
	char extension[8];
	extract_file_extension(filename,extension);
	EXPECT_STREQ(extension,"");
}

int main(int argc,char ** argv)
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
