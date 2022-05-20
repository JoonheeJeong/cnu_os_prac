#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/kdev_t.h>
#include "gpio_device_driver.h"
#include <time.h>

#define END_STAGE   5
#define END_FAIL    3

enum LED {
    R = 1,
    G = 2,
    W = 4,
    Y = 8
};

enum STAGE_RESULT {
    NEED_TEST	= 0,
    SUCCESS	= 1,	    
    FAILURE	= 2,
    SURRENDER	= 3
};

const char CHAR_LED[] = { '*', 'R', 'G', '*', 'W', '*', '*', '*', 'Y' };

int output(int fd, char write_data) { return write(fd, &write_data, 1); }

void start_game(int fd)
{
    srand(time(NULL));

    for (int i = 0; i < 3; ++i) {
	output(fd, R);
	usleep(200000);
	output(fd, G);
	usleep(200000);
	output(fd, W);
	usleep(200000);
    }
    output(fd, 0);
    usleep(200000);
}

void succeed_all(int fd) { 
    start_game(fd); 
    puts("Succeed all the stages!");
}

void print_stage_problem(int stage, int problem_set[])
{
    printf("  Stage %d's problem: ", stage);
    printf("%c", CHAR_LED[problem_set[0]]);
    for (int i = 1; i < stage; ++i)
	printf("-%c", CHAR_LED[problem_set[i]]);
    puts("");
}

void print_stage(int stage, int problem_set[], int solution_set[])
{
    print_stage_problem(stage, problem_set);
    printf("        Your answer: ");
    printf("%c", CHAR_LED[solution_set[0]]);
    for (int i = 1; i <= stage; ++i)
	printf("-%c", CHAR_LED[solution_set[i]]);
    puts("");
}

void fail(int fd, int stage, int problem_set[], int solution_set[])
{
    for (int i = 0; i < 3; ++i) {
	output(fd, R + G + W);
	usleep(200000);
	output(fd, 0);
	usleep(200000);
    }
}

void problem(int fd, int stage, int problem_set[])
{
    for (int i = 0; i < stage; ++i) {
	output(fd, problem_set[i] = 1 << (rand() % 3));
	usleep(130000);
	output(fd, 0);
	usleep(50000);
    }
}

int solve(int fd, int stage, int solution_set[])
{
    char read_data = 0;
    char pre_read_data = 0;
    int i = 0;

    while (i <= stage) {
	read(fd, &read_data, 1);
	write(fd, &read_data, 1);
	if (i != stage && read_data == Y)
	    return SURRENDER;
	if (read_data != 0 && pre_read_data == 0)
	    solution_set[i++] = read_data;
	pre_read_data = read_data;
	usleep(100000);
    }
    return (read_data != Y) ? FAILURE : NEED_TEST; 
}

int test(int stage, int problem_set[], int solution_set[])
{
    for (int i = 0; i < stage; ++i)
	if (solution_set[i] != problem_set[i])
	    return FAILURE;
    return SUCCESS;
}

int main()
{
    mknod(DEV_FILE_NAME, (S_IRWXU|S_IRWXG|S_IFCHR), MKDEV(DEV_GPIO_MAJOR, 0));
    int fd = open(DEV_FILE_NAME, O_RDWR|O_NONBLOCK);
    if (fd < 0) {
	fprintf(stderr, "Error: Cannot open GPIO Driver\n");
	exit(1);
    }

    int stage = 1;
    int problem_set[END_STAGE + 1] = {};
    int solution_set[END_STAGE + 1] = {};
    int fail_stack = 0;

    puts("#################[ Welcome to Agility Game ! ]#####################");
    puts("Remember LED(s) and press the matched button(s) and the yellow");
    puts("(submission) button. If you push the yellow button in the middle of");
    puts("solving the problem, it is considerd a surrender. If you're ready");
    puts("then prees the yellow button! Enjoy the game!!\n");

    printf("Final stage    : %d\n", END_STAGE); 
    printf("Left Chance(s) : %d\n", END_FAIL); 
    puts("===================================================================");

    // waiting the start input
    char read_data;
    do
	read(fd, &read_data, 1);
    while (read_data != Y);

    // start game
    start_game(fd);

    while (stage <= END_STAGE) {
	// wait 0.5s for each round.
	usleep(500000); 

	// blink LED(s) according to the stage.
	problem(fd, stage, problem_set);

	// input the solution
	int stage_result = solve(fd, stage, solution_set);
	if (stage_result == NEED_TEST)
	// test for the result
	    stage_result = test(stage, problem_set, solution_set);

	// handle the result (next stage or succeed or fail)
	if (stage_result == SUCCESS) { 
	    printf("[Succeed] Stage %d\n", stage);
	    print_stage(stage, problem_set, solution_set);
	    if (stage == END_STAGE)		// success-end
		succeed_all(fd);
	    stage++;				// to the next stage
	} else if (stage_result == FAILURE || stage_result == SURRENDER) {
	    if (stage_result == FAILURE) {
		puts("[Fail]");
		print_stage(stage, problem_set, solution_set);
	    }
	    else {
		puts("[Surrender]");
		print_stage_problem(stage, problem_set);
	    }
	    fail(fd, stage, problem_set, solution_set);
	    if (++fail_stack == END_FAIL) {	// failure-end
		puts("[Fail]");
		puts("  You failed three times in total.");
		break;
	    }
	    // retry the stage
	    int left_chance = END_FAIL - fail_stack;
	    if (left_chance > 1)
		printf("There are still %d more chances left.\n", left_chance);
	    else
		printf("You have the last chance.\n");
	} else {				// error-end
	    fprintf(stderr, "Error: An unexpected situation occurs.\n");
	    break;
	} 
    }

    close(fd);
    return 0;
}
