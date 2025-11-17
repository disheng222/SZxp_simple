#include <stdio.h>
#include <string.h>
#include "szx.h"

inline long bytesToLong_bigEndian(unsigned char* b) {
	long temp = 0;
	long res = 0;

	res <<= 8;
	temp = b[0] & 0xff;
	res |= temp;

	res <<= 8;
	temp = b[1] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[2] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[3] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[4] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[5] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[6] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[7] & 0xff;
	res |= temp;						
	
	return res;
}

inline size_t bytesToSize(unsigned char* bytes)
{
	size_t result = bytesToLong_bigEndian(bytes);//8	
	return result;
}

inline float bytesToFloat(unsigned char* bytes)
{
	lfloat buf;
	memcpy(buf.byte, bytes, 4);
	return buf.value;
}

void convertByteArray2IntArray_fast_2b(size_t stepLength, unsigned char* byteArray, size_t byteArrayLength, unsigned char **intArray)
{
	if(stepLength > byteArrayLength*4)
	{
		printf("Error: stepLength > byteArray.length*4\n");
		printf("stepLength=%zu, byteArray.length=%zu\n", stepLength, byteArrayLength);
		exit(0);
	}
	if(stepLength>0)
		*intArray = (unsigned char*)malloc(stepLength*sizeof(unsigned char));
	else
		*intArray = NULL;
	size_t i, n = 0;

	int mod4 = stepLength%4;
	if(mod4==0)
	{
		for (i = 0; i < byteArrayLength; i++) {
			unsigned char tmp = byteArray[i];
			(*intArray)[n++] = (tmp & 0xC0) >> 6;
			(*intArray)[n++] = (tmp & 0x30) >> 4;
			(*intArray)[n++] = (tmp & 0x0C) >> 2;
			(*intArray)[n++] = tmp & 0x03;
		}	
	}
	else
	{
		size_t t = byteArrayLength - mod4;
		for (i = 0; i < t; i++) {
			unsigned char tmp = byteArray[i];
			(*intArray)[n++] = (tmp & 0xC0) >> 6;
			(*intArray)[n++] = (tmp & 0x30) >> 4;
			(*intArray)[n++] = (tmp & 0x0C) >> 2;
			(*intArray)[n++] = tmp & 0x03;
		}
		unsigned char tmp = byteArray[i];				
		switch(mod4)
		{
		case 1:
			(*intArray)[n++] = (tmp & 0xC0) >> 6;
			break;
		case 2:
			(*intArray)[n++] = (tmp & 0xC0) >> 6;
			(*intArray)[n++] = (tmp & 0x30) >> 4;			
			break;
		case 3:	
			(*intArray)[n++] = (tmp & 0xC0) >> 6;
			(*intArray)[n++] = (tmp & 0x30) >> 4;
			(*intArray)[n++] = (tmp & 0x0C) >> 2;		
			break;
		}
	}
}

void convertByteArray2IntArray_fast_1b_args(size_t intArrayLength, unsigned char* byteArray, size_t byteArrayLength, unsigned char* intArray)
{   
	size_t n = 0, i;
	int tmp;
	for (i = 0; i < byteArrayLength-1; i++) 
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
	if(n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x80) >> 7;
	if(n == intArrayLength)
		return;	
	intArray[n++] = (tmp & 0x40) >> 6;
	if(n == intArrayLength)
		return;	
	intArray[n++] = (tmp & 0x20) >> 5;
	if(n == intArrayLength)
		return;
	intArray[n++] = (tmp & 0x10) >> 4;
	if(n == intArrayLength)
		return;	
	intArray[n++] = (tmp & 0x08) >> 3;
	if(n == intArrayLength)
		return;	
	intArray[n++] = (tmp & 0x04) >> 2;
	if(n == intArrayLength)
		return;	
	intArray[n++] = (tmp & 0x02) >> 1;
	if(n == intArrayLength)
		return;	
	intArray[n++] = (tmp & 0x01) >> 0;	
}

int szx_decompress_one_block_float(float* newData, size_t blockSize, unsigned char* cmpBytes)
{
	int cmpSize = 0;
	size_t nbEle = blockSize;
	
	register float medianValue;
	size_t leadNumArray_size = nbEle%4==0?nbEle/4:nbEle/4+1;
	
	size_t k = 0;
	int reqLength = (int)cmpBytes[k];
	k++;
	medianValue = bytesToFloat(&(cmpBytes[k]));
	k+=sizeof(float);
	
	unsigned char* leadNumArray = &(cmpBytes[k]);
	k += leadNumArray_size;
	unsigned char* residualMidBytes = &(cmpBytes[k]);	
	unsigned char* q = residualMidBytes;
		
	cmpSize = k;	
		
	size_t i = 0, j = 0;
	k = 0;
	
	register lfloat lfBuf_pre;
	register lfloat lfBuf_cur;
	
	lfBuf_pre.ivalue = 0;

	int reqBytesLength, resiBitsLength; 
	register unsigned char leadingNum;

	reqBytesLength = reqLength/8;
	resiBitsLength = reqLength%8;
	int rightShiftBits = 0;
	
	if(resiBitsLength!=0)
	{
		rightShiftBits = 8 - resiBitsLength;
		reqBytesLength ++;
	}
	
    if(reqBytesLength == 3)
    {
        for(i=0;i < nbEle;i++)
        {
            lfBuf_cur.value = 0;
            
            j = (i >> 2); //i/4
            k = (i & 0x03) << 1; //(i%4)*2
            leadingNum = (leadNumArray[j] >> (6 - k)) & 0x03;
            
            if(leadingNum == 1)
            {	
                lfBuf_cur.byte[3] = lfBuf_pre.byte[3];
                lfBuf_cur.byte[1] = q[0];
                lfBuf_cur.byte[2] = q[1];				
                q += 2;
            }
            else if(leadingNum == 2)
            {
                lfBuf_cur.byte[2] = lfBuf_pre.byte[2];
                lfBuf_cur.byte[3] = lfBuf_pre.byte[3];
                lfBuf_cur.byte[1] = q[0];									
                q += 1;
            }
            else if(leadingNum == 3)
            {
                lfBuf_cur.byte[1] = lfBuf_pre.byte[1];
                lfBuf_cur.byte[2] = lfBuf_pre.byte[2];
                lfBuf_cur.byte[3] = lfBuf_pre.byte[3];				
            }
            else //==0
            {
                lfBuf_cur.byte[1] = q[0];
                lfBuf_cur.byte[2] = q[1];					
                lfBuf_cur.byte[3] = q[2];					
                q += 3;
            }

            lfBuf_cur.ivalue = lfBuf_cur.ivalue << rightShiftBits;
            newData[i] = lfBuf_cur.value + medianValue;
            lfBuf_cur.ivalue = lfBuf_cur.ivalue >> rightShiftBits;
            
            lfBuf_pre = lfBuf_cur;
        }
    }
    else if(reqBytesLength == 2)
    {
        for(i=0;i < nbEle;i++)
        {
            lfBuf_cur.value = 0;
            
            j = (i >> 2); //i/4
            k = (i & 0x03) << 1; //(i%4)*2
            leadingNum = (leadNumArray[j] >> (6 - k)) & 0x03;

            if(leadingNum == 1)
            {	
                lfBuf_cur.byte[3] = lfBuf_pre.byte[3];
                lfBuf_cur.byte[2] = q[0];			
                q += 1;	
            }
            else if(leadingNum >= 2)
            {
                lfBuf_cur.byte[2] = lfBuf_pre.byte[2];
                lfBuf_cur.byte[3] = lfBuf_pre.byte[3];									
            }
            else //==0
            {
                lfBuf_cur.byte[2] = q[0];					
                lfBuf_cur.byte[3] = q[1];					
                q += 2;
            }
            
            lfBuf_cur.ivalue = lfBuf_cur.ivalue << rightShiftBits;
            newData[i] = lfBuf_cur.value + medianValue;
            lfBuf_cur.ivalue = lfBuf_cur.ivalue >> rightShiftBits;
            
            lfBuf_pre = lfBuf_cur;
        }					
    }
    else if(reqBytesLength == 1)
    {
        for(i=0;i < nbEle;i++)
        {
            lfBuf_cur.value = 0;
            
            j = (i >> 2); //i/4
            k = (i & 0x03) << 1; //(i%4)*2
            leadingNum = (leadNumArray[j] >> (6 - k)) & 0x03;
            
            if(leadingNum != 0) //>=1
            {	
                lfBuf_cur.byte[3] = lfBuf_pre.byte[3];				
            }
            else //==0
            {
                lfBuf_cur.byte[3] = q[0];				
                q += 1;	
            }
            
            lfBuf_cur.ivalue = lfBuf_cur.ivalue << rightShiftBits;
            newData[i] = lfBuf_cur.value + medianValue;
            lfBuf_cur.ivalue = lfBuf_cur.ivalue >> rightShiftBits;
            
            lfBuf_pre = lfBuf_cur;
        }				
    }
    else //reqBytesLength == 4
    {
        for(i=0;i < nbEle;i++)
        {
            lfBuf_cur.value = 0;
            
            j = (i >> 2); //i/4
            k = (i & 0x03) << 1; //(i%4)*2
            leadingNum = (leadNumArray[j] >> (6 - k)) & 0x03;
            
            if(leadingNum == 1)
            {	
                lfBuf_cur.byte[0] = q[0];
                lfBuf_cur.byte[1] = q[1];
                lfBuf_cur.byte[2] = q[2];				
                lfBuf_cur.byte[3] = lfBuf_pre.byte[3];					
                q += 3;
            }
            else if(leadingNum == 2)
            {
                lfBuf_cur.byte[0] = q[0];									
                lfBuf_cur.byte[1] = q[1];									
                lfBuf_cur.byte[2] = lfBuf_pre.byte[2];
                lfBuf_cur.byte[3] = lfBuf_pre.byte[3];					
                q += 2;
            }
            else if(leadingNum == 3)
            {
                lfBuf_cur.byte[0] = q[0];									
                lfBuf_cur.byte[1] = lfBuf_pre.byte[1];
                lfBuf_cur.byte[2] = lfBuf_pre.byte[2];
                lfBuf_cur.byte[3] = lfBuf_pre.byte[3];	
                q += 1;				
            }
            else //==0
            {
                lfBuf_cur.byte[0] = q[0];
                lfBuf_cur.byte[1] = q[1];
                lfBuf_cur.byte[2] = q[2];					
                lfBuf_cur.byte[3] = q[3];					
                q += 4;
            }

            lfBuf_cur.ivalue = lfBuf_cur.ivalue << rightShiftBits;
            newData[i] = lfBuf_cur.value + medianValue;
            lfBuf_cur.ivalue = lfBuf_cur.ivalue >> rightShiftBits;
            
            lfBuf_pre = lfBuf_cur;			
        }
    }
	
	cmpSize += (q - residualMidBytes); //add the number of residualMidBytes
	return cmpSize;
}

void szx_decompress_float(float** newData, size_t nbEle, unsigned char* cmpBytes)
{
	*newData = (float*)malloc(sizeof(float)*nbEle);
	
	unsigned char* r = cmpBytes;
	r+=4; //skip version information
    int blockSize = bytesToLong_bigEndian(r);  //get block size
    r += sizeof(size_t);
	size_t nbConstantBlocks = bytesToLong_bigEndian(r); //get number of constant blocks
	r += sizeof(size_t);
		
	size_t nbBlocks = nbEle/blockSize;
	size_t remainCount = nbEle%blockSize;
	size_t stateNBBytes = remainCount == 0 ? (nbBlocks%8==0?nbBlocks/8:nbBlocks/8+1) : ((nbBlocks+1)%8==0? (nbBlocks+1)/8:(nbBlocks+1)/8+1);
	size_t actualNBBlocks = remainCount==0 ? nbBlocks : nbBlocks+1;
	
	size_t nbNonConstantBlocks = actualNBBlocks - nbConstantBlocks;
	

	unsigned char* stateArray = (unsigned char*)malloc(actualNBBlocks);
	float* constantMedianArray = (float*)malloc(nbConstantBlocks*sizeof(float));

    int16_t* O = (int16_t*) r;
    unsigned char* R = r+ nbNonConstantBlocks*sizeof(uint16_t); //block-size information

    convertByteArray2IntArray_fast_1b_args(actualNBBlocks, R, stateNBBytes, stateArray); //get the stateArray
	
	unsigned char* p = R + stateNBBytes; //p is the starting address of constant median values.
	
	size_t i = 0, j = 0, k = 0; //k is used to keep track of constant block index
	for(i = 0;i < nbConstantBlocks;i++, j+=4) //get the median values for constant-value blocks
		constantMedianArray[i] = bytesToFloat(p+j);

	unsigned char* q = p + sizeof(float)*nbConstantBlocks; //q is the starting address of the non-constant data blocks
	float* op = *newData;

	size_t nonConstantBlockID=0;
	for(i=0;i<nbBlocks;i++, op += blockSize)
	{
		unsigned char state = stateArray[i];
		if(state) //non-constant block
		{
            szx_decompress_one_block_float(op, blockSize, q);
            q += O[nonConstantBlockID];
            nonConstantBlockID++;
		}
		else //constant block
		{
			float medianValue = constantMedianArray[k];			
			for(j=0;j<blockSize;j++)
				op[j] = medianValue;
			p += sizeof(float);
			k ++;
		}
	}

	if(remainCount)
	{
		unsigned char state = stateArray[i];
		if(state) //non-constant block
		{
			szx_decompress_one_block_float(op, remainCount, q);	
		}
		else //constant block
		{
			float medianValue = constantMedianArray[k];				
			for(j=0;j<remainCount;j++)
				op[j] = medianValue;
		}		
	}
	
	free(stateArray);
	free(constantMedianArray);
}
