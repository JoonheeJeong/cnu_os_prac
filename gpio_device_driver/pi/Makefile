TARGETS = simple_blink button_blink button_wp

all : $(TARGETS)

simple_blink : simple_blink.o
	gcc $< -o $@

button_blink : button_blink.o
	gcc $< -o $@

button_wp: button_wp.o
	gcc $< -o $@ -lwiringPi

%.o : %.c
	gcc -c $<

clean:
	rm -rf $(TARGETS) *.o
