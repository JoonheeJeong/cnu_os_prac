outputs = hello_world input_n_print \
		  pipe fifo_read fifo_write \
		  semaphore_01 semaphore_01_ordering \
		  named_sem

all : $(outputs)

clean:
	rm -f $(outputs)

CC = gcc

CFLAGS = -Wall -o
LDFLAGS = -pthread

hello_world: hello_world.c 
	$(CC) $< $(CFLAGS) $@
input_n_print: input_n_print.c
	$(CC) $< $(CFLAGS) $@

pipe: pipe.c
	$(CC) $< $(CFLAGS) $@
fifo_read: fifo_read.c
	$(CC) $< $(CFLAGS) $@
fifo_write: fifo_write.c
	$(CC) $< $(CFLAGS) $@

semaphore_01: semaphore_01.c
	$(CC) $< $(CFLAGS) $@ $(LDFLAGS)
semaphore_01_ordering: semaphore_01_ordering.c
	$(CC) $< $(CFLAGS) $@ $(LDFLAGS)

named_sem: named_sem.c
	$(CC) $< $(CFLAGS) $@ $(LDFLAGS)
