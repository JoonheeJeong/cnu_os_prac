TARGETS = simple_blink button_blink button_wp multibutton_blink agility_game

all : $(TARGETS)

simple_blink : simple_blink.o
	gcc $< -o $@

button_blink : button_blink.o
	gcc $< -o $@

button_wp: button_wp.o
	gcc $< -o $@ -lwiringPi

multibutton_blink : multibutton_blink.o
	gcc $< -o $@

agility_game : agility_game.o
	gcc $< -o $@

%.o : %.c
	gcc -c $<

clean:
	rm -rf $(TARGETS) *.o
