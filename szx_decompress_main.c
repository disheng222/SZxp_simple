#include <stdio.h>
#include "szx.h"
#include <inttypes.h>

int main(int argc, char * argv[])
{

   size_t nbEle;
    char zipFilePath[640], outputFilePath[645];
    if(argc < 2)
    {
		printf("Usage: szx_decompress [srcFilePath] [nbEle]\n");
		printf("Example: szx_decompress testfloat_8_8_128.dat.szx 8192\n");
		exit(0);
	}

    sprintf(zipFilePath, "%s", argv[1]);
    nbEle = strtoimax(argv[2], NULL, 10);

    sprintf(outputFilePath, "%s.out", zipFilePath);

    size_t byteLength;
    int status;
    unsigned char *bytes = readByteData(zipFilePath, &byteLength, &status);
    if(status!=SZxp_SCES)
    {
        printf("Error: %s cannot be read!\n", zipFilePath);
        exit(0);
    }

    float *data = NULL;
    szx_decompress_float(&data, nbEle, bytes);
    writeFloatData_inBytes(data, nbEle, outputFilePath, &status);

    if(status!=SZxp_SCES)
    {
        printf("Error: %s cannot be written!\n", outputFilePath);
        exit(0);
    }
    printf("done\n");

    free(bytes);
}
