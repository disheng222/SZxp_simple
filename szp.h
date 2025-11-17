#ifndef SZP_H
#define SZP_H

#include "utility.h"

size_t szp_convertIntArray2ByteArray_fast_1b_args(
    unsigned char *intArray,
    size_t intArrayLength,
    unsigned char *result
);

size_t szp_convertUInt2Byte_fast_1b_args(
    unsigned int *intArray,
    size_t intArrayLength,
    unsigned char *result
);

size_t szp_convertUInt2Byte_fast_2b_args(
    unsigned int *timeStepType,
    size_t timeStepTypeLength,
    unsigned char *result
);

size_t szp_convertUInt2Byte_fast_3b_args(
    unsigned int *timeStepType,
    size_t timeStepTypeLength,
    unsigned char *result
);

size_t szp_convertUInt2Byte_fast_4b_args(
    unsigned int *timeStepType,
    size_t timeStepTypeLength,
    unsigned char *result
);

size_t szp_convertUInt2Byte_fast_5b_args(
    unsigned int *timeStepType,
    size_t timeStepTypeLength,
    unsigned char *result
);

size_t szp_convertUInt2Byte_fast_6b_args(
    unsigned int *timeStepType,
    size_t timeStepTypeLength,
    unsigned char *result
);

size_t szp_convertUInt2Byte_fast_7b_args(
    unsigned int *timeStepType,
    size_t timeStepTypeLength,
    unsigned char *result
);

size_t szp_save_fixed_length_bits(
    unsigned int *unsignintArray,
    size_t intArrayLength,
    unsigned char *result,
    unsigned int bit_count
);

unsigned char *szp_compress_float(
    float *oriData,
    size_t *outSize,
    float absErrBound,
    size_t nbEle,
    int blockSize
);

void szp_convertByte2UInt_fast_1b_args(
    size_t intArrayLength,
    unsigned char *byteArray,
    size_t byteArrayLength,
    unsigned int *intArray
);

void szp_convertByte2UInt_fast_2b_args(
    size_t stepLength,
    unsigned char *byteArray,
    size_t byteArrayLength,
    unsigned int *intArray
);

void szp_convertByte2UInt_fast_3b_args(
    size_t stepLength,
    unsigned char *byteArray,
    size_t byteArrayLength,
    unsigned int *intArray
);

void szp_convertByte2UInt_fast_4b_args(
    size_t stepLength,
    unsigned char *byteArray,
    size_t byteArrayLength,
    unsigned int *intArray
);

void szp_convertByte2UInt_fast_5b_args(
    size_t stepLength,
    unsigned char *byteArray,
    size_t byteArrayLength,
    unsigned int *intArray
);

void szp_convertByte2UInt_fast_6b_args(
    size_t stepLength,
    unsigned char *byteArray,
    size_t byteArrayLength,
    unsigned int *intArray
);

void szp_convertByte2UInt_fast_7b_args(
    size_t stepLength,
    unsigned char *byteArray,
    size_t byteArrayLength,
    unsigned int *intArray
);

size_t szp_extract_fixed_length_bits(
    unsigned char *result,
    size_t intArrayLength,
    unsigned int *unsignintArray,
    unsigned int bit_count
);

float *szp_decompress_float(
    size_t nbEle,
    float absErrBound,
    int blockSize,
    unsigned char *cmpBytes
);

#endif /* SZP_H */

