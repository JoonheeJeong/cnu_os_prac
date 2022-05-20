#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>

#define LED_R	0
#define BTN_R	23

void blink_led()
{
    char read_data = 0;
    char pre_read_data = 0;
    int event_count = 0;

    while (1) {
	read_data = digitalRead(BTN_R);
	if (pre_read_data == 0 && read_data == 1) {
	    printf("%10d: [BTN_R] PUSH\n", ++event_count);
        } else if (pre_read_data == 1 && read_data == 0) {
	    printf("%10d: [BTN_R] PULL\n", ++event_count);
	}
	pre_read_data = read_data;
	digitalWrite(LED_R, read_data);
	usleep(100000); // delay by 0.1s to prevent duplicate inputs
    }
}

int main()
{
    printf("Read Button and Output to the RED LED (wiringPi Version)\n");

    if (wiringPiSetup() == -1) {
	fprintf(stderr, "Error: Cannot open GPIO Driver\n");
	exit(1);
    }
    pinMode(LED_R, OUTPUT);
    pinMode(BTN_R, INPUT);

    blink_led();

    return 0;
}
