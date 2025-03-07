CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = memory-usage/arrays.c
OUT = arrays.out

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)