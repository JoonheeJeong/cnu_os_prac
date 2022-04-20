outputs = fifo_server fifo_client \
		  sem_pc \
		  pp_server pp_client
		  
all : $(outputs)

clean:
	rm -f $(outputs)

CC = gcc

CFLAGS = -Wall -o
LDFLAGS = -lpthread

fifo_server: fifo_server.c
	$(CC) $< $(CFLAGS) $@ $(LDFLAGS)
fifo_client: fifo_client.c
	$(CC) $< $(CFLAGS) $@ $(LDFLAGS)

sem_pc: sem_pc.c
	$(CC) $< $(CFLAGS) $@ $(LDFLAGS)

pp_server: pp_server.c
	$(CC) $< $(CFLAGS) $@ $(LDFLAGS)
pp_client: pp_client.c
	$(CC) $< $(CFLAGS) $@ $(LDFLAGS)
