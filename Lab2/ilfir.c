#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct seq_t { int N, *d; } seq_t;

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

/* assignment */
void ilfir(const seq_t x, const seq_t y, seq_t* ph)
{
	seq_t h;
	
	if(!ph) { exit(EXIT_FAILURE); }
	h = (*ph);
	(*ph) = h;
}

int main()
{
	int nscan;
	seq_t h, x, y;

	nscan = scanseq(&x);
	nscan += scanseq(&y);
	if(nscan != 2) { exit(EXIT_SUCCESS); }
	ilfir(x, y, &h);
	printseq(h);

	free(h.d); free(x.d); free(y.d);
	return EXIT_SUCCESS;
}