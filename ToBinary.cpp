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

	build(buf, fp, len);
	/*
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
	*/
	// All done -- return success
	fclose(fp);
	free(buf);
	return 1;
}
static std::vector<char> ReadAllBytes(char const* filename)
{
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();
    std::vector<char>  result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}
int build(char* buf, FILE* fp, long len){
	toBson(buf);
	return 1;
	
	
}
int toBson(char* buf) {
	bson_writer_t *writer;
	bson_t *doc;
	uint8_t *buff = (unsigned char*) buf;
	size_t buflen = 0;
	bool r;
	int i;
	FILE* fp;

	writer = bson_writer_new(&buff, &buflen, 0, bson_realloc_ctx, NULL);

	for(i = 0; i < 10000; i++) {
		r = bson_writer_begin(writer, &doc);
		assert(r);
		
		r = BSON_APPEND_INT32(doc, "i", i);
		assert(r);

		bson_writer_end(writer);
	}
	
	fp=fopen("andri.png", "wb");

	if (!fp)
	{
		free(buf);
		return 0;
	}

	// Write the entire buffer to file
	if (!fwrite(buff,sizeof(uint8_t), 1, fp))
	{
		free(buff);
		fclose(fp);
		return 0;
	}

	bson_free(buff);

	return 0;
}
int main()
{
	copy_file("C:\\Users\\Kevin\\Documents\\Visual Studio 2015\\Projects\\BSON Trial\\BSON Trial\\android.png", "C:\\Users\\Kevin\\Documents\\Visual Studio 2015\\Projects\\BSON Trial\\BSON Trial\\andr.png");
	
	return 1;
}