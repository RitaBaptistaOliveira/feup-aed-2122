#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "funSearchProblem.h"

using testing::Eq;
/*
TEST(test, facingsun){
    FunSearchProblem r;
    vector<int> v1;
    vector<int> v2= {4,33,14,18,45};
    vector<int> v3 = {1,2,3,4,5};
    vector<int> v4 = {5,4,3,2,1};
    EXPECT_EQ(0,r.facingSun(v1));
    EXPECT_EQ(3,r.facingSun(v2));
    EXPECT_EQ(5,r.facingSun(v3));
    EXPECT_EQ(1,r.facingSun(v4));

}
*/
TEST(test, squareR){
    FunSearchProblem r;
    int num = 1;
    EXPECT_EQ(1,r.squareR(num));
    EXPECT_EQ(4,r.squareR(21));
}
/*
TEST(test, missingvalue){

}

TEST(test, minPages){

}
*/