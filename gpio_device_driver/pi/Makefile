TARGETS = simple_blink button_blink

all : $(TARGETS)

simple_blink : simple_blink.o
	gcc -o simple_blink simple_blink.o

button_blink : button_blink.o
	gcc -o button_blink button_blink.o

%.o : %.c
	gcc -c $<

clean:
	rm -rf $(TARGETS) *.o
