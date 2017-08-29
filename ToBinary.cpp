// ToBinary.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_DEPRECATE
#include "stdafx.h"



int copy_file(const char* srcfilename, const char* dstfilename)
{
	long  len;
	char* buf = NULL;
	FILE* fp = NULL;

	// Open the source file
	#pragma warning(disable:4996)
	fp = fopen(srcfilename, "rb");
	if (!fp) return 0;

	// Get its length (in bytes)
	if (fseek(fp, 0, SEEK_END) != 0)  // This should typically succeed
	{                                 // (beware the 2Gb limitation, though)
		fclose(fp);
		return 0;
	}

	len = ftell(fp);
	rewind(fp);

	// Get a buffer big enough to hold it entirely
	buf = (char*)malloc(len);
	if (!buf)
	{
		fclose(fp);
		return 0;
	}

	// Read the entire file into the buffer
	if (!fread(buf, len, 1, fp))
	{
		free(buf);
		fclose(fp);
		return 0;
	}

	fclose(fp);

	// Open the destination file
	#pragma warning(disable:4996)
	fp = fopen(dstfilename, "wb");
	if (!fp)
	{
		free(buf);
		return 0;
	}

	// Write the entire buffer to file
	if (!fwrite(buf, len, 1, fp))
	{
		free(buf);
		fclose(fp);
		return 0;
	}

	// All done -- return success
	fclose(fp);
	free(buf);
	return 1;
}
static std::vector<char> ReadAllBytes(char const* filename)
{
    std::ifstream ifs(filename, ios::binary|ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}
int build(std::vector<std::string> dataTypes, std::vector<std::string> values,const char* dstfilename){
	for (int i = 0; i<dataTypes.size(); i++) {

	}
	std::vector<char> imgArray = ReadAllBytes(dstfilename);
	
	
	
	
}
int main()
{
	copy_file("C:\\Users\\Kevin\\Documents\\Visual Studio 2015\\Projects\\BSON Trial\\BSON Trial\\android.png", "C:\\Users\\Kevin\\Documents\\Visual Studio 2015\\Projects\\BSON Trial\\BSON Trial\\andr.png");
	/**
	auto builder = bsoncxx::builder::stream::document{};
	bsoncxx::document::value doc_value = builder
	  << "Image" << "FILEHERE"
	  << "DateTime" << "CURRENT TIME HERE"
	  << "Type" << 1
	  << "SomethingExtra << EXTRAHERE
	  << bsoncxx::builder::stream::close_document
	  << bsoncxx::builder::stream::finalize;
	**/
	return 1;
}