#include <iostream>
#include "gtest/gtest.h"

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
protected:

    FooTest(){}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(FooTest,TESTDATASAVED){}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
