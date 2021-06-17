
outputs = simple-race-2 simple-race simple-lock a b c

all : $(outputs)

clean:
	rm -f $(outputs)

CC = gcc

CFLAGS = -Wall -pthread -o

simple-race-2: simple-race-2.c
	$(CC) $(CFLAGS) simple-race-2 simple-race-2.c

simple-race: simple-race.c
	$(CC) $(CFLAGS) simple-race simple-race.c

simple-lock: simple-lock.c
	$(CC) $(CFLAGS) simple-lock simple-lock.c

a: thread_create.c
	$(CC) $(CFLAGS) a thread_create.c 

b: thread_create_with_return_args.c
	$(CC) $(CFLAGS) b thread_create_with_return_args.c 

c: thread_create_simple_args.c
	$(CC) $(CFLAGS) c thread_create_simple_args.c
