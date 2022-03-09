outputs = answer_01 answer_02 answer_03

all : $(outputs)

clean:
	rm -f $(outputs)

CC = gcc

CFLAGS = -Wall -g -o

answer_01: answer_01.c
	$(CC) $(CFLAGS) answer_01 answer_01.c

answer_02: answer_02.c
	$(CC) $(CFLAGS) answer_02 answer_02.c

answer_03: answer_03.c
	$(CC) $(CFLAGS) answer_03 answer_03.c
