# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I.

# ---- Compression ----
SZX_COMPRESS_SRCS = szx_compress.c utility.c szx_compress_main.c
SZX_COMPRESS_OBJS = $(SZX_COMPRESS_SRCS:.c=.o)
SZX_COMPRESS_BIN = szx_compress

# ---- Decompression ----
SZX_DECOMPRESS_SRCS = szx_decompress.c utility.c szx_decompress_main.c
SZX_DECOMPRESS_OBJS = $(SZX_DECOMPRESS_SRCS:.c=.o)
SZX_DECOMPRESS_BIN = szx_decompress

# ---- Compression ----
SZP_COMPRESS_SRCS = szp_compress.c utility.c szp_compress_main.c
SZP_COMPRESS_OBJS = $(SZP_COMPRESS_SRCS:.c=.o)
SZP_COMPRESS_BIN = szp_compress

# ---- Decompression ----
SZP_DECOMPRESS_SRCS = szp_decompress.c utility.c szp_decompress_main.c
SZP_DECOMPRESS_OBJS = $(SZP_DECOMPRESS_SRCS:.c=.o)
SZP_DECOMPRESS_BIN = szp_decompress

all: $(SZX_COMPRESS_BIN) $(SZX_DECOMPRESS_BIN) $(SZP_COMPRESS_BIN) $(SZP_DECOMPRESS_BIN)

# Build compression binary
$(SZX_COMPRESS_BIN): $(SZX_COMPRESS_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SZX_COMPRESS_OBJS)

# Build decompression binary
$(SZX_DECOMPRESS_BIN): $(SZX_DECOMPRESS_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SZX_DECOMPRESS_OBJS)

# Build compression binary
$(SZP_COMPRESS_BIN): $(SZP_COMPRESS_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SZP_COMPRESS_OBJS) -lm

# Build decompression binary
$(SZP_DECOMPRESS_BIN): $(SZP_DECOMPRESS_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SZP_DECOMPRESS_OBJS) -lm
# Generic rule for compiling .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f *.o $(SZX_COMPRESS_BIN) $(SZX_DECOMPRESS_BIN) $(SZP_COMPRESS_BIN) $(SZP_DECOMPRESS_BIN)
