#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <Eigen/Dense>
#include "fcm.h"


////This is to solve the problem with gtest which somehow sets the nullptr pointers
//FCM::FCM(double m, double epsilon, bool googletestispresent){
//    m_epsilon = epsilon;
//    m_m = m;
//    m_membership = new MatrixXf;
//    m_data = new MatrixXf;
//    m_cluster_center = new MatrixXf;
////    cout<<"data is set to nullptr\n";
////    cout<<"m_data right away: "<< m_data<<endl;
//}

FCM::FCM(double m, double epsilon){
    m_epsilon = epsilon;
    m_m = m;
    m_membership = nullptr;
    m_data = nullptr;
    m_cluster_center = nullptr;
//    cout<<"data is set to nullptr\n";
//    cout<<"m_data right away: "<< m_data<<endl;
}

//FCM::FCM(double m){
//    /*
//     * The recommended value of m is 2
//    */
//    FCM(m, 1.0);
//}

//FCM::FCM(){
//    FCM(2);
//}

FCM::~FCM(){

    cout << __func__ <<" FCM destructor\n";

//    if(m_data){
//        //m_data
//        cout << __func__ << " will be deleted m_data\n";
//        cout << __func__ << " m_data: \n" << m_data <<endl ;
//        delete m_data;
//        m_data = nullptr;
//        if(m_data==nullptr){
//            cout << __func__ << " verify m_data success\n";
//        }else{
//            cout << __func__ << " verify m_data fail\n";
//        }
//    }
//    else if(m_data != nullptr){
//        cout << __func__ << " neither nullptr nor non-empty\n";
//    }
//    else{
//        cout << __func__ << " m_data is nullptr\n";
//    }


    if(m_data==nullptr){
        //m_data
        cout << __func__ << " m_data is nullptr\n";
    }
    else{
        cout << __func__ << " will be deleted m_data\n";
        cout << __func__ << " m_data: \n" << m_data <<endl ;
        delete m_data;
        m_data = nullptr;
        if(m_data==nullptr){
            cout << __func__ << " verify m_data success\n";
        }else{
            cout << __func__ << " verify m_data fail\n";
        }
    }

    if(m_membership==nullptr){
        //m_membership
        cout << __func__ << " m_membership is nullptr\n";
    }
    else{
        cout << __func__ << " will be deleted m_membership\n";
        delete m_membership;
        m_membership = nullptr;
        if(m_membership==nullptr){
            cout << __func__ << " verify m_membership success\n";
        }else{
            cout << __func__ << " verify m_membership fail\n";
        }
    }

    if(m_cluster_center==nullptr){
        //m_cluster_center
        cout << __func__ << " m_cluster_center is nullptr\n";
    }
    else{
        cout << __func__ << " will be deleted m_cluster_center\n";
        delete m_cluster_center;
        m_cluster_center = nullptr;
        if(m_cluster_center==nullptr){
            cout << __func__ << " verify m_cluster_center success\n";
        }else{
            cout << __func__ << " verify m_cluster_center fail\n";
        }
    }
}

double FCM::update_membership(){
    long i, j;
    double new_uij;
    double max_diff = 0.0, diff;

    if(m_membership==0 || m_membership->rows() == 0){
        this->init_membership();
    }

    for (j = 0; j < m_num_clusters; j++) {
        for (i = 0; i < m_data->rows(); i++) {
            cout << "i: " << i << " , j: " << j <<endl;
            new_uij = compute_membership_point(i, j);
            diff = new_uij - (*m_membership)(i,j);
            if (diff > max_diff){
                max_diff = diff;
            }
            (*m_membership)(i,j) = new_uij;
        }
    }
    return max_diff;
}

void FCM::compute_centers(){
    long i, j, k;
    double numerator, denominator;
    MatrixXf t;
    t.resize(m_data->rows(), m_num_clusters);
    if(m_data == nullptr || m_data->rows() == 0){
        cout << __func__ <<"ERROR: number of rows is zero";
        return;
    }
    for (i = 0; i < m_data->rows(); i++) { // compute (u^m) for each cluster for each point
        for (j = 0; j < m_num_clusters; j++) {
            t(i,j) = pow((*m_membership)(i,j), m_m);
        }
    }
    for (j = 0; j < m_num_clusters; j++) { // loop for each cluster
        for (k = 0; k < m_num_dimensions; k++) { // for each dimension
            numerator = 0.0;
            denominator = 0.0;
            for (i = 0; i < m_data->rows(); i++) {
                numerator += t(i,j) * (*m_data)(i,k);
                denominator += t(i,j);
            }
            (*m_cluster_center)(j,k) = numerator / denominator;
        }
    }
}

double FCM::get_dist(long i, long j){
    /*
     * distance which is denoted in the paper as d
    */
    long k;
    double sum = 0.0;
    if(m_num_clusters==0){
        cout<< __func__ << " ERROR: number of clusters should not be zero\n";
    }
    else{
        cout<< __func__ << " number of clusters: "<<m_num_clusters<<endl;
    }
    for (k = 0; k < m_num_dimensions; k++) {
        cout<< __func__ << "  i: "<<i<<" j: "<<j << " k: "<<k<<endl;
        cout<< __func__ << "  data rows: "<<m_data->rows()<<" data cols: "<<m_data->cols()<<endl;
        cout << " center rows: "<<m_cluster_center->rows()<<" center cols: "<<m_cluster_center->cols()<<endl;
        sum += pow((*m_data)(i,k) - (*m_cluster_center)(j,k), 2);
    }
    return sqrt(sum);
    return 0;
}

double FCM::compute_membership_point(long i, long j){
    long k;
    double t, p, sum;
    sum = 0.0;
    p = 2 / (m_m - 1);
    if(m_num_clusters==0){
        cout<< __func__ << " ERROR: number of clusters should not be zero\n";
    }
    for (k = 0; k < m_num_clusters; k++) {
      cout<< __func__ << " k: "<<k<<endl;
      t = this->get_dist(i, j) / this->get_dist(i, k);
      t = pow(t, p);
      sum += t;
    }
    return 1.0 / sum;
}

void FCM::set_data(MatrixXf *data){
    //cout << __func__ << "  " <<m_data <<endl;
    if(m_data!=nullptr){
        cout << __func__ << " data is not nullptr\n";
        delete m_data;
    }
    if(m_membership!=nullptr){
        cout << __func__ <<  " membership is not nullptr\n";
        delete m_membership;
    }
    if(data->rows()==0){
        cout << __func__ << " ERROR: seting empty data\n";
    }
    m_data = data;
    m_num_dimensions = m_data->cols();
}

void FCM::set_membership(MatrixXf *membership){
    if(m_data==0){
        cout << __func__ << " ERROR: the data should present before setting up the membership\n";
    }
    if(m_num_clusters==0){
        if(membership->cols() == 0){
            cout << __func__ << " ERROR: the number of clusters is 0 and the membership matrix is empty\n";
        }
        else{
            m_num_clusters = membership->cols();
        }
    }
    if(m_membership!=nullptr){
        delete m_membership;
    }
    m_membership = membership;
    if(m_membership->rows()==0){
        m_membership->resize(m_data->rows(), m_num_clusters);
    }
}

void FCM::init_membership(){
    long i, j;
    double mem;
    cout<< __func__ << " inside\n";
    if(m_num_clusters == 0){
        cout << __func__ << " ERROR: the number of clusters is 0\n";
    }
    if(m_data==nullptr){
        cout << __func__ << " ERROR: the data should present before setting up the membership\n";
    }
    if(m_membership!=nullptr){
        cout << __func__  << " membership is not nullptr (ERROR)\n";
        delete m_membership;
    }
    else{
        cout << __func__  << " membership is nullptr\n";
    }
    m_membership = new MatrixXf;
    m_membership->resize(m_data->rows(), m_num_clusters);
    mem = 1.0 / m_num_clusters;
    for(j=0;j<m_num_clusters;j++){
        cout << __func__  << "  " << j <<endl;
        for(i=0;i<m_data->rows();i++){
            cout << __func__  << " row  " << i <<endl;
            (*m_membership)(i,j) = mem;
        }
    }
    cout << "end fors" <<endl;
}

void FCM::set_num_clusters(long num_clusters){
    m_num_clusters = num_clusters;
}


MatrixXf * FCM::get_data(){
    return m_data;
}

MatrixXf * FCM::get_membership(){
    return m_membership;
}
MatrixXf * FCM::get_cluster_center(){
    return m_cluster_center;
}


void FCM::init_centers(){
    if(m_num_clusters==0){
        cout<< __func__ << " ERROR: num of clusters should not be zero\n";
    }
    if(m_cluster_center==nullptr){
        m_cluster_center  = new MatrixXf;
    }
    m_cluster_center->resize(m_num_clusters, m_num_dimensions);
}








