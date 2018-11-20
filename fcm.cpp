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

FCM::FCM(double m, double epsilon){
    m_epsilon = epsilon;
    m_m = m;
}

FCM::FCM(double m){
    FCM(m, 1.0);
}

FCM::FCM(){
    FCM(2);
}


double FCM::update_membership(){
    return 0;
}

void FCM::compute_centers(){
    //nothing
}

double FCM::get_norm(long i, long j){
    return 0;
}

double FCM::compute_membership_point(long i, long j){
    return 0;
}




