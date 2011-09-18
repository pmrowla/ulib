#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define AH_64BIT
#include <ulib/alignhash_tpl.h>

const char *usage = 
	"%s [ins] [get]\n";

volatile long counter = 0;

DECLARE_ALIGNHASH(myhash, uint32_t, uint32_t, 1, alignhash_hashfn, alignhash_equalfn)

static void sig_alarm_handler(int signum)
{
	printf("%ld per sec\n", counter);
	counter = 0;
	alarm(1);
}

void register_sig_handler()
{
	struct sigaction sigact;

	sigact.sa_handler = sig_alarm_handler;
	sigact.sa_flags = 0;
	if (sigaction(SIGALRM, &sigact, NULL)) {
		perror("sigaction");
		exit(-1);
	}
	alarm(1);
}

void constant_insert(long ins, long get)
{
	long t;
	int ret;

	alignhash_t(myhash) *my = alignhash_init(myhash);

	if (my == NULL) {
		fprintf(stderr, "alloc failed\n");
		return;
	}

	for (t = 0; t < ins; t++) {
		ah_iter_t itr = alignhash_set(myhash, my, lrand48(), &ret);
		if (alignhash_end(my) != itr)
			alignhash_value(my, itr) = t;
		counter++;
	}

	printf("insertion done\n");

	for (t = 0; t < get; t++) {
		alignhash_get(myhash, my, lrand48());
		counter++;
	}

	alignhash_destroy(myhash, my);
    
	printf("all done\n");
}

int main(int argc, char *argv[])
{
	long ins = 10000000;
	long get = 1000000000;

	if (argc > 1)
		ins = atol(argv[1]);
	if (argc > 2)
		get = atol(argv[2]);

	srand48((int)time(NULL));

	register_sig_handler();

	constant_insert(ins, get);

	return 0;
}
