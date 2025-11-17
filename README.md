# SZxp_simple
Simple version for SZx and SZp

It should have the same compression ratio with SZx (https://github.com/szcompressor/SZx) and SZp (https://github.com/szcompressor/SZp)
It supports only float data type. 
The key compression and decompression codes for SZx are in szx_compress.c and szx_decompress.c, respectively. 
The key compression and decompression codes for SZp are in szp_compress.c and szp_decompress.c, respectively. 


#Quick start

Build the project using 'make'. 

For SZx: 

Then, run szx_compress and szx_decompress to test the codes using the example data file testfloat_8_8_128.dat. 

szx_compress testfloat_8_8_128.dat 64 1E-3
szx_decompress testfloat_8_8_128.dat.szx 8192



For SZp: 

Then, run szp_compress and szp_decompress to test the codes using the example data file testfloat_8_8_128.dat. 

szp_compress testfloat_8_8_128.dat 64 1E-3
szp_decompress testfloat_8_8_128.dat.szp 8192 64 1E-3




