#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct seq_t { int N, *d; } seq_t;
typedef unsigned int uint;

static const uint _p 40961;
static const uint _z 243;

int scanseq(seq_t* pseq)
{
	int n;
	seq_t seq;
	
	if(!pseq) { exit(EXIT_FAILURE); }
	if(!scanf("%d: [", &seq.N)) { return 0; }
	seq.d = (int*) malloc(seq.N * sizeof(int));
	if(!seq.d) { exit(EXIT_FAILURE); }
	scanf("%d", &seq.d[n = 0]);
	while((++n < seq.N) && scanf(",%d", &seq.d[n])) { /* do nothing */ }
	if(getchar()!=']') { return 0; }
	(*pseq) = seq;
	return 1;
}

void printseq(const seq_t seq)
{
	int n;

	if(!seq.d || seq.N < 0 ) { exit(EXIT_FAILURE); }
	printf("%d: [", seq.N);
	if(seq.N) { printf("%d", seq.d[0]); }
	for(n = 1; n < seq.N; ++n) { printf(",%d", seq.d[n]); }
	printf("]\n");
}

void copyseq(const seq_t seq, seq_t* pcpy)
{
	seq_t cpy;
	int n;

	if(!pcpy) { exit(EXIT_FAILURE); }

	cpy.N = seq.N;
	cpy.d = (int*) malloc(cpy.N * sizeof(int));
	if(!cpy.d) { exit(EXIT_FAILURE); }
	for(n = 0; n < seq.N; ++n) { cpy.d[n] = seq.d[n]; }
	(*pcpy) = cpy;
}

void _ntt(const seq_t x, uint z, uint p)
{

}

void ntt(const seq_t x, seq_t* py)
{

}

/* assignment */
void lfir2(const seq_t h, const seq_t x, seq_t* py)
{
	if(!py) { exit(EXIT_FAILURE); }
	
}

int main()
{
	int nscan;
	seq_t h, x, y;

	nscan = scanseq(&h);
	nscan += scanseq(&x);
	if(nscan != 2) { exit(EXIT_SUCCESS); }
	lfir2(h, x, &y);
	printseq(y);

	free(h.d); free(x.d); free(y.d);
	return EXIT_SUCCESS;
}