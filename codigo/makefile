CC = gcc

OPTIM   = -O3 -march=native -mtune=native -pipe -fivopts
OPTIM  += -fmodulo-sched -flto -fwhole-program -fno-plt
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wunused-result $(OPTIM)

main: ex2.c
	$(CC) $(CFLAGS) $< -o $@
