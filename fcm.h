#ifndef FCM_H
#define FCM_H

#define MAX_DATA_POINTS 10000
#define MAX_CLUSTER 100
#define MAX_DATA_DIMENSION 5
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long num_data_points;
long num_clusters;
long num_dimensions;
double low_high[MAX_DATA_DIMENSION][2];
double degree_of_memb[MAX_DATA_POINTS][MAX_CLUSTER];
double epsilon;
double fuzziness;
double data_point[MAX_DATA_POINTS][MAX_DATA_DIMENSION];
double cluster_centre[MAX_CLUSTER][MAX_DATA_DIMENSION];


long fcm_init(char *);
long fcm_calculate_centre_vectors();
double fcm_get_norm(long, long);
double fcm_get_new_value(long, long);
double fcm_update_degree_of_membership();
long fcm_fcm(char*);
long fcm_gnuplot_membership_matrix();
void fcm_print_data_points(char *);
void fcm_print_membership_matrix(char *);

#endif
