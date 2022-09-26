#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cycle.h"
#include "MyVector.h"
#include "fibonacci.h"

using testing::Eq;
/*
TEST(test_1, max){
    MyVector<int> v;

    EXPECT_THROW(v.max(), EmptyVector);

    v.push_back(4); v.push_back(33);
    v.push_back(14); v.push_back(18);
    v.push_back(45); v.push_back(33);
    EXPECT_EQ(45,v.max());

    v.push_back(85);
    EXPECT_EQ(85,v.max());

    for (int i = 0; i < 4; i++)
    {
        int vsize[] = {1000,10000,50000,100000};
        v.fillVector(vsize[i]);
        ticks tstart, tend;
        unsigned t;
        tstart = getticks();
        v.max();
        tend = getticks();
        t = ( (int)tend - (int)tstart )/1000;
        cout << "(vmax(size 8)) t = " <<  t <<endl;
    }
}

TEST(test_1, hasDuplicates){
    MyVector<int> v;

    v.push_back(4); v.push_back(33);
    v.push_back(14); v.push_back(18);
    v.push_back(45);
    EXPECT_EQ(false,v.hasDuplicates());

    v.push_back(33);
    EXPECT_EQ(true,v.hasDuplicates());
    for (int i = 0; i < 4; i++)
    {
        int vsize[] = {1000,10000,50000,100000};
        v.fillVector(vsize[i]);
        ticks tstart, tend;
        unsigned t;
        tstart = getticks();
        v.hasDuplicates();
        tend = getticks();
        t = ( (int)tend - (int)tstart )/1000;
        cout << "(hasduplicate) t = " <<  t <<endl;
    }
}

*/
TEST(test_1, removeDuplicates){
    MyVector<int> v;

    v.push_back(4); v.push_back(33);
    v.push_back(14); v.push_back(18);
    v.push_back(45); v.push_back(10);

    v.removeDuplicates();
    vector<int> vx = v.getValues();
    EXPECT_EQ(6, vx.size());
    EXPECT_EQ(4, vx[0]);
    EXPECT_EQ(18, vx[3]);

    v.push_back(33); v.push_back(20);
    v.push_back(18);
    v.removeDuplicates();
    vx = v.getValues();
    EXPECT_EQ(7, vx.size());
    EXPECT_EQ(4, vx[0]);
    EXPECT_EQ(33, vx[1]);
    EXPECT_EQ(18, vx[3]);
    EXPECT_EQ(20, vx[6]);

    v.push_back(20); v.push_back(20);
    v.push_back(20); v.push_back(44);
    v.removeDuplicates();
    vx = v.getValues();
    EXPECT_EQ(8, vx.size());
    EXPECT_EQ(4, vx[0]);
    EXPECT_EQ(18, vx[3]);
    EXPECT_EQ(20, vx[6]);
    EXPECT_EQ(44, vx[7]);
}

/*
TEST(test_2, fibonacci_1){
    EXPECT_EQ(0, fibonacci_1(0));
    EXPECT_EQ(1, fibonacci_1(1));
    EXPECT_EQ(1, fibonacci_1(2));
    EXPECT_EQ(13, fibonacci_1(7));
    EXPECT_EQ(144, fibonacci_1(12));
    EXPECT_EQ(2584, fibonacci_1(18));
}


TEST(test_2, fibonacci_2){

    ticks tstart, tend;
    unsigned t;
    tstart = getticks();
    EXPECT_EQ(13, fibonacci_2(7));
    tend = getticks();
    t = ( (int)tend - (int)tstart )/1000;
    cout << "t = " << t << endl;
    EXPECT_EQ(144, fibonacci_2(12));
    EXPECT_EQ(2584, fibonacci_2(18));
}
*/