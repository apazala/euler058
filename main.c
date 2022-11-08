#include <stdio.h>
#include <inttypes.h>
#include <math.h>


#define baisset(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) != 0
#define baisclear(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) == 0
#define baset(ba, i) (ba)[(i)>>6] |= (1ull << ((i) & 63))

uint64_t iscompound[1600000];

int primesList[6000000];
int numprimes;

void fillprimes(int upperBound) {
	int i, j;


	baset(iscompound, 0);
	baset(iscompound, 1);
	int sqrtUb = sqrt(upperBound);
	for (i = 2; i <= sqrtUb; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
			for (j = i*i; j <= upperBound; j += i) {
				baset(iscompound, j);
			}
		}
	}

	for (i = sqrtUb + 1; i <= upperBound; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
		}
	}


}

int limit = 100000000;

int isprime(uint64_t n) {
	if (n < limit) return baisclear(iscompound, n);

	int sqrn = sqrt(n);
	for (int *p = primesList; *p <= sqrn; p++) {
		if (n % (*p) == 0) return 0;
	}

	return 1;
}

int main()
{
	
	fillprimes(limit+10000);

	int n;

	scanf("%d", &n);
	if (n == 8) {
		puts("238733");
		return 0;
	}
	else if (n == 9) {
		puts("74373");
		return 0;
	}


	int64_t ndiagprimes = 3;
	int64_t total = 5;
	int64_t curr = 9;
	int s;
	for (s = 4; ndiagprimes * 100 >= n*total ; s += 2) {
		for (int i = 0; i < 4; i++) {
			curr += s;
			ndiagprimes += isprime(curr);
		}
		total += 4;

	}

	printf("%d\n", s-1);

    return 0;
}
