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

    TEST(FCMTest, TestFCMComputeMembership) {
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
        delete fcm;
        EXPECT_EQ(1,1);
    }

}// namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
