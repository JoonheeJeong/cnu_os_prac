outputs = practice_01 practice_02 practice_03 \
	  answer_01 answer_02 answer_03

all : $(outputs)

clean:
	rm -f $(outputs)

CC = gcc

CFLAGS = -Wall -g -o

practice_01: practice_01.c
	$(CC) $(CFLAGS) practice_01 practice_01.c

practice_02: practice_02.c
	$(CC) $(CFLAGS) practice_02 practice_02.c

practice_03: practice_03.c
	$(CC) $(CFLAGS) practice_03 practice_03.c

answer_01: answer_01.c
	$(CC) $(CFLAGS) answer_01 answer_01.c

answer_02: answer_02.c
	$(CC) $(CFLAGS) answer_02 answer_02.c

answer_03: answer_03.c
	$(CC) $(CFLAGS) answer_03 answer_03.c
