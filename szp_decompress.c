#include "szp.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

void szp_convertByteArray2IntArray_fast_1b_args(size_t intArrayLength, unsigned char *byteArray, size_t byteArrayLength, unsigned char *intArray)
{
	size_t n = 0, i;
	unsigned int tmp;
	for (i = 0; i < byteArrayLength - 1; i++)
	{
		tmp = byteArray[i];
		intArray[n++] = (tmp & 0x80) >> 7;
		intArray[n++] = (tmp & 0x40) >> 6;
		intArray[n++] = (tmp & 0x20) >> 5;
		intArray[n++] = (tmp & 0x10) >> 4;
		intArray[n++] = (tmp & 0x08) >> 3;
		intArray[n++] = (tmp & 0x04) >> 2;
		intArray[n++] = (tmp & 0x02) >> 1;
		intArray[n++] = (tmp & 0x01) >> 0;
	}

	tmp = byteArray[i];
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x80) >> 7;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x40) >> 6;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x20) >> 5;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x10) >> 4;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x08) >> 3;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x04) >> 2;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x02) >> 1;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x01) >> 0;
}

void szp_convertByte2UInt_fast_1b_args(size_t intArrayLength, unsigned char *byteArray, size_t byteArrayLength, unsigned int *intArray)
{
	size_t n = 0, i;
	unsigned int tmp;
	for (i = 0; i < byteArrayLength - 1; i++)
	{
		tmp = byteArray[i];
		intArray[n++] = (tmp & 0x80) >> 7;
		intArray[n++] = (tmp & 0x40) >> 6;
		intArray[n++] = (tmp & 0x20) >> 5;
		intArray[n++] = (tmp & 0x10) >> 4;
		intArray[n++] = (tmp & 0x08) >> 3;
		intArray[n++] = (tmp & 0x04) >> 2;
		intArray[n++] = (tmp & 0x02) >> 1;
		intArray[n++] = (tmp & 0x01) >> 0;
	}

	tmp = byteArray[i];
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x80) >> 7;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x40) >> 6;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x20) >> 5;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x10) >> 4;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x08) >> 3;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x04) >> 2;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x02) >> 1;
	if (n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x01) >> 0;
}

void szp_convertByte2UInt_fast_2b_args(size_t stepLength, unsigned char *byteArray, size_t byteArrayLength, unsigned int *intArray)
{

	size_t i, n = 0;

	int mod4 = stepLength % 4;
	if (mod4 == 0)
	{
		for (i = 0; i < byteArrayLength; i++)
		{
			unsigned char tmp = byteArray[i];
			intArray[n++] = (tmp & 0xC0) >> 6;
			intArray[n++] = (tmp & 0x30) >> 4;
			intArray[n++] = (tmp & 0x0C) >> 2;
			intArray[n++] = tmp & 0x03;
		}
	}
	else
	{
		size_t t = byteArrayLength - 1;
		for (i = 0; i < t; i++)
		{
			unsigned char tmp = byteArray[i];
			intArray[n++] = (tmp & 0xC0) >> 6;
			intArray[n++] = (tmp & 0x30) >> 4;
			intArray[n++] = (tmp & 0x0C) >> 2;
			intArray[n++] = tmp & 0x03;
		}
		unsigned char tmp = byteArray[i];
		switch (mod4)
		{
		case 1:
			intArray[n++] = (tmp & 0xC0) >> 6;
			break;
		case 2:
			intArray[n++] = (tmp & 0xC0) >> 6;
			intArray[n++] = (tmp & 0x30) >> 4;
			break;
		case 3:
			intArray[n++] = (tmp & 0xC0) >> 6;
			intArray[n++] = (tmp & 0x30) >> 4;
			intArray[n++] = (tmp & 0x0C) >> 2;
			break;
		}
	}
}

void szp_convertByte2UInt_fast_3b_args(size_t stepLength, unsigned char *byteArray, size_t byteArrayLength, unsigned int *intArray)
{
	size_t i = 0, ii = 0, n = 0;
	unsigned char tmp = byteArray[i];
	for (n = 0; n < stepLength;)
	{
		switch (n % 8)
		{
		case 0:
			intArray[n++] = (tmp & 0xE0) >> 5;
			break;
		case 1:
			intArray[n++] = (tmp & 0x1C) >> 2;
			break;
		case 2:
			ii = (tmp & 0x03) << 1;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0x80) >> 7;
			intArray[n++] = ii;
			break;
		case 3:
			intArray[n++] = (tmp & 0x70) >> 4;
			break;
		case 4:
			intArray[n++] = (tmp & 0x0E) >> 1;
			break;
		case 5:
			ii = (tmp & 0x01) << 2;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xC0) >> 6;
			intArray[n++] = ii;
			break;
		case 6:
			intArray[n++] = (tmp & 0x38) >> 3;
			break;
		case 7:
			intArray[n++] = (tmp & 0x07);
			i++;
			tmp = byteArray[i];
			break;
		}
	}
}

void szp_convertByte2UInt_fast_4b_args(size_t stepLength, unsigned char *byteArray, size_t byteArrayLength, unsigned int *intArray)
{
	size_t i = 0, n = 0;
	unsigned char tmp;
	for (i = 0; i < byteArrayLength; i++)
	{
		tmp = byteArray[i];
		intArray[n++] = (tmp & 0xF0) >> 4;
		if (n == stepLength)
			break;
		intArray[n++] = tmp & 0x0F;
	}
}

void szp_convertByte2UInt_fast_5b_args(size_t stepLength, unsigned char *byteArray, size_t byteArrayLength, unsigned int *intArray)
{
	size_t i = 0, ii = 0, n = 0;
	unsigned char tmp = byteArray[i];
	for (n = 0; n < stepLength;)
	{
		switch (n % 8)
		{
		case 0:
			intArray[n++] = (tmp & 0xF8) >> 3;
			break;
		case 1:
			ii = (tmp & 0x07) << 2;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xC0) >> 6;
			intArray[n++] = ii;
			break;
		case 2:
			intArray[n++] = (tmp & 0x3E) >> 1;
			break;
		case 3:
			ii = (tmp & 0x01) << 4;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xF0) >> 4;
			intArray[n++] = ii;
			break;
		case 4:
			ii = (tmp & 0x0F) << 1;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0x80) >> 7;
			intArray[n++] = ii;
			break;
		case 5:
			intArray[n++] = (tmp & 0x7C) >> 2;
			break;
		case 6:
			ii = (tmp & 0x03) << 3;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xE0) >> 5;
			intArray[n++] = ii;
			break;
		case 7:
			intArray[n++] = (tmp & 0x1F);
			i++;
			tmp = byteArray[i];
			break;
		}
	}
}

void szp_convertByte2UInt_fast_6b_args(size_t stepLength, unsigned char *byteArray, size_t byteArrayLength, unsigned int *intArray)
{
	size_t i = 0, ii = 0, n = 0;
	unsigned char tmp = byteArray[i];
	for (n = 0; n < stepLength;)
	{
		switch (n % 4)
		{
		case 0:
			intArray[n++] = (tmp & 0xFC) >> 2;
			break;
		case 1:
			ii = (tmp & 0x03) << 4;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xF0) >> 4;
			intArray[n++] = ii;
			break;
		case 2:
			ii = (tmp & 0x0F) << 2;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xC0) >> 6;
			intArray[n++] = ii;
			break;
		case 3:
			intArray[n++] = (tmp & 0x3F);
			i++;
			tmp = byteArray[i];
			break;
		}
	}
}

void szp_convertByte2UInt_fast_7b_args(size_t stepLength, unsigned char *byteArray, size_t byteArrayLength, unsigned int *intArray)
{
	size_t i = 0, ii = 0, n = 0;
	unsigned char tmp = byteArray[i];
	for (n = 0; n < stepLength;)
	{
		switch (n % 8)
		{
		case 0:
			intArray[n++] = (tmp & 0xFE) >> 1;
			break;
		case 1:
			ii = (tmp & 0x01) << 6;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xFC) >> 2;
			intArray[n++] = ii;
			break;
		case 2:
			ii = (tmp & 0x03) << 5;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xF8) >> 3;
			intArray[n++] = ii;
			break;
		case 3:
			ii = (tmp & 0x07) << 4;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xF0) >> 4;
			intArray[n++] = ii;
			break;
		case 4:
			ii = (tmp & 0x0F) << 3;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xE0) >> 5;
			intArray[n++] = ii;
			break;
		case 5:
			ii = (tmp & 0x1F) << 2;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0xC0) >> 6;
			intArray[n++] = ii;
			break;
		case 6:
			ii = (tmp & 0x3F) << 1;
			i++;
			tmp = byteArray[i];
			ii |= (tmp & 0x80) >> 7;
			intArray[n++] = ii;
			break;
		case 7:
			intArray[n++] = (tmp & 0x7F);
			i++;
			tmp = byteArray[i];
			break;
		}
	}
}

size_t szp_extract_fixed_length_bits(unsigned char *result, size_t intArrayLength, unsigned int *unsignintArray, unsigned int bit_count)
{
	unsigned int byte_count = 0;
	unsigned int remainder_bit = 0;
	
	size_t i, j;
	byte_count = bit_count / 8; 
	remainder_bit = bit_count % 8;
	size_t byteLength = 0;
	
	
	size_t n = 0;
	unsigned int tmp1, tmp2;
	i = 0;
	size_t byte_offset = byte_count * intArrayLength;

	if (remainder_bit == 0)
	{
		byteLength = byte_offset;
	}
	else
	{
		byteLength = byte_count * intArrayLength + (remainder_bit * intArrayLength - 1) / 8 + 1;
	}

	
	if (remainder_bit > 0)
	{
		switch (remainder_bit)
		{
		case 1:
			szp_convertByte2UInt_fast_1b_args(intArrayLength, result + byte_offset, (intArrayLength - 1) / 8 + 1, unsignintArray);
			break;
		case 2:
			szp_convertByte2UInt_fast_2b_args(intArrayLength, result + byte_offset, (intArrayLength * 2 - 1) / 8 + 1, unsignintArray);
			break;
		case 3:
			szp_convertByte2UInt_fast_3b_args(intArrayLength, result + byte_offset, (intArrayLength * 3 - 1) / 8 + 1, unsignintArray);
			break;
		case 4:
			szp_convertByte2UInt_fast_4b_args(intArrayLength, result + byte_offset, (intArrayLength * 4 - 1) / 8 + 1, unsignintArray);
			break;
		case 5:
			szp_convertByte2UInt_fast_5b_args(intArrayLength, result + byte_offset, (intArrayLength * 5 - 1) / 8 + 1, unsignintArray);
			break;
		case 6:
			szp_convertByte2UInt_fast_6b_args(intArrayLength, result + byte_offset, (intArrayLength * 6 - 1) / 8 + 1, unsignintArray);
			break;
		case 7:
			szp_convertByte2UInt_fast_7b_args(intArrayLength, result + byte_offset, (intArrayLength * 7 - 1) / 8 + 1, unsignintArray);
			break;
		default:
			printf("Error: try to extract %d bits\n", remainder_bit);
		}
	}
	if (byte_count > 0)
	{
		if(remainder_bit == 0)
		{
			memset(unsignintArray, 0 , intArrayLength * sizeof(unsigned int));
		}
		while (i < intArrayLength)
		{
			j = 0;
			tmp1 = 0;
			tmp2 = 0;
			while (j < byte_count && n < byteLength)
			{
				tmp1 = result[n];
				tmp1 <<= (8 * j);
				tmp2 = (tmp2 | tmp1);
				n++;
				j++;
			}
			tmp2 <<= remainder_bit; 
			unsignintArray[i] = (unsignintArray[i] | tmp2);
			i++;
		}
	}

	return byteLength;
}

float *szp_decompress_float(size_t nbEle, float absErrBound, int blockSize, unsigned char *cmpBytes)
{
    float *newData = (float *)malloc(sizeof(float) * nbEle);
	float *newData_pointer = newData;

	size_t i = 0;
	size_t j = 0;

	int prior = 0;
	int current = 0;
	int diff = 0;

	unsigned int bit_count = 0;
	unsigned char *inputBytes_pointer = cmpBytes;

	float ori_prior = 0.0;
	float ori_current = 0.0;

	memcpy(&prior, inputBytes_pointer, sizeof(int));
	inputBytes_pointer += sizeof(unsigned int);

	ori_prior = (float)prior * absErrBound;
	memcpy(newData, &ori_prior, sizeof(float)); 
	newData_pointer += 1;
	
	unsigned char *temp_sign_arr = (unsigned char *)malloc(blockSize * sizeof(unsigned char));
	unsigned int *temp_predict_arr = (unsigned int *)malloc(blockSize * sizeof(unsigned int));
	unsigned int savedbitsbytelength = 0;
	
	for (i = 1; i < nbEle; i = i + blockSize)
	{
		size_t current_block_size = (i + blockSize > nbEle) ? (nbEle - i) : blockSize;

		bit_count = inputBytes_pointer[0];
		inputBytes_pointer++;
		
		if (bit_count == 0)
		{
			ori_prior = (float)prior * absErrBound;
			
			for (j = 0; j < current_block_size; j++)
			{
				memcpy(newData_pointer, &ori_prior, sizeof(float));
				newData_pointer++;
			}
		}
		else
		{
			szp_convertByteArray2IntArray_fast_1b_args(current_block_size, inputBytes_pointer, (current_block_size - 1) / 8 + 1, temp_sign_arr);
			inputBytes_pointer += ((current_block_size - 1) / 8 + 1);

			savedbitsbytelength = szp_extract_fixed_length_bits(inputBytes_pointer, current_block_size, temp_predict_arr, bit_count);
			inputBytes_pointer += savedbitsbytelength;
			for (j = 0; j < current_block_size; j++)
			{
				if (temp_sign_arr[j] == 0)
				{
					diff = temp_predict_arr[j];
				}
				else
				{
					diff = 0 - temp_predict_arr[j];
				}
				current = prior + diff;
				ori_current = (float)current * absErrBound;
				prior = current;
				memcpy(newData_pointer, &ori_current, sizeof(float));
				newData_pointer++;
			}
		}
	}
	free(temp_predict_arr);
	free(temp_sign_arr);
	return newData;
}

