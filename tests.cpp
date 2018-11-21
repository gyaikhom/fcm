#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "fcm.h"

using namespace Eigen;
using namespace std;

namespace {
    TEST(FCMTest, TestSetup) {
        EXPECT_EQ(1,1);
    }

    TEST(FCMTest, TestFCMConstuctor) {
        FCM *fcm;
        fcm = new FCM(2,0.5);
        EXPECT_EQ(NULL, fcm->get_data());
        delete fcm;
    }

    TEST(FCMTest, TestFCMSetdata) {
        FCM *fcm;
        fcm = new FCM(2, 0.5);
        MatrixXf* data;
        data = new MatrixXf;
        data->resize(4,3);
        (*data) <<  1.0, 1.2, 0.9,
                    5.9, 5.1, 5.6,
                    20.2, 20.4, 21.5,
                    50.0, 50.1, 50.2;
        fcm->set_data(data);
        delete fcm;
        EXPECT_EQ(1,1);
    }

    TEST(FCMTest, TestFCMUpdateMembership) {
        FCM *fcm;
        fcm = new FCM(2, 0.5);
        MatrixXf* data;
        data = new MatrixXf;
        data->resize(4,3);
        (*data) <<  1.0, 1.2, 0.9,
                    5.9, 5.1, 5.6,
                    20.2, 20.4, 21.5,
                    50.0, 50.1, 50.2;
        fcm->set_data(data);
        fcm->set_num_clusters(4);
        fcm->update_membership();
//        cout << "membership: \n"<< *(fcm->get_membership()) << endl;
//        cout << "cluster center: \n"<< *(fcm->get_cluster_center()) << endl;
        delete fcm;
        EXPECT_EQ(1,1);
    }

    TEST(FCMTest, TestFCMComputeCenters) {
        FCM *fcm;
        fcm = new FCM(2, 0.5);
        MatrixXf* data;
        data = new MatrixXf;
        data->resize(4,3);
        (*data) <<  1.0, 1.2, 0.9,
                    5.9, 5.1, 5.6,
                    20.2, 20.4, 21.5,
                    50.0, 50.1, 50.2;
        fcm->set_data(data);
        fcm->set_num_clusters(4);
        MatrixXf* membership = new MatrixXf;
        membership->resize(data->rows(), 4);
        (*membership) << 1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1;
        fcm->set_membership(membership);
        fcm->compute_centers();
        EXPECT_EQ((*(fcm->get_cluster_center()))(0,0), (*data)(0,0));
        EXPECT_EQ((*(fcm->get_cluster_center()))(1,1), (*data)(1,1));
        EXPECT_EQ((*(fcm->get_cluster_center()))(2,2), (*data)(2,2));
        delete fcm;
    }

    TEST(FCMTest, TestFCMNewdata) {
        FCM *fcm;
        fcm = new FCM(2, 0.5);
        MatrixXf* data;
        data = new MatrixXf;
        data->resize(4,3);
        (*data) <<  1.0, 1.2, 0.9,
                    5.9, 5.1, 5.6,
                    20.2, 20.4, 21.5,
                    50.0, 50.1, 50.2;
        fcm->set_data(data);
        fcm->set_num_clusters(4);
        MatrixXf* membership = new MatrixXf;
        membership->resize(data->rows(), 4);
        (*membership) << 1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1;
        fcm->set_membership(membership);
        fcm->compute_centers();
        MatrixXf* data2;
        data2 = new MatrixXf;
        data2->resize(4,3);
        (*data2) <<  1.0, 1.2, 0.9,
                    5.9, 5.1, 5.6,
                    20.2, 20.4, 21.5,
                    50.0, 50.1, 50.2;
        fcm->set_data(data2);
        fcm->update_membership();
        cout << "membership: \n"<< *(fcm->get_membership()) << endl;
        delete fcm;
    }



}// namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
