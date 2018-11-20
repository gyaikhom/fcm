#ifndef FCM_H
#define FCM_H

#include<Eigen/Dense>

using namespace Eigen;
using namespace std;

class FCM{

  public:
    double m_m;
    double m_epsilon;
    long m_num_clusters;
    long m_num_dimensions;
    MatrixXf m_membership;
    MatrixXf m_data;
    MatrixXf m_cluster_center;

    FCM(double, double);
    FCM(double);
    FCM();



    double update_membership(); // returns the max diff
    void compute_centers();
    double get_norm(long, long);
    double compute_membership_point(long, long);

};

#endif

