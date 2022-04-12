outputs = cv-problem cv-solution cv-solution-no-lock \
		  dice-timer-skeleton dice-timer \
		  cv-pc cv-pc-answer cv-pc-error

all : $(outputs)

clean:
	rm -f $(outputs)

CC = gcc

CFLAGS = -Wall -pthread -o

cv-problem: cv-problem.c
	$(CC) $(CFLAGS) $@ $<
cv-solution: cv-solution.c
	$(CC) $(CFLAGS) $@ $<
cv-solution-no-lock: cv-solution-no-lock.c
	$(CC) $(CFLAGS) $@ $<

dice-timer-skeleton: dice-timer-skeleton.c
	$(CC) $(CFLAGS) $@ $<
dice-timer: dice-timer.c
	$(CC) $(CFLAGS) $@ $<

cv-pc: cv-pc.c
	$(CC) $(CFLAGS) $@ $<
cv-pc-answer: cv-pc-answer.c
	$(CC) $(CFLAGS) $@ $<
cv-pc-error: cv-pc-error.c
	$(CC) $(CFLAGS) $@ $<
