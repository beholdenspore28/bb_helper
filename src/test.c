#include "stdio.h"
#include "blib_file.h"
#include "blib_math.h"

void fileBufferExample(){
	printf("\n\nBEGIN FILEBUFFER TEST\n\n");
	char* filepath = "testfile";
	blib_fileBuffer_t FILE = blib_fileBuffer_read(filepath);
	if (FILE.error) {
		printf("failed to load file \'%s\'\n", filepath);
	} else {
		printf("\'%s\'", FILE.text);
	}

	blib_fileBuffer_close(FILE);
	printf("\n\nEND FILEBUFFER TEST \n\n");
}

void mathExample(){
	
}

int main () {
	//fileBufferExample();
	mathExample();
}
