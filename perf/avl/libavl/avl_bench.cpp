#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ulib/timer.h>
#include <ulib/common.h>
#include <ulib/rand_tpl.h>
#include "avl.h"

uint64_t u, v, w;
#define myrand()  RAND_NR_NEXT(u, v, w)

const char *usage =
	"%s [ins] [get]\n";

volatile long counter = 0;
volatile long done    = 0;

struct node {
	uint64_t value;

	node(uint64_t val = 0)
		: value(val) { }

	bool
	operator<(const node &other) const
	{ return value < other.value; }

	bool
	operator>(const node &other) const
	{ return value > other.value; }
};

int node_cmp(const void *a, const void *b, void *)
{
	return generic_compare(*(node *)a, *(node *)b);
}

void node_destroy(void *n, void *)
{
	delete (node *)n;
}


static void sig_alarm_handler(int)
{
	printf("%ld per sec, %ld done\n", counter, done);
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
	avl_table *tree;

	tree = avl_create(node_cmp, NULL, &avl_allocator_default);
	if (tree == NULL) {
		fprintf(stderr, "create avl table failed\n");
		exit(EXIT_FAILURE);
	}

	for (t = 0; t < ins; t++) {
		node *n = new node(myrand());
		avl_insert(tree, n);
		counter++;
		done++;
	}

	printf("insertion done\n");
	done = 0;

	for (t = 0; t < get; t++) {
		node n(myrand());
		avl_find(tree, &n);
		counter++;
		done++;
	}

	ulib_timer_t timer;
	size_t num = avl_count(tree);
	timer_start(&timer);
	avl_destroy(tree, node_destroy);
	printf("all done, %zu elements, %f sec\n", num, timer_stop(&timer));
}

int main(int argc, char *argv[])
{
	long ins = 2000000;
	long get = 5000000;
	uint64_t seed = time(NULL);

	if (argc > 1)
		ins = atol(argv[1]);
	if (argc > 2)
		get = atol(argv[2]);

	RAND_NR_INIT(u, v, w, seed);

	register_sig_handler();

	constant_insert(ins, get);

	printf("passed\n");

	return 0;
}
