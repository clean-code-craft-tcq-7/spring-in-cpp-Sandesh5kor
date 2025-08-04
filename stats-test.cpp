#include "stats.h"

#include "gtest/gtest.h"
#include <cmath>

TEST(Statistics, ReportsAverageMinMax) {
    auto computedStats = Statistics::ComputeStatistics({1.5, 8.9, 3.2, 4.5});
    float epsilon = 0.001;
    EXPECT_LT(std::abs(computedStats.average - 4.525), epsilon);
    EXPECT_LT(std::abs(computedStats.max - 8.9), epsilon);
    EXPECT_LT(std::abs(computedStats.min - 1.5), epsilon);
}

TEST(Statistics, AverageNaNForEmpty) {
    auto computedStats = Statistics::ComputeStatistics({});
    EXPECT_TRUE(std::isnan(computedStats.average));
    EXPECT_TRUE(std::isnan(computedStats.max));
    EXPECT_TRUE(std::isnan(computedStats.min));
}

TEST(Statistics, NaNInInputIsIgnored) {
    auto computedStats = Statistics::ComputeStatistics({NAN, 1.0, 2.0});
    float epsilon = 0.001;
    EXPECT_LT(std::abs(computedStats.average - 1.5), epsilon);
    EXPECT_LT(std::abs(computedStats.max - 2.0), epsilon);
    EXPECT_LT(std::abs(computedStats.min - 1.0), epsilon);
}

TEST(Statistics, SingleElement) {
    auto computedStats = Statistics::ComputeStatistics({42.0});
    EXPECT_FLOAT_EQ(computedStats.average, 42.0);
    EXPECT_FLOAT_EQ(computedStats.max, 42.0);
    EXPECT_FLOAT_EQ(computedStats.min, 42.0);
}

TEST(Statistics, AllNaNInput) {
    auto computedStats = Statistics::ComputeStatistics({NAN, NAN});
    EXPECT_TRUE(std::isnan(computedStats.average));
    EXPECT_TRUE(std::isnan(computedStats.max));
    EXPECT_TRUE(std::isnan(computedStats.min));
}

TEST(Statistics, NegativeAndLargeValues) {
    auto computedStats = Statistics::ComputeStatistics({-1.0, 0.0, 1000.0, 999.9});
    EXPECT_TRUE(std::isnan(computedStats.average));
    EXPECT_TRUE(std::isnan(computedStats.max));
    EXPECT_TRUE(std::isnan(computedStats.min));
}

TEST(Statistics, InputWithNaNAndValidNumbers) {
    auto computedStats = Statistics::ComputeStatistics({NAN, 2.0, NAN, 4.0});
    float epsilon = 0.001;
    EXPECT_LT(std::abs(computedStats.average - 3.0), epsilon);
    EXPECT_LT(std::abs(computedStats.max - 4.0), epsilon);
    EXPECT_LT(std::abs(computedStats.min - 2.0), epsilon);
}