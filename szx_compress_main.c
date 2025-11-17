#include <stdio.h>
#include "szx.h"


/*main*/
int main(int argc, char * argv[])
{
    char oriFilePath[640], outputFilePath[645];
    if(argc < 3)
    {
		printf("Usage: szx_compress [srcFilePath] [block size] [err bound]\n");
		printf("Example: szx_compress testfloat_8_8_128.dat 64 1E-3\n");
		exit(0);
    }

    sprintf(oriFilePath, "%s", argv[1]);
    int blockSize = atoi(argv[2]);
    float errBound = atof(argv[3]);

    sprintf(outputFilePath, "%s.szx", oriFilePath);

    int status = 0;
    size_t nbEle;
    float *data = readFloatData(oriFilePath, &nbEle, &status);
    if(status != SZxp_SCES)
    {
		printf("Error: data file %s cannot be read!\n", oriFilePath);
		exit(0);
    }

    size_t outSize;


    unsigned char* bytes = szx_compress_float(data, &outSize, errBound, nbEle, blockSize);
    printf("compression size = %zu, CR = %f\n", outSize, 1.0f*nbEle*sizeof(float)/outSize);
    writeByteData(bytes, outSize, outputFilePath, &status);
    if(status != SZxp_SCES)
    {
        printf("Error: data file %s cannot be written!\n", outputFilePath);
        exit(0);
    }

    printf("done\n");
    free(bytes);
    free(data);

    return 0;    

}
