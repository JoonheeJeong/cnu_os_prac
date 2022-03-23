TARGET= simple_calculator
OBJECTS = main.o add.o sub.o mul.o div.o
CC = gcc
CFLAGS = -Wall
LDFLAGS = -Wall

all : $(TARGET)

ifeq (0,1)
main.o : main.c calc_func.h
	$(CC) $(CFLAGS) -c main.c
add.o  : add.c calc_func.h
	$(CC) $(CFLAGS) -c add.c
sub.o  : sub.c calc_func.h
	$(CC) $(CFLAGS) -c sub.c
mul.o  : mul.c calc_func.h
	$(CC) $(CFLAGS) -c mul.c
div.o  : div.c calc_func.h
	$(CC) $(CFLAGS) -c div.c
endif

%.o : %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)
	
clean :
	rm -f $(OBJECTS) $(TARGET)

