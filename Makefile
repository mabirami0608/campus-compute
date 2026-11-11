CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: campuscompute

campuscompute: main.c scheduler.c banker.c campuscompute.h
	$(CC) $(CFLAGS) main.c scheduler.c banker.c -o campuscompute

clean:
	rm -f campuscompute
