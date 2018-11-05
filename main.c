#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fcm.h"


int main(int argc, char **argv) {
    printf("------------------------------------------------------------------------\n");
    if (argc != 3) {
        printf("USAGE: fcm <input file> or gen <input file>\n");
        //printf("USAGE: fcm <input file>\n");
        exit(1);
    }
    if(strcmp(argv[1], "fcm")==0){
        fcm_fcm(argv[2]);
        printf("Number of data points: %d\n", num_data_points);
        printf("Number of clusters: %d\n", num_clusters);
        printf("Number of data-point dimensions: %d\n", num_dimensions);
        printf("Accuracy margin: %lf\n", epsilon);
        fcm_print_membership_matrix("membership.matrix");
        fcm_gnuplot_membership_matrix();
        printf("------------------------------------------------------------------------\n");
        printf("The program run was successful...\n");
        printf("Storing membership matrix in file 'membership.matrix'\n\n");
        printf("If the points are on a plane (2 dimensions)\n");
        printf("the gnuplot script was generated in file 'gnuplot.script', and\n");
        printf("the gnuplot data in files cluster.[0]... \n\n");
        printf("Process 'gnuplot.script' to generate graph: 'cluster_plot.png'\n\n");
        printf("NOTE: While generating the gnuplot data, for each of the data points\n");
        printf("the corresponding cluster is the one which has the highest\n");
        printf("degree-of-membership as found in 'membership.matrix'.\n");
        printf("------------------------------------------------------------------------\n");
    }
    return 0;
}
