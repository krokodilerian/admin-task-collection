#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIALSIZE 128
#define KEYLEN 16
#define HSIZE (1<<KEYLEN)

int ht[HSIZE];

inline uint32_t zend_inline_hash_func(const char *arKey, uint32_t nKeyLength)
{
        register uint32_t hash = 3317;

        /* variant with the hash unrolled eight times */
        for (; nKeyLength >= 8; nKeyLength -= 8) {
                hash = ((hash << 5) + hash) + *arKey++;
                hash = ((hash << 5) + hash) + *arKey++;
                hash = ((hash << 5) + hash) + *arKey++;
                hash = ((hash << 5) + hash) + *arKey++;
                hash = ((hash << 5) + hash) + *arKey++;
                hash = ((hash << 5) + hash) + *arKey++;
                hash = ((hash << 5) + hash) + *arKey++;
                hash = ((hash << 5) + hash) + *arKey++;
        }
        switch (nKeyLength) {
                case 7: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
                case 6: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
                case 5: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
                case 4: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
                case 3: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
                case 2: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
                case 1: hash = ((hash << 5) + hash) + *arKey++; break;
                case 0: break;
        }
        return hash;
} 

void addtohash(char *k) {
	uint32_t val;

	val = zend_inline_hash_func(k, strlen(k)) & (HSIZE - 1);
	ht[val]++;
}

int main() {

	char *qs, *qp;
	char *var;

	int numvar = 0;
	int uniqvar = 0;

	int i;

	size_t varsz = INITIALSIZE;

	printf("Content-type: text/plain\n\n");

	qs = getenv("QUERY_STRING");

	if (qs == NULL) return 0;
	memset(ht, 0, HSIZE);

	qp = qs;
	var = (char *) malloc(varsz);

	while(qs != '\0') {
		qp = strchr(qs, '=');
		if (qp == NULL) break;
		if ( (qp - qs + 2) > varsz) {
			varsz *= 2;
			var = realloc(var, varsz);
		}
		strncpy(var, qs, (qp-qs));
		var[qp-qs+1] = '\0';

		addtohash(var);
		numvar++;

		qs = strchr(qp, '&');
		if (qs == NULL) break;
		qs++;
		
	}

	for (i=0; i<HSIZE; i++) {
		if(ht[i]==0) continue;
		uniqvar++;
		printf("hash %d num %d\n", i, ht[i]);
	}

	printf("%d variables, %d unique\n", numvar, uniqvar);
	if (numvar<1000) {
		printf("Not enough variables\n");
		return 0;
	}

	if (uniqvar>3) {
		printf("not enough collisions\n");
		return 0;
	}

	printf("!Passed!\n");

	return 0;
}
