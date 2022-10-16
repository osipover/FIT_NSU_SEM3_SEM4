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
    ASSERT_THROW({BigInt v("123error456");}, invalid_argument);
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

class BigIntComparison : public ::testing::Test{
public:
    BigInt* argument[6];
protected:
    void SetUp(){
        argument[0] = new BigInt("12345678987654321");
        argument[1] = new BigInt("1234163271623473642341223443");
        argument[2] = new BigInt("12345678987654322");
        argument[3] = new BigInt("-12345678987654321");
        argument[4] = new BigInt("-1234163271623473642341223443");
        argument[5] = new BigInt("-98765432123456789");
    }
    void TearDown(){
        delete argument[0];
        delete argument[1];
        delete argument[2];
        delete argument[3];
        delete argument[4];
        delete argument[5];
    }
};

TEST_F(BigIntComparison, TestOperatorEqually){
    ASSERT_EQ(*argument[0] == *argument[3], false);
    ASSERT_EQ(*argument[0] == *argument[1], false);
    ASSERT_EQ(*argument[0] == *argument[2], false);
    ASSERT_EQ(*argument[0] == *argument[0], true);
    ASSERT_EQ(*argument[3] == *argument[3], true);
}

TEST_F(BigIntComparison, TestOperatorNotEqually){
    ASSERT_EQ(*argument[0] != *argument[3], true);
    ASSERT_EQ(*argument[0] != *argument[1], true);
    ASSERT_EQ(*argument[0] != *argument[2], true);
    ASSERT_EQ(*argument[0] != *argument[0], false);
    ASSERT_EQ(*argument[3] != *argument[3], false);
}

TEST_F(BigIntComparison, TestOperatorLess){
    ASSERT_EQ(*argument[0] < *argument[0], false);
    ASSERT_EQ(*argument[3] < *argument[3], false);

    ASSERT_EQ(*argument[3] < *argument[0], true);
    ASSERT_EQ(*argument[0] < *argument[3], false);

    ASSERT_EQ(*argument[0] < *argument[1], true);
    ASSERT_EQ(*argument[1] < *argument[0], false);
    ASSERT_EQ(*argument[0] < *argument[2], true);
    ASSERT_EQ(*argument[2] < *argument[0], false);

    ASSERT_EQ(*argument[3] < *argument[4], false);
    ASSERT_EQ(*argument[4] < *argument[3], true);
    ASSERT_EQ(*argument[3] < *argument[5], false);
    ASSERT_EQ(*argument[5] < *argument[3], true);
}

TEST_F(BigIntComparison, TestOperatorLessOrEqually){
    ASSERT_EQ(*argument[0] <= *argument[0], true);
    ASSERT_EQ(*argument[3] <= *argument[3], true);

    ASSERT_EQ(*argument[3] <= *argument[0], true);
    ASSERT_EQ(*argument[0] <= *argument[3], false);

    ASSERT_EQ(*argument[0] <= *argument[1], true);
    ASSERT_EQ(*argument[1] <= *argument[0], false);
    ASSERT_EQ(*argument[0] <= *argument[2], true);
    ASSERT_EQ(*argument[2] <= *argument[0], false);

    ASSERT_EQ(*argument[3] <= *argument[4], false);
    ASSERT_EQ(*argument[4] <= *argument[3], true);
    ASSERT_EQ(*argument[3] <= *argument[5], false);
    ASSERT_EQ(*argument[5] <= *argument[3], true);
}

TEST_F(BigIntComparison, TestOperatorGreater){
    ASSERT_EQ(*argument[0] > *argument[0], false);
    ASSERT_EQ(*argument[3] > *argument[3], false);

    ASSERT_EQ(*argument[3] > *argument[0], false);
    ASSERT_EQ(*argument[0] > *argument[3], true);

    ASSERT_EQ(*argument[0] > *argument[1], false);
    ASSERT_EQ(*argument[1] > *argument[0], true);
    ASSERT_EQ(*argument[0] > *argument[2], false);
    ASSERT_EQ(*argument[2] > *argument[0], true);

    ASSERT_EQ(*argument[3] > *argument[4], true);
    ASSERT_EQ(*argument[4] > *argument[3], false);
    ASSERT_EQ(*argument[3] > *argument[5], true);
    ASSERT_EQ(*argument[5] > *argument[3], false);
}

TEST_F(BigIntComparison, TestOperatorGreaterOrEqual){
    ASSERT_EQ(*argument[0] >= *argument[0], true);
    ASSERT_EQ(*argument[3] >= *argument[3], true);

    ASSERT_EQ(*argument[3] >= *argument[0], false);
    ASSERT_EQ(*argument[0] >= *argument[3], true);

    ASSERT_EQ(*argument[0] >= *argument[1], false);
    ASSERT_EQ(*argument[1] >= *argument[0], true);
    ASSERT_EQ(*argument[0] >= *argument[2], false);
    ASSERT_EQ(*argument[2] >= *argument[0], true);

    ASSERT_EQ(*argument[3] >= *argument[4], true);
    ASSERT_EQ(*argument[4] >= *argument[3], false);
    ASSERT_EQ(*argument[3] >= *argument[5], true);
    ASSERT_EQ(*argument[5] >= *argument[3], false);
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

TEST_P(BigIntOperatorSum, TestSumAssignment){
    BigIntTestArguments v = GetParam();
    v.firstArg += v.secondArg;
    ASSERT_EQ(v.result, (string)v.firstArg);
}

TEST_P(BigIntOperatorSum, TestOperatorSum){
    BigIntTestArguments v = GetParam();
    ASSERT_EQ(v.result, (string)(v.firstArg + v.secondArg));
}

class BigIntOperatorDiff : public ::testing:: TestWithParam<BigIntTestArguments>{};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        BigIntOperatorDiff,
        ::testing::Values(
                BigIntTestArguments(BigInt("82837473481334132371371"), BigInt("1631266371726316929"), "82835842214962406054442"),
                BigIntTestArguments(BigInt("11231726"), BigInt("1461783641982736481738412"), "-1461783641982736470506686"),
                BigIntTestArguments(BigInt("52362534"), BigInt("-723862"), "53086396"),
                BigIntTestArguments(BigInt("-123456789"), BigInt("987654321"), "-1111111110"),
                BigIntTestArguments(BigInt("-123454321"), BigInt("-12345"), "-123441976"),
                BigIntTestArguments(BigInt("-12345"), BigInt("-123454321"), "123441976"),
                BigIntTestArguments(BigInt("999999999999999999999"), BigInt("999999999999000000000"), "999999999"),
                BigIntTestArguments(BigInt("-1"), BigInt("-1"), "0"),
                BigIntTestArguments(BigInt("-0"), BigInt("-0"), "0"))
);

TEST_P(BigIntOperatorDiff, TestDiffAssignment){
    BigIntTestArguments v = GetParam();
    v.firstArg -= v.secondArg;
    ASSERT_EQ(v.result, (string)v.firstArg);
}

TEST_P(BigIntOperatorDiff, TestOperatorDiff){
    BigIntTestArguments v = GetParam();
    ASSERT_EQ(v.result, (string)(v.firstArg - v.secondArg));
}

class BigIntOperatorMul : public ::testing:: TestWithParam<BigIntTestArguments>{};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        BigIntOperatorMul,
        ::testing::Values(
                BigIntTestArguments(BigInt("1234651783"), BigInt("1832941736434817342"), "2263044783024363294579620786"),
                BigIntTestArguments(BigInt("1832941736434817342"), BigInt("1234651783"), "2263044783024363294579620786"),
                BigIntTestArguments(BigInt("-12345"), BigInt("12345"), "-152399025"),
                BigIntTestArguments(BigInt("12345"), BigInt("-12345"), "-152399025"),
                BigIntTestArguments(BigInt("-12345"), BigInt("-12345"), "152399025"),
                BigIntTestArguments(BigInt("19837491837471263548172634"), BigInt("0"), "0"))
);

TEST_P(BigIntOperatorMul, TestMulAssignment){
    BigIntTestArguments v = GetParam();
    v.firstArg *= v.secondArg;
    ASSERT_EQ(v.result, (string)v.firstArg);
}

TEST_P(BigIntOperatorMul, TestOperatorMul){
    BigIntTestArguments v = GetParam();
    ASSERT_EQ(v.result, (string)(v.firstArg * v.secondArg));
}

class BigIntOperatorDiv : public ::testing:: TestWithParam<BigIntTestArguments>{};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        BigIntOperatorDiv,
        ::testing::Values(
                BigIntTestArguments(BigInt("1274617623764374237478236426"), BigInt("827384728374234"), "1540538010979"),
                BigIntTestArguments(BigInt("1274617623764374237478236426"), BigInt("2"), "637308811882187118739118213"),
                BigIntTestArguments(BigInt("2"), BigInt("1274617623764374237478236426"), "0"),
                BigIntTestArguments(BigInt("0"), BigInt("1274617623764374237478236426"), "0"),
                BigIntTestArguments(BigInt("1274617623764374237478236426"), BigInt("-827384728374234"), "-1540538010979"),
                BigIntTestArguments(BigInt("-1274617623764374237478236426"), BigInt("827384728374234"), "-1540538010979"),
                BigIntTestArguments(BigInt("-1274617623764374237478236426"), BigInt("-827384728374234"), "1540538010979"))
);

TEST_P(BigIntOperatorDiv, TestDivAssignment){
    BigIntTestArguments v = GetParam();
    v.firstArg /= v.secondArg;
    ASSERT_EQ(v.result, (string)v.firstArg);
}

TEST_P(BigIntOperatorDiv, TestOperatorDiv){
    BigIntTestArguments v = GetParam();
    ASSERT_EQ(v.result, (string)(v.firstArg / v.secondArg));
}

TEST(BigIntOperatorDiv, TestDivByZero){
    BigInt v("18741872381273");
    BigInt zero("0");
    ASSERT_THROW(v / zero, invalid_argument);
}

class BigIntOperatorMod : public ::testing:: TestWithParam<BigIntTestArguments>{};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        BigIntOperatorMod,
        ::testing::Values(
                BigIntTestArguments(BigInt("1274617623764374237478236426"),BigInt("827384728374234"), "331606765521340"),
                BigIntTestArguments(BigInt("1274617623764374237478236426"),BigInt("2"), "0"),
                BigIntTestArguments(BigInt("1274617623764374237478236426"),BigInt("10"), "6"),
                BigIntTestArguments(BigInt("1274617623764374237478236426"),BigInt("10000000000000000000000000000"), "1274617623764374237478236426"),
                BigIntTestArguments(BigInt("1274617623764374237478236426"),BigInt("-827384728374234"), "331606765521340"),
                BigIntTestArguments(BigInt("-1274617623764374237478236426"),BigInt("827384728374234"), "331606765521340"),
                BigIntTestArguments(BigInt("-1274617623764374237478236426"),BigInt("-827384728374234"), "331606765521340"))
);

TEST_P(BigIntOperatorMod, TestModAssignment){
    BigIntTestArguments v = GetParam();
    v.firstArg %= v.secondArg;
    ASSERT_EQ(v.result, (string)v.firstArg);
}

TEST_P(BigIntOperatorMod, TestOperatorMod){
    BigIntTestArguments v = GetParam();
    ASSERT_EQ(v.result, (string)(v.firstArg % v.secondArg));
}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
