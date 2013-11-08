/**
 * This generates data for testing the FCM algorithm.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximum number of clusters allowed by this implementation. */
#define MAX_CLUSTER 100

/* Maximum number of data points which should be clustered. */
#define MAX_DATA 10000

/* Maximum number of dimensions of a data point. */
#define MAX_DATA_DIMENSION 5

int main(int argc, char **argv) {
	int n, c, d, i, j;
	int l[MAX_DATA_DIMENSION], h[MAX_DATA_DIMENSION];
	double epsilon, m;
	FILE *f;
	if (argc != 2) {
		printf("Usage: gen <filename>\n");
		exit(1);
	}
	printf("\nThis program generates random data points\n");
	printf("for testing the FCM algorithm.\n\n");
	do {
		printf("Enter number of data points.\n");
		printf("Value should be >= 1 and < %d: ", MAX_DATA);
		if (scanf("%d", &n) == EOF)
			continue;
	} while (n < 1 || n > MAX_DATA);
	do {
		printf("Enter number of clusters.\n");
		printf("Value should be >= 2 and < %d: ", MAX_CLUSTER);
		if (scanf("%d", &c) == EOF)
			continue;
	} while (c < 2 || c > MAX_CLUSTER);
	do {
		printf("Enter termination criterion (epsilon).\n");
		printf("Value should be >= 0.0 and <= 1.0: ");
		if (scanf("%lf", &epsilon) == EOF)
			continue;
	} while (epsilon < 0 || epsilon > 1.0);
	do {
		printf("Enter fuzzyness coefficient.\n");
		printf("Value should be > 1.0: ");
		if (scanf("%lf", &m) == EOF)
			continue;
	} while (m <= 1.0);
	do {
		printf("Enter number of dimensions.\n");
		printf("Value should be >= 1 and < %d: ", MAX_DATA_DIMENSION);
		if (scanf("%d", &d) == EOF)
			continue;
	} while (d < 1 || d > MAX_DATA_DIMENSION);
	printf("\nThe program will generate random data points by using\n");
	printf("the lowest and highest values allowed for a given dimension.\n");
	printf("The highest value should be greater than the lowest value\n");
	printf("for a given dimension.\n");
	for (i = 0; i < d; i++) {
		do {
			printf("Enter lowest value for dimension [%d]: ", i);
			if (scanf("%d", &l[i]) == EOF)
				continue;
			printf("Enter highest value for dimension [%d]: ", i);
			if (scanf("%d", &h[i]) == EOF)
				continue;
		} while (l[i] >= h[i]);
	}

	if ((f = fopen(argv[1], "w")) == NULL) {
		printf("Failed to create new data file named %s\n", argv[1]);
		exit(1);
	}
	fprintf(f, "%d %d %d\n", n, c, d);
	fprintf(f, "%lf %lf\n", m, epsilon);
	for (i = 0; i < n; i++) {
		for (j = 0; j < d; j++) {
			fprintf(f, "%d ", (rand() % (h[j] - l[j] + 1)) + l[j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
	return 0;
}
