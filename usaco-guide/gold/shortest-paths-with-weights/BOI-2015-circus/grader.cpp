#include "circus.h"
#include <stdio.h>
#include <stdlib.h>

#define NMAX 100000
#define QMAX 1000000

static int N, M, Q;
static int P[NMAX];

int main()
{
	int i, d;
	long long max_code;

	scanf("%d%d", &N, &M);
	for (i = 0; i < N; ++i) {
		scanf("%d", &P[i]);
	}
	init(N, M, P);
	scanf("%d", &Q);
	for (i = 0; i < Q; ++i) {
		scanf("%d", &d);
		printf("%d\n", minLength(d));
	}

	return 0;
}
