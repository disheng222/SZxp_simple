#include "szp.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

size_t szp_convertIntArray2ByteArray_fast_1b_args(unsigned char *intArray, size_t intArrayLength, unsigned char *result)
{
	size_t byteLength = 0;
	size_t i, j;
	if (intArrayLength % 8 == 0)
		byteLength = intArrayLength / 8;
	else
		byteLength = intArrayLength / 8 + 1;

	size_t n = 0;
	int tmp, type;
	for (i = 0; i < byteLength; i++)
	{
		tmp = 0;
		for (j = 0; j < 8 && n < intArrayLength; j++)
		{
			type = intArray[n];
			
			tmp = (tmp | (type << (7 - j)));
			n++;
		}
		result[i] = (unsigned char)tmp;
	}
	return byteLength;
}

size_t szp_convertUInt2Byte_fast_1b_args(unsigned int *intArray, size_t intArrayLength, unsigned char *result)
{
	size_t byteLength = 0;
	size_t i, j;
	if (intArrayLength % 8 == 0)
		byteLength = intArrayLength / 8;
	else
		byteLength = intArrayLength / 8 + 1;

	size_t n = 0;
	unsigned int tmp, type;
	for (i = 0; i < byteLength; i++)
	{
		tmp = 0;
		for (j = 0; j < 8 && n < intArrayLength; j++)
		{
			type = intArray[n];
			
			tmp = (tmp | (type << (7 - j)));
			n++;
		}
		result[i] = (unsigned char)tmp;
	}
	return byteLength;
}

size_t szp_convertUInt2Byte_fast_2b_args(unsigned int *timeStepType, size_t timeStepTypeLength, unsigned char *result)
{
	unsigned char tmp = 0;
	size_t i, byteLength = 0;
	if (timeStepTypeLength % 4 == 0)
		byteLength = timeStepTypeLength * 2 / 8;
	else
		byteLength = timeStepTypeLength * 2 / 8 + 1;
	size_t n = 0;
	if (timeStepTypeLength % 4 == 0)
	{
		for (i = 0; i < byteLength; i++)
		{
			tmp = 0;

			tmp |= timeStepType[n++] << 6;
			tmp |= timeStepType[n++] << 4;
			tmp |= timeStepType[n++] << 2;
			tmp |= timeStepType[n++];

			result[i] = tmp;
		}
	}
	else
	{
		size_t byteLength_ = byteLength - 1;
		for (i = 0; i < byteLength_; i++)
		{
			tmp = 0;

			tmp |= timeStepType[n++] << 6;
			tmp |= timeStepType[n++] << 4;
			tmp |= timeStepType[n++] << 2;
			tmp |= timeStepType[n++];

			

			result[i] = tmp;
		}
		tmp = 0;
		int mod4 = timeStepTypeLength % 4;
		for (int j = 0; j < mod4; j++)
		{
			unsigned char type = timeStepType[n++];
			tmp = tmp | type << (6 - (j << 1));
		}
		result[i] = tmp;
	}

	
	return byteLength;
}

size_t szp_convertUInt2Byte_fast_3b_args(unsigned int *timeStepType, size_t timeStepTypeLength, unsigned char *result)
{
	size_t i = 0, k = 0, byteLength = 0, n = 0;
	if (timeStepTypeLength % 8 == 0)
		byteLength = timeStepTypeLength * 3 / 8;
	else
		byteLength = timeStepTypeLength * 3 / 8 + 1;

	unsigned char tmp = 0;
	for (n = 0; n < timeStepTypeLength; n++)
	{
		k = n % 8;
		switch (k)
		{
		case 0:
			tmp = tmp | (timeStepType[n] << 5);
			break;
		case 1:
			tmp = tmp | (timeStepType[n] << 2);
			break;
		case 2:
			tmp = tmp | (timeStepType[n] >> 1);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 7);
			break;
		case 3:
			tmp = tmp | (timeStepType[n] << 4);
			break;
		case 4:
			tmp = tmp | (timeStepType[n] << 1);
			break;
		case 5:
			tmp = tmp | (timeStepType[n] >> 2);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 6);
			break;
		case 6:
			tmp = tmp | (timeStepType[n] << 3);
			break;
		case 7:
			tmp = tmp | (timeStepType[n] << 0);
			(result)[i++] = tmp;
			tmp = 0;
			break;
		}
	}
	if (k != 7) 
		(result)[i] = tmp;

	return byteLength;
}

size_t szp_convertUInt2Byte_fast_4b_args(unsigned int *timeStepType, size_t timeStepTypeLength, unsigned char *result)
{
	size_t i = 0, byteLength = 0, n = 0;
	if (timeStepTypeLength % 2 == 0)
		byteLength = timeStepTypeLength * 4 / 8;
	else
		byteLength = timeStepTypeLength * 4 / 8 + 1;

	for (n = 0; n < timeStepTypeLength;)
	{
		unsigned char tmp = 0;
		for (int j = 0; j < 2 && n < timeStepTypeLength; j++)
		{
			unsigned int type = timeStepType[n];
			if (j == 0)
				tmp = tmp | (type << 4);
			else 
				tmp = tmp | type;
			n++;
		}
		(result)[i++] = tmp;
	}
	return byteLength;
}

size_t szp_convertUInt2Byte_fast_5b_args(unsigned int *timeStepType, size_t timeStepTypeLength, unsigned char *result)
{
	size_t i = 0, k = 0, byteLength = 0, n = 0;
	if (timeStepTypeLength % 8 == 0)
		byteLength = timeStepTypeLength * 5 / 8;
	else
		byteLength = timeStepTypeLength * 5 / 8 + 1;

	unsigned char tmp = 0;
	for (n = 0; n < timeStepTypeLength; n++)
	{
		k = n % 8;
		switch (k)
		{
		case 0:
			tmp = tmp | (timeStepType[n] << 3);
			break;
		case 1:
			tmp = tmp | (timeStepType[n] >> 2);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 6);
			break;
		case 2:
			tmp = tmp | (timeStepType[n] << 1);
			break;
		case 3:
			tmp = tmp | (timeStepType[n] >> 4);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 4);
			break;
		case 4:
			tmp = tmp | (timeStepType[n] >> 1);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 7);
			break;
		case 5:
			tmp = tmp | (timeStepType[n] << 2);
			break;
		case 6:
			tmp = tmp | (timeStepType[n] >> 3);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 5);
			break;
		case 7:
			tmp = tmp | (timeStepType[n] << 0);
			(result)[i++] = tmp;
			tmp = 0;
			break;
		}
	}
	if (k != 7) 
		(result)[i] = tmp;

	return byteLength;
}

size_t szp_convertUInt2Byte_fast_6b_args(unsigned int *timeStepType, size_t timeStepTypeLength, unsigned char *result)
{
	size_t i = 0, k = 0, byteLength = 0, n = 0;
	if (timeStepTypeLength % 8 == 0)
		byteLength = timeStepTypeLength * 6 / 8;
	else
		byteLength = timeStepTypeLength * 6 / 8 + 1;

	unsigned char tmp = 0;
	for (n = 0; n < timeStepTypeLength; n++)
	{
		k = n % 4;
		switch (k)
		{
		case 0:
			tmp = tmp | (timeStepType[n] << 2);
			break;
		case 1:
			tmp = tmp | (timeStepType[n] >> 4);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 4);
			break;
		case 2:
			tmp = tmp | (timeStepType[n] >> 2);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 6);
			break;
		case 3:
			tmp = tmp | (timeStepType[n] << 0);
			(result)[i++] = tmp;
			tmp = 0;
			break;
		}
	}
	if (k != 3) 
		(result)[i] = tmp;

	return byteLength;
}

size_t szp_convertUInt2Byte_fast_7b_args(unsigned int *timeStepType, size_t timeStepTypeLength, unsigned char *result)
{
	size_t i = 0, k = 0, byteLength = 0, n = 0;
	if (timeStepTypeLength % 8 == 0)
		byteLength = timeStepTypeLength * 7 / 8;
	else
		byteLength = timeStepTypeLength * 7 / 8 + 1;

	unsigned char tmp = 0;
	for (n = 0; n < timeStepTypeLength; n++)
	{
		k = n % 8;
		switch (k)
		{
		case 0:
			tmp = tmp | (timeStepType[n] << 1);
			break;
		case 1:
			tmp = tmp | (timeStepType[n] >> 6);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 2);
			break;
		case 2:
			tmp = tmp | (timeStepType[n] >> 5);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 3);
			break;
		case 3:
			tmp = tmp | (timeStepType[n] >> 4);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 4);
			break;
		case 4:
			tmp = tmp | (timeStepType[n] >> 3);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 5);
			break;
		case 5:
			tmp = tmp | (timeStepType[n] >> 2);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 6);
			break;
		case 6:
			tmp = tmp | (timeStepType[n] >> 1);
			(result)[i++] = tmp;
			tmp = 0 | (timeStepType[n] << 7);
			break;
		case 7:
			tmp = tmp | (timeStepType[n] << 0);
			(result)[i++] = tmp;
			tmp = 0;
			break;
		}
	}
	if (k != 7) 
		(result)[i] = tmp;

	return byteLength;
}

size_t szp_save_fixed_length_bits(unsigned int *unsignintArray, size_t intArrayLength, unsigned char *result, unsigned int bit_count)
{

	unsigned int byte_count = 0;
	unsigned int remainder_bit = 0;
	size_t i, j;
	byte_count = bit_count / 8; 
	remainder_bit = bit_count % 8;
	size_t byteLength = 0;
		
	size_t byte_offset = byte_count * intArrayLength;
	if (remainder_bit == 0)
	{
		byteLength = byte_offset;
	}
	else
	{
		byteLength = byte_count * intArrayLength + (remainder_bit * intArrayLength - 1) / 8 + 1;
	}

	size_t n = 0;
	unsigned int tmp;
	i = 0;
	if (byte_count > 0)
	{
		while (n < intArrayLength)
		{
			j = 0;
			tmp = unsignintArray[n];
			tmp >>= remainder_bit;
			while (i < byteLength && j < byte_count)
			{
				result[i] = (unsigned char)tmp;
				i++;
				tmp >>= 8; // right shift by 8 bits to store the next full byte
				j++;
			}
			n++;
		}
	}
	if (remainder_bit > 0)
	{
		if (byte_count > 0)
		{
			for (i = 0; i < intArrayLength; i++)
			{
				unsignintArray[i] <<= (32 - remainder_bit);
				unsignintArray[i] >>= (32 - remainder_bit);
			}
		}
		

		switch (remainder_bit)
		{
		case 1:
			szp_convertUInt2Byte_fast_1b_args(unsignintArray, intArrayLength, result + byte_offset);
			break;
		case 2:
			szp_convertUInt2Byte_fast_2b_args(unsignintArray, intArrayLength, result + byte_offset);
			break;
		case 3:
			szp_convertUInt2Byte_fast_3b_args(unsignintArray, intArrayLength, result + byte_offset);
			break;
		case 4:
			szp_convertUInt2Byte_fast_4b_args(unsignintArray, intArrayLength, result + byte_offset);
			break;
		case 5:
			szp_convertUInt2Byte_fast_5b_args(unsignintArray, intArrayLength, result + byte_offset);
			break;
		case 6:
			szp_convertUInt2Byte_fast_6b_args(unsignintArray, intArrayLength, result + byte_offset);
			break;
		case 7:
			szp_convertUInt2Byte_fast_7b_args(unsignintArray, intArrayLength, result + byte_offset);
			break;
		default:
			printf("Error: try to save %d bits\n", remainder_bit);
		}
	}

	return byteLength;
}


unsigned char *szp_compress_float(float *oriData, size_t *outSize,
                                  float absErrBound, size_t nbEle,
                                  int blockSize) {
	float *op = oriData;
	double inver_bound = 1 / absErrBound; //reciprocal of error bound

	int prior = 0;
	int current = 0;
	int diff = 0;
	unsigned int max = 0;
	unsigned int bit_count = 0;

	*outSize = 0;
	size_t maxPreservedBufferSize =
	  sizeof(float) * nbEle; // assume that the compressed data size would not
							 // exceed the original size
	unsigned char *outputBytes = (unsigned char *)malloc(maxPreservedBufferSize);
	unsigned char *output_pointer = outputBytes;

	//Store the first data point as it is in the dataset
	prior = (op[0]) * inver_bound; 
	memcpy(output_pointer, &prior, sizeof(int));
	output_pointer += sizeof(unsigned int);
	(*outSize) += sizeof(unsigned int);
	
	unsigned char *temp_sign_arr = (unsigned char *)malloc(blockSize * sizeof(unsigned char));
	unsigned int *temp_predict_arr = (unsigned int *)malloc(blockSize * sizeof(unsigned int));	
	unsigned int signbytelength = 0;
	unsigned int savedbitsbytelength = 0;	
	
	size_t i, j;
	for (i = 1; i < nbEle; i = i + blockSize) //block_size = e.g., 64
	{
		size_t current_block_size = (i + blockSize > nbEle) ? (nbEle - i) : blockSize;

		max = 0;
		for (j = 0; j < current_block_size; j++)
		{
			current = (op[i + j]) * inver_bound; //quantization into integer value
			diff = current - prior; //1D 1Layer Lorenzo prediciton
			prior = current;
			if (diff == 0)
			{
				temp_sign_arr[j] = 0;
				temp_predict_arr[j] = 0;
			}	
			else
			{
				if (diff < 0)
				{
					temp_sign_arr[j] = 1;
					temp_predict_arr[j] = -diff;
				}
				else
				{
					temp_sign_arr[j] = 0;
					temp_predict_arr[j] = diff;
				}
				if (max < temp_predict_arr[j])
					max = temp_predict_arr[j];
			}
		}

		if (max == 0) 
		{
			output_pointer[0] = 0;  //constant block
			output_pointer++; //increment 1 byte
			(*outSize) ++; //increment 1 byte
		}
		else
		{
			bit_count = (unsigned int)(log2f(max)) + 1;
			output_pointer[0] = bit_count; //fill data
			
			(*outSize) ++; //increase outputSize
			output_pointer++; //move pointer
			
			signbytelength = szp_convertIntArray2ByteArray_fast_1b_args(temp_sign_arr, current_block_size, output_pointer); 
			
			output_pointer += signbytelength; //move output pointer
			
			(*outSize) += signbytelength; //increase output size
			
			savedbitsbytelength = szp_save_fixed_length_bits(temp_predict_arr, current_block_size, output_pointer, bit_count);
			
			output_pointer += savedbitsbytelength;
			(*outSize) += savedbitsbytelength;
		}
	}
	
	return outputBytes;
}
