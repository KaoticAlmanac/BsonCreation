#include <iostream>
#include <assert.h>
#include <cstring>

// ToBinary.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

int toBsonArray(std::vector<char> binary){
    bson_t doc;
    bson_t arr;

    bson_init(&doc);

    std::string binHolder;
    binHolder=std::string(binary.begin(),binary.end());
    char *cop = new char[binary.size()*binary.size()];
    strcpy(cop,binHolder.data());

    //bson_string_t* turnIn;
    //turnIn = bson_string_new(NULL);



    bson_append_utf8(&doc,"Image",-1, binHolder.data(),-1);

    FILE* fp;
    char* buf;
    buf=(char*)bson_get_data(&doc);

    std::cout << "wrote BSON";
    fp = fopen("andri.bson", "wb");

    if (!fp) {
        free(buf);
        return 0;
    }

    // Write the entire buffer to file
    if (!fwrite(buf, sizeof(uint8_t), 1, fp)) {
        free(buf);
        fclose(fp);
        return 0;
    }
    std::cout << "saved bson";
    bson_free(buf);


    return 0;

}


int ToBSON(std::vector<char> binary) {
    bson_writer_t *write;
    bson_t doc;
    bson_init(&doc);
    bool r;

    FILE *fp;
    std::string filePath;
    filePath = "andri.bson";
    const char *img = "Image";
    bson_subtype_t type = bson_subtype_t::BSON_SUBTYPE_BINARY;

    int i;
    uint8_t *buf = (uint8_t *) malloc(binary.size()*binary.size());

    size_t len = 0;
    len = binary.size();

    write = bson_writer_new(&buf, &len, 0, bson_realloc_ctx, NULL);
    //bson_writer_begin(write, &doc);

    for (i = 0; i < binary.size(); i++) {
        uint8_t *bin;
        char *step;
        step = (char *) binary[i];
        bin = reinterpret_cast<uint8_t *>(step);


        //r=bson_append_binary(&doc, img, -1, type, bin, len);
        r=BSON_APPEND_BINARY(&doc,img,type,bin,len);

        assert(r);

    }
    //bson_writer_end(write);

    std::cout << "wrote BSON";
    fp = fopen("andri.bson", "wb");

    if (!fp) {
        free(buf);
        return 0;
    }

    // Write the entire buffer to file
    if (!fwrite(buf, sizeof(uint8_t), 1, fp)) {
        free(buf);
        fclose(fp);
        return 0;
    }
    std::cout << "saved bson";
    bson_free(buf);
    bson_writer_destroy(write);
}

int toBson(uint8_t *buf, long len) {
    std::cout << "ToBson";
    bson_writer_t *writer;
    bson_t *doc;
    //uint8_t *buff = (unsigned char *) buf;
    uint8_t *buff;
    buff=(uint8_t*)malloc(len);
    size_t buflen = 0;
    bool r;
    int i;
    FILE *fp;
    buflen = len;
    std::cout << "Initialized BSON";
    writer = bson_writer_new(&buff, &buflen, 0, bson_realloc_ctx, NULL);
    for (i = 0; i < len; i++) {
        r = bson_writer_begin(writer, &doc);
        assert(r);


        //r = BSON_APPEND_INT32(doc, "i", i);
        //assert(r);

        r=bson_append_utf8(doc,"Image",-1,(char*)buf,len);
        assert(r);

        //r=bson_append_binary(doc,"Image",-1,bson_subtype_t::BSON_SUBTYPE_BINARY,buff,buflen);
        //assert(r);
        bson_writer_end(writer);
    }
    std::cout << "wrote BSON";
    fp = fopen("andri.bson", "wb");

    if (!fp) {
        free(buf);
        return 0;
    }

    // Write the entire buffer to file
    if (!fwrite(buff, sizeof(uint8_t), 1, fp)) {
        free(buff);
        fclose(fp);
        return 0;
    }
    std::cout << "saved bson";
    bson_free(buff);


    return 0;
}

int build(uint8_t *buf, long len) {
    toBson(buf, len);
    return 1;
    /**uint8_t* buff=NULL;
    buff=(uint8_t*)buf;
    std::cout << "Sent Buffer";
    bson_t doc;

    bson_init(&doc);
    std::cout << "Initialized Document";

    if(bson_append_binary(&doc,"Image",-1,(bson_subtype_t)0x80,buff,len)){
        FILE* file;
        file=fopen("willThisWork.png","wb");
        std::cout << "Created destination file";
        fwrite(bson_get_data(&doc),1,doc.len,stdout);
        std::cout << "Wrote file";
    }
    buff=NULL;
    bson_destroy(&doc);*/

}

int copy_file(const char *srcfilename, const char *dstfilename) {
    long len;
    uint8_t *buf = NULL;
    FILE *fp = NULL;

    std::cout << "Initialized files";

    // Open the source file
    //#pragma warning(disable:4996)
    fp = fopen(srcfilename, "rb");
    if (!fp) {
        perror("fopen");
        return 0;
    }

    // Get its length (in bytes)
    if (fseek(fp, 0, SEEK_END) != 0)  // This should typically succeed
    {                                 // (beware the 2Gb limitation, though)
        fclose(fp);
        return 0;
    }
    std::cout << "Open file";
    len = ftell(fp);
    rewind(fp);

    // Get a buffer big enough to hold it entirely
    buf = (uint8_t *) malloc(len);
    if (!buf) {
        fclose(fp);
        return 0;
    }

    // Read the entire file into the buffer
    if (!fread(buf, len, 1, fp)) {
        free(buf);
        fclose(fp);
        return 0;
    }
    std::cout << "Got buffer";
    fclose(fp);

    build(buf, len);
    free(buf);
    return 1;
}

static std::vector<char> ReadAllBytes(char const *filename) {
    std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

/**    std::filebuf* pubf = ifs.rdbuf();
    std::size_t size =pubf->pubseekoff(0,ifs.end,ifs.in);
    b=new uint8_t[size];
    pubf->sgetn((char*)b,size);
**/
    ifs.close();
    return result;
}

int main() {
    std::cout << "start";
    copy_file("../Android_robot.png", "andr.png");
    //toBson(reinterpret_cast<char*>(ReadAllBytes("../Android_robot.png").data()));

///////////////////////////////////
    //std::vector<char> res;
    //res = ReadAllBytes("../Android_robot.png");
    //toBsonArray(res);
    //res.clear(); //works
    //////////////////////////////////



    //char *send = new char[res.size()];//size=14k+
    //send= reinterpret_cast<char*>(res.data());
    //unsigned long hip = res.size();
    //std::copy(res.begin(), res.end(), send);
    //toBson(send,res.size());
    //ToBSON(res);




    return 1;
}
