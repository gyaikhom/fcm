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

//    TEST(FCMTest, TestFCMComputeMembership) {
//        FCM *fcm;
//        fcm = new FCM(2, 0.5);
//        MatrixXf* data;
//        data = new MatrixXf;
//        data->resize(4,3);
//        (*data) <<  1.0, 1.2, 0.9,
//                    5.9, 5.1, 5.6,
//                    20.2, 20.4, 21.5,
//                    50.0, 50.1, 50.2;
//        fcm->set_data(data);
//        fcm->update_membership();
//        delete fcm;
//        EXPECT_EQ(1,1);
//    }


//    TEST(FCMTest, TestFCMSetdata) {
//        MatrixXf data;
//        data.resize(4,3);
//        data << 1.0, 1.2, 0.9,
//                5.9, 5.1, 5.6,
//                20.2, 20.4, 21.5,
//                50.0, 50.1, 50.2;
//        cout << "data: "<<endl << data << endl;
//        FCM fcm;
//        fcm.set_data(&data);
//        EXPECT_EQ(1,1);
//    }

//    TEST(FCMTest, TestFCMComputeMembership) {
//        MatrixXf *data;
//        data = new MatrixXf;
//        data->resize(4,3);
//        (*data) << 1.0, 1.2, 0.9,
//                5.9, 5.1, 5.6,
//                20.2, 20.4, 21.5,
//                50.0, 50.1, 50.2;
//        cout << "TEST data: "<< endl << (*data) << endl;
//        FCM *fcm;
//        fcm = new FCM;
//        cout << "TEST m_data (should be NULL): " << fcm->m_data << endl;
//        cout << "TEST m_data is null? should be true " << (fcm->m_data == NULL) << endl;
//    }



}// namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
