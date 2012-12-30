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
    avl_node_t link;
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

int node_cmp(const void *a, const void *b)
{
    return generic_compare(*(node *)a, *(node *)b);
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
    node *avl;
    avl_tree_t tree;

    avl_create(&tree, node_cmp, sizeof(node), 0);

    for (t = 0; t < ins; t++) {
        avl = new node(myrand());
        avl_index_t where;
        avl_find(&tree, avl, &where);
        avl_insert(&tree, avl, where);
        counter++;
        done++;
    }

    printf("insertion done\n");
    done = 0;

    for (t = 0; t < get; t++) {
        node n(myrand());
        avl_find(&tree, &n.link, NULL);
        counter++;
        done++;
    }

    ulib_timer_t timer;
    size_t num = 0;
    timer_start(&timer);
    for (node *p = avl_first(&tree); p != NULL; p = AVL_NEXT(&tree, p)) {
        avl_remove(&tree, p);
        delete p;
        ++num;
    }

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
