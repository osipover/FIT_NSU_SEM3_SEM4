#include <iostream>
#include <utility>
#include "BigInt.h"
#include <gtest/gtest.h>

class BigIntTestArguments{
public:
    BigIntTestArguments(BigInt firstArg, string result):
        firstArg(firstArg), result(std::move(result)){}
    BigIntTestArguments(BigInt firstArg, BigInt secondArg, string result):
        firstArg(firstArg), secondArg(secondArg), result(std::move(result)){}
    BigInt firstArg;
    BigInt secondArg;
    string result;
};

TEST(BigIntTest, TestConstructorInt){
    BigInt v1(0);
    BigInt v2(-999999999);
    BigInt v3(2147483647);
    BigInt v4(-2147483648);
    ASSERT_EQ("0", (string)v1);
    ASSERT_EQ("-999999999", (string)v2);
    ASSERT_EQ("2147483647", (string)v3);
    ASSERT_EQ("-2147483648", (string)v4);
};

TEST(BigIntTest, TestConstructorString){
    BigInt v1("12345678987654321");
    BigInt v2("-12345678987654321");
    BigInt v3("00000000000000000001");
    BigInt v4("-00000000");
    ASSERT_EQ("12345678987654321", (string)v1);
    ASSERT_EQ("-12345678987654321", (string)v2);
    ASSERT_EQ("1", (string)v3);
    ASSERT_EQ("0", (string)v4);
}

TEST(BigIntTest, TestAssignment){
    BigInt v1(987654321);
    BigInt v2("999999999999999999");
    v1 = v2;
    v2 = v1;
    ASSERT_EQ(v1, v2);
}

TEST(BigIntTest, TestSize){
    BigInt v1(12345);
    BigInt v2("111111111222222222333333333");
    ASSERT_EQ(4, v1.size());
    ASSERT_EQ(12, v2.size());
}

TEST(BigIntTest, TestIntConversion){
    BigInt v1(-12345);
    BigInt v2(2147483647);
    ASSERT_EQ(-12345, (int)v1);
    ASSERT_EQ(2147483647, (int)v2);
}

TEST(BigIntTest, TestBinNOT){
    BigInt v1(2147483647);
    BigInt v2("-2147483648");
    BigInt v3(0);
    ASSERT_EQ("-2147483648", (string)~v1);
    ASSERT_EQ("2147483647", (string)~v2);
    ASSERT_EQ("-1", (string)~v3);
}

class BigIntIncrement : public ::testing::TestWithParam<BigIntTestArguments>{};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        BigIntIncrement,
        ::testing::Values(
              BigIntTestArguments(BigInt(-1), "0"),
              BigIntTestArguments(BigInt(999999999), "1000000000"),
              BigIntTestArguments(BigInt(-1000000000), "-999999999"),
              BigIntTestArguments(BigInt("999999999999999999"), "1000000000000000000"))
);

TEST_P(BigIntIncrement, TestPostfixIncrement){
    BigIntTestArguments v = GetParam();
    v.firstArg++;
    ASSERT_EQ(v.result, (string) v.firstArg);
}

TEST_P(BigIntIncrement, TestPrefixIncrement){
    BigIntTestArguments v = GetParam();
    ++v.firstArg;
    ASSERT_EQ(v.result, (string) v.firstArg);
}

class BigIntDecrement : public ::testing::TestWithParam<BigIntTestArguments>{};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        BigIntDecrement,
        ::testing::Values(
                BigIntTestArguments(BigInt("0"), "-1"),
                BigIntTestArguments(BigInt(1000000000), "999999999"),
                BigIntTestArguments(BigInt(-999999999), "-1000000000"),
                BigIntTestArguments(BigInt("1000000000000000000"), "999999999999999999"))
);

TEST_P(BigIntDecrement, TestPostfixDecrement){
    BigIntTestArguments v = GetParam();
    v.firstArg--;
    ASSERT_EQ(v.result, (string)v.firstArg);
}

TEST_P(BigIntDecrement, TestPrefixDecrement){
    BigIntTestArguments v = GetParam();
    --v.firstArg;
    ASSERT_EQ(v.result, (string)v.firstArg);
}

class BigIntOperatorSum : public ::testing::TestWithParam<BigIntTestArguments>{};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        BigIntOperatorSum,
        ::testing::Values(
            BigIntTestArguments(BigInt("123476183746823764123"), BigInt("7234628471282378913443"), "7358104655029202677566"),
            BigIntTestArguments(BigInt("111111111"), BigInt("-222222222"), "-111111111"),
            BigIntTestArguments(BigInt("222222222"), BigInt("-111111111"), "111111111"),
            BigIntTestArguments(BigInt("-111111111"), BigInt("222222222"), "111111111"),
            BigIntTestArguments(BigInt("-222222222"), BigInt("111111111"), "-111111111"),
            BigIntTestArguments(BigInt("-555555555"), BigInt("-1000000000000"), "-1000555555555"),
            BigIntTestArguments(BigInt("-0"), BigInt("-0"), "0"))

);

TEST_P(BigIntOperatorSum, TestSumAsigment){
    BigIntTestArguments v = GetParam();
    v.firstArg += v.secondArg;
    ASSERT_EQ(v.result, (string)v.firstArg);
}

TEST_P(BigIntOperatorSum, TestOperatorSum){
    BigIntTestArguments v = GetParam();
    ASSERT_EQ(v.result, (string)(v.firstArg + v.secondArg));
}



int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
