#include <stdio.h>
#include "szp.h"
#include <inttypes.h>

int main(int argc, char * argv[])
{

   size_t nbEle;
    char zipFilePath[640], outputFilePath[645];
    if(argc < 4)
    {
		printf("Usage: szp_decompress [srcFilePath] [nbEle] [blockSize] [error bound]\n");
		printf("Example: szp_decompress testfloat_8_8_128.dat.szp 8192 64 1E-3\n");
		exit(0);
	}

    sprintf(zipFilePath, "%s", argv[1]);
    nbEle = strtoimax(argv[2], NULL, 10);
    int blockSize = atoi(argv[3]);
    float errBound = atof(argv[4]);    

    sprintf(outputFilePath, "%s.out", zipFilePath);

    size_t byteLength;
    int status;
    unsigned char *bytes = readByteData(zipFilePath, &byteLength, &status);
    if(status!=SZxp_SCES) // 1 indicates normal
    {
        printf("Error: %s cannot be read!\n", zipFilePath);
        exit(0);
    }

    float *data = szp_decompress_float(nbEle, errBound, blockSize, bytes);

    writeFloatData_inBytes(data, nbEle, outputFilePath, &status);

    if(status!=SZxp_SCES)
    {
        printf("Error: %s cannot be written!\n", outputFilePath);
        exit(0);
    }
    printf("done\n");

    free(bytes);
	free(data);
}
