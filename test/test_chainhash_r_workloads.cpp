#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <ulib/rdtsc.h>
#include <ulib/chainhash_r.h>
#include <ulib/thread.h>
#include <ulib/rand_tpl.h>

using namespace ulib;

#define R_TH_NUM 10
#define W_TH_NUM 5

chain_hash_map_r<int,int> map(1000, 10);

class writer : public thread {
public:
	int
	run()
	{
		while (is_running()) {
			map[RAND_NR_NEXT(_u, _v, _w) & 0xffffff] =
				RAND_NR_NEXT(_u, _v, _w); 
			++_cnt;
		}
		return 0;
	}

	writer()
	: _cnt(0)
	{
		uint64_t seed = time(NULL);
		RAND_NR_INIT(_u, _v, _w, seed);
	}

	uint64_t
	count() const
	{ return _cnt; }

private:
	volatile uint64_t _cnt;
	uint64_t _u, _v, _w;
};

class reader : public thread {
public:
	int
	run()
	{
		while (is_running()) {
			chain_hash_map<int,int>::const_iterator it =
				map.find(RAND_NR_NEXT(_u, _v, _w));
			++_cnt;
		}
		return 0;
	}

	reader()
	: _cnt(0)
	{
		uint64_t seed = time(NULL);
		RAND_NR_INIT(_u, _v, _w, seed);
	}

	uint64_t
	count() const
	{ return _cnt; }

private:
	volatile uint64_t _cnt;
	uint64_t _u, _v, _w;
};

int main()
{
	reader r[R_TH_NUM];
	writer w[W_TH_NUM];
	
	for (int i = 0; i < R_TH_NUM; ++i)
		r[i].start();
	for (int i = 0; i < W_TH_NUM; ++i)
		w[i].start();

	uint64_t start = rdtsc();
	sleep(5);

	for (int i = 0; i < R_TH_NUM; ++i)
		r[i].stop_and_join();
	for (int i = 0; i < W_TH_NUM; ++i)
		w[i].stop_and_join();
	uint64_t elapse = rdtsc() - start;
	
	uint64_t r_cnt = 0;
	uint64_t w_cnt = 0;	
	for (int i = 0; i < R_TH_NUM; ++i)
		r_cnt += r[i].count();
	for (int i = 0; i < W_TH_NUM; ++i)
		w_cnt += w[i].count();

	uint64_t ns_per_read  = elapse / r_cnt;
	uint64_t ns_per_write = elapse / w_cnt;

	printf("total ops   :%lu read, %lu write\n", r_cnt, w_cnt);
	printf("ns_per_read :%lu\t%lu op/s\n", ns_per_read,  1000000000ul / ns_per_read);
	printf("ns_per_write:%lu\t%lu op/s\n", ns_per_write, 1000000000ul / ns_per_write);

	printf("passed\n");

	return 0;
}
