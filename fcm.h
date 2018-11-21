#ifndef FCM_H
#define FCM_H

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class FCM{

  public:
//    FCM(double, double, bool);
    FCM(double, double);
//    FCM(double);
//    FCM();
    ~FCM();

    double update_membership(); // returns the max diff
    void compute_centers();
    double get_dist(long, long);
    double compute_membership_point(long, long);
    void set_data(MatrixXf *);
    void set_membership(MatrixXf *);
    void init_membership();
    void set_num_clusters(long);

    MatrixXf * get_data();
    MatrixXf * get_membership();
    MatrixXf * get_cluster_center();

  private:
    double m_m; // the fuzziness
    double m_epsilon; // threshold to stop
    long m_num_clusters;
    long m_num_dimensions;

    MatrixXf * m_membership;
    MatrixXf * m_data;
    MatrixXf * m_cluster_center;

    void init_centers();
};

#endif

