#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fcm.h"
//#define MAX_DATA_POINTS 10000
//#define MAX_CLUSTER 100
//#define MAX_DATA_DIMENSION 5
/*
long num_data_points;
long num_clusters;
long num_dimensions;
double low_high[MAX_DATA_DIMENSION][2];
double degree_of_memb[MAX_DATA_POINTS][MAX_CLUSTER];
double epsilon;
double fuzziness;
double data_point[MAX_DATA_POINTS][MAX_DATA_DIMENSION];
double cluster_centre[MAX_CLUSTER][MAX_DATA_DIMENSION];
*/

long
fcm_init(char *fname) {
    int i, j, r, rval;
    FILE *f;
    double s;
    if ((f = fopen(fname, "r")) == NULL) {
        printf("Failed to open input file.");
        return -1;
    }
    fscanf(f, "%d %d %d", &num_data_points, &num_clusters, &num_dimensions);
    if (num_clusters > MAX_CLUSTER) {
        printf("Number of clusters should be < %d\n", MAX_CLUSTER);
        goto failure;
    }
    if (num_data_points > MAX_DATA_POINTS) {
        printf("Number of data points should be < %d\n", MAX_DATA_POINTS);
        goto failure;
    }
    if (num_dimensions > MAX_DATA_DIMENSION) {
        printf("Number of dimensions should be >= 1.0 and < %d\n",
                MAX_DATA_DIMENSION);
        goto failure;
    }
    fscanf(f, "%lf", &fuzziness);
    if (fuzziness <= 1.0) {
        printf("Fuzzyness coefficient should be > 1.0\n");
        goto failure;
    }
    fscanf(f, "%lf", &epsilon);
    if (epsilon <= 0.0 || epsilon > 1.0) {
        printf("Termination criterion should be > 0.0 and <= 1.0\n");
        goto failure;
    }
    for (i = 0; i < num_data_points; i++) {
        for (j = 0; j < num_dimensions; j++) {
            fscanf(f, "%lf", &data_point[i][j]);
            if (data_point[i][j] < low_high[j][0])
                low_high[j][0] = data_point[i][j];
            if (data_point[i][j] > low_high[j][1])
                low_high[j][1] = data_point[i][j];
        }
    }
    for (i = 0; i < num_data_points; i++) {
        s = 0.0;
        r = 100;
        for (j = 1; j < num_clusters; j++) {
            rval = rand() % (r + 1);
            r -= rval;
            degree_of_memb[i][j] = rval / 100.0;
            s += degree_of_memb[i][j];
        }
        degree_of_memb[i][0] = 1.0 - s;
    }
    fclose(f);
    return 0;
failure:
    fclose(f);
    exit(1);
}

long
fcm_calculate_centre_vectors() {
    int i, j, k;
    double numerator, denominator;
    double t[MAX_DATA_POINTS][MAX_CLUSTER];
    for (i = 0; i < num_data_points; i++) {
        for (j = 0; j < num_clusters; j++) {
            t[i][j] = pow(degree_of_memb[i][j], fuzziness);
        }
    }
    for (j = 0; j < num_clusters; j++) {
        for (k = 0; k < num_dimensions; k++) {
            numerator = 0.0;
            denominator = 0.0;
            for (i = 0; i < num_data_points; i++) {
                numerator += t[i][j] * data_point[i][k];
                denominator += t[i][j];
            }
            cluster_centre[j][k] = numerator / denominator;
        }
    }
    return 0;
}

double
fcm_get_norm(int i, int j) {
    int k;
    double sum = 0.0;
    for (k = 0; k < num_dimensions; k++) {
        sum += pow(data_point[i][k] - cluster_centre[j][k], 2);
    }
    return sqrt(sum);
}

double
fcm_get_new_value(int i, int j) {
    int k;
    double t, p, sum;
    sum = 0.0;
    p = 2 / (fuzziness - 1);
    for (k = 0; k < num_clusters; k++) {
        t = fcm_get_norm(i, j) / fcm_get_norm(i, k);
        t = pow(t, p);
        sum += t;
    }
    return 1.0 / sum;
}

double
fcm_update_degree_of_membership() {
    int i, j;
    double new_uij;
    double max_diff = 0.0, diff;
    for (j = 0; j < num_clusters; j++) {
        for (i = 0; i < num_data_points; i++) {
            new_uij = fcm_get_new_value(i, j);
            diff = new_uij - degree_of_memb[i][j];
            if (diff > max_diff)
                max_diff = diff;
            degree_of_memb[i][j] = new_uij;
        }
    }
    return max_diff;
}

long
fcm_fcm(char *fname) {
    double max_diff;
    fcm_init(fname);
    do {
        fcm_calculate_centre_vectors();
        max_diff = fcm_update_degree_of_membership();
    } while (max_diff > epsilon);
    return 0;
}

long
fcm_gnuplot_membership_matrix() {
    int i, j, cluster;
    char fname[100];
    double highest;
    FILE * f[MAX_CLUSTER];
    if (num_dimensions != 2) {
        printf("Plotting the cluster only works when the\n");
        printf("number of dimensions is two. This will create\n");
        printf("a two-dimensional plot of the cluster points.\n");
        exit(1);
    }
    for (j = 0; j < num_clusters; j++) {
        sprintf(fname, "cluster.%d", j);
        if ((f[j] = fopen(fname, "w")) == NULL) {
            printf("Could not create %s\n", fname);
            for (i = 0; i < j; i++) {
                fclose(f[i]);
                sprintf(fname, "cluster.%d", i);
                remove(fname);
            }
            return -1;
        }
        fprintf(f[j], "#Data points for cluster: %d\n", j);
    }
    for (i = 0; i < num_data_points; i++) {
        cluster = 0;
        highest = 0.0;
        for (j = 0; j < num_clusters; j++) {
            if (degree_of_memb[i][j] > highest) {
                highest = degree_of_memb[i][j];
                cluster = j;
            }
        }
        fprintf(f[cluster], "%lf %lf\n", data_point[i][0], data_point[i][1]);
    }
    for (j = 0; j < num_clusters; j++) {
        fclose(f[j]);
    }
    if ((f[0] = fopen("gnuplot.script", "w")) == NULL) {
        printf("Could not create gnuplot.script.\n");
        for (i = 0; i < j; i++) {
            fclose(f[i]);
            sprintf(fname, "cluster.%d", i);
            remove(fname);
        }
        return -1;
    }
    fprintf(f[0], "set terminal png medium\n");
    fprintf(f[0], "set output \"cluster_plot.png\"\n");
    fprintf(f[0], "set title \"FCM clustering\"\n");
    fprintf(f[0], "set xlabel \"x-coordinate\"\n");
    fprintf(f[0], "set ylabel \"y-coordinate\"\n");
    fprintf(f[0], "set xrange [%lf : %lf]\n", low_high[0][0], low_high[0][1]);
    fprintf(f[0], "set yrange [%lf : %lf]\n", low_high[1][0], low_high[1][1]);
    fprintf(f[0],
            "plot 'cluster.0' using 1:2 with points pt 7 ps 1 lc 1 notitle");
    for (j = 1; j < num_clusters; j++) {
        sprintf(fname, "cluster.%d", j);
        fprintf(f[0],
                ",\\\n'%s' using 1:2 with points  pt 7 ps 1 lc %d notitle",
                fname, j + 1);
    }
    fprintf(f[0], "\n");
    fclose(f[0]);
    return 0;
}

void
fcm_print_data_points(char *fname) {
    int i, j;
    FILE *f;
    if (fname == NULL)
        f = stdout;
    else if ((f = fopen(fname, "w")) == NULL) {
        printf("Cannot create output file.\n");
        exit(1);
    }
    fprintf(f, "Data points:\n");
    for (i = 0; i < num_data_points; i++) {
        printf("Data[%d]: ", i);
        for (j = 0; j < num_dimensions; j++) {
            printf("%.5lf ", data_point[i][j]);
        }
        printf("\n");
    }
    if (fname == NULL)
        fclose(f);
}

void
fcm_print_membership_matrix(char *fname) {
    int i, j;
    FILE *f;
    if (fname == NULL)
        f = stdout;
    else if ((f = fopen(fname, "w")) == NULL) {
        printf("Cannot create output file.\n");
        exit(1);
    }
    fprintf(f, "Membership matrix:\n");
    for (i = 0; i < num_data_points; i++) {
        fprintf(f, "Data[%d]: ", i);
        for (j = 0; j < num_clusters; j++) {
            fprintf(f, "%lf ", degree_of_memb[i][j]);
        }
        fprintf(f, "\n");
    }
    if (fname == NULL)
        fclose(f);
}

