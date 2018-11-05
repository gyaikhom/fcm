#include <gtest/gtest.h>

namespace {
    TEST(FCMTest, FCMTestClus) {
    EXPECT_EQ(1,1); 
    }
}// namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
