// Standard Libraries
#include <cmath>
#include <iostream>

// Project headers
#include "experiment.hpp"
#include "csv_reader.hpp"

// ===========================================
// helper function to determine T/F for the tests
bool approximatelyEqual(double actual, double expected)
{
    if (std::abs(actual - expected) < 0.00001)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// ===========================================

bool userRecordsEqual(
    const UserRecord& actual,
    const UserRecord& expected)
{
    return actual.userId == expected.userId &&
           actual.device == expected.device &&
           actual.variant == expected.variant &&
           actual.purchased == expected.purchased &&
           approximatelyEqual(
               actual.orderPrice,
               expected.orderPrice);
}

// ===========================================

// test conversionRate
bool testConversionRate()
{
    // test 1
    ExperimentGroup control1{1000, 100, 50000.0};
    double actual1 {control1.conversionRate()};
    double expected1 {0.1};
    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }

    // test 2 (no users)
    ExperimentGroup control2{0, 0, 0.0};
    double actual2 {control2.conversionRate()};
    double expected2 {0.0};
    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }
    
    // test 3 (no conversions)
    ExperimentGroup control3{1000, 0, 50000.0};
    double actual3 {control3.conversionRate()};
    double expected3 {0.0};
    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }

    // test 4 (conversions = users)
    ExperimentGroup control4{1000, 1000, 50000.0};
    double actual4 {control4.conversionRate()};
    double expected4 {1.0};
    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }

    return true;
}

// ===========================================

// test absolute lift
bool testAbsoluteLift()
{
    // test 1 (general)
    ExperimentGroup control1{1000, 100, 50000.0};
    ExperimentGroup treatment1{1000, 120, 55000.0};
    Experiment Test1{control1, treatment1};
    double actual1 {Test1.absoluteLift()};
    double expected1 {0.02};
    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }

    // test 2 (control = treatment)
    ExperimentGroup control2{1000, 100, 50000.0};
    ExperimentGroup treatment2{1000, 100, 55000.0};
    Experiment Test2{control2, treatment2};
    double actual2 {Test2.absoluteLift()};
    double expected2 {0.0};
    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }

    // test 3 (control > treatment)
    ExperimentGroup control3{1000, 150, 50000.0};
    ExperimentGroup treatment3{1000, 120, 55000.0};
    Experiment Test3{control3, treatment3};
    double actual3 {Test3.absoluteLift()};
    double expected3 {-0.03};
    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }

    // test 4 (0 users in a group)
    ExperimentGroup control4{0, 0, 0.0};
    ExperimentGroup treatment4{1000, 120, 55000.0};
    Experiment Test4{control4, treatment4};
    double actual4 {Test4.absoluteLift()};
    double expected4 {0.0};
    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }

    return true;
}

// ===========================================

// test relative lift
bool testRelativeLift()
{
    // test 1 (general)
    ExperimentGroup control1{1000, 100, 50000.0};
    ExperimentGroup treatment1{1000, 120, 55000.0};
    Experiment Test1{control1, treatment1};
    double actual1 {Test1.relativeLift()};
    double expected1 {0.2};
    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }

    // test 2 (control = treatment)
    ExperimentGroup control2{1000, 100, 50000.0};
    ExperimentGroup treatment2{1000, 100, 55000.0};
    Experiment Test2{control2, treatment2};
    double actual2 {Test2.relativeLift()};
    double expected2 {0.0};
    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }

    // test 3 (control > treatment)
    ExperimentGroup control3{1000, 150, 50000.0};
    ExperimentGroup treatment3{1000, 120, 55000.0};
    Experiment Test3{control3, treatment3};
    double actual3 {Test3.relativeLift()};
    double expected3 {-0.2};
    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }

    // test 4 (0 users in a group)
    ExperimentGroup control4{0, 0, 0.0};
    ExperimentGroup treatment4{1000, 120, 55000.0};
    Experiment Test4{control4, treatment4};
    double actual4 {Test4.relativeLift()};
    double expected4 {0.0};
    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }

    return true;
}

// ===========================================

// test revenue per user
bool testRevPerUser()
{
    // test 1 (general)
    ExperimentGroup control1{1000, 100, 50000.0};
    double actual1 {control1.revenuePerUser()};
    double expected1 {50};
    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }

    // test 2 (no users)
    ExperimentGroup control2{0, 0, 0.0};
    double actual2 {control2.revenuePerUser()};
    double expected2 {0.0};
    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }

    // test 3 (no revenue)
    ExperimentGroup control3{1000, 120, 0.0};
    double actual3 {control3.revenuePerUser()};
    double expected3 {0.0};
    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }
    return true;
}

// ===========================================

// test absolute revenue lift
bool testAbsRevLift()
{
    // test 1 (general)
    ExperimentGroup control1{1000, 100, 50000.0};
    ExperimentGroup treatment1{1000, 120, 55000.0};
    Experiment Test1{control1, treatment1};
    double actual1 {Test1.absoluteRevenueLift()};
    double expected1 {5.0};
    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }

    // test 2 (control = treatment)
    ExperimentGroup control2{1000, 100, 55000.0};
    ExperimentGroup treatment2{1000, 100, 55000.0};
    Experiment Test2{control2, treatment2};
    double actual2 {Test2.absoluteRevenueLift()};
    double expected2 {0.0};
    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }

    // test 3 (control > treatment)
    ExperimentGroup control3{1000, 150, 60000.0};
    ExperimentGroup treatment3{1000, 120, 55000.0};
    Experiment Test3{control3, treatment3};
    double actual3 {Test3.absoluteRevenueLift()};
    double expected3 {-5.0};
    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }

    // test 4 (0 users in a group)
    ExperimentGroup control4{0, 0, 0.0};
    ExperimentGroup treatment4{1000, 120, 55000.0};
    Experiment Test4{control4, treatment4};
    double actual4 {Test4.absoluteRevenueLift()};
    double expected4 {0.0};
    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }

    // test 5 (0 revenue in a group)
    ExperimentGroup control5{1000, 50, 0.0};
    ExperimentGroup treatment5{1000, 120, 55000.0};
    Experiment Test5{control5, treatment5};
    double actual5 {Test5.absoluteRevenueLift()};
    double expected5 {55.0};
    if (!approximatelyEqual(actual5, expected5))
    {
        return false;
    }
    return true;
}

// ===========================================

// test relative revenue lift
bool testRelRevLift()
{
    // test 1 (general)
    ExperimentGroup control1{1000, 100, 50000.0};
    ExperimentGroup treatment1{1000, 120, 55000.0};
    Experiment Test1{control1, treatment1};
    double actual1 {Test1.relativeRevenueLift()};
    double expected1 {0.1};
    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }

    // test 2 (control = treatment)
    ExperimentGroup control2{1000, 100, 55000.0};
    ExperimentGroup treatment2{1000, 100, 55000.0};
    Experiment Test2{control2, treatment2};
    double actual2 {Test2.relativeRevenueLift()};
    double expected2 {0.0};
    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }

    // test 3 (control > treatment)
    ExperimentGroup control3{1000, 150, 50000.0};
    ExperimentGroup treatment3{1000, 120, 45000.0};
    Experiment Test3{control3, treatment3};
    double actual3 {Test3.relativeRevenueLift()};
    double expected3 {-0.1};
    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }

    // test 4 (0 users in a group)
    ExperimentGroup control4{0, 0, 0.0};
    ExperimentGroup treatment4{1000, 120, 55000.0};
    Experiment Test4{control4, treatment4};
    double actual4 {Test4.relativeRevenueLift()};
    double expected4 {0.0};
    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }

    // test 5 (0 revenue in a group)
    ExperimentGroup control5{1000, 50, 0.0};
    ExperimentGroup treatment5{1000, 120, 55000.0};
    Experiment Test5{control5, treatment5};
    double actual5 {Test5.relativeRevenueLift()};
    double expected5 {0.0};
    if (!approximatelyEqual(actual5, expected5))
    {
        return false;
    }
    return true;
}

// ===========================================

bool testLoadUsersFromCSV()
{
    auto actualList =
        loadUsersFromCsv("cpp/tests/data/test_users.csv");

    std::vector<UserRecord> expectedList
    {
        {1, "Mobile", "A", 0, 0.0},
        {2, "Desktop", "B", 1, 49.99},
        {3, "Mobile", "B", 1, 39.50},
        {4, "Desktop", "A", 0, 0.0}
    };

    if (actualList.size() != expectedList.size())
    {
        return false;
    }

    for (std::size_t i = 0; i < actualList.size(); ++i)
    {
        if (!userRecordsEqual(actualList[i], expectedList[i]))
        {
            return false;
        }
    }

    return true;
}

// ===========================================

bool testCreateExperiment()
{
    std::vector<UserRecord> userList
    {
        {1, "Mobile", "A", 0, 0.0},
        {2, "Desktop", "B", 1, 49.99},
        {3, "Mobile", "B", 1, 39.50},
        {4, "Desktop", "A", 0, 0.0}
    };
    Experiment expectedExperiment
    {
        {2, 0, 0.0},
        {2, 2, 89.49}
    };
    Experiment actualExperiment =
        createExperiment(userList);
    if (
        expectedExperiment.control.users !=
        actualExperiment.control.users ||
        expectedExperiment.control.conversions !=
        actualExperiment.control.conversions ||
        !approximatelyEqual(
            expectedExperiment.control.revenue,
            actualExperiment.control.revenue) ||
        expectedExperiment.treatment.users !=
        actualExperiment.treatment.users ||
        expectedExperiment.treatment.conversions !=
        actualExperiment.treatment.conversions ||
        !approximatelyEqual(
            expectedExperiment.treatment.revenue,
            actualExperiment.treatment.revenue)
    )
    {
        return false;
    }
    return true;
}

// ===========================================

// test conversion standard error
bool testConversionStandardError()
{
    // test 1: general case
    // control = 10%, treatment = 11.5%
    Experiment test1
    {
        {10000, 1000, 0.0},
        {10000, 1150, 0.0}
    };

    double actual1 {test1.conversionStandardError()};
    double expected1 {0.0043792123};

    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }


    // test 2: equal conversion rates
    Experiment test2
    {
        {1000, 100, 0.0},
        {1000, 100, 0.0}
    };

    double actual2 {test2.conversionStandardError()};
    double expected2 {0.0134164079};

    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }


    // test 3: no conversions in either group
    Experiment test3
    {
        {1000, 0, 0.0},
        {1000, 0, 0.0}
    };

    double actual3 {test3.conversionStandardError()};
    double expected3 {0.0};

    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }


    // test 4: zero users in control
    Experiment test4
    {
        {0, 0, 0.0},
        {1000, 100, 0.0}
    };

    double actual4 {test4.conversionStandardError()};
    double expected4 {0.0};

    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }


    // test 5: different sample sizes
    Experiment test5
    {
        {5000, 500, 0.0},
        {8000, 960, 0.0}
    };

    double actual5 {test5.conversionStandardError()};
    double expected5 {0.0055856960};

    if (!approximatelyEqual(actual5, expected5))
    {
        return false;
    }

    return true;
}

// ===========================================

// test 95% conversion confidence interval
bool testConversionConfidenceInterval95()
{
    // test 1: positive lift
    Experiment test1
    {
        {10000, 1000, 0.0},
        {10000, 1150, 0.0}
    };

    ConfidenceInterval actual1 {
        test1.conversionConfidenceInterval95()
    };

    double expectedLower1 {0.006416744};
    double expectedUpper1 {0.023583256};

    if (!approximatelyEqual(actual1.lower, expectedLower1) ||
        !approximatelyEqual(actual1.upper, expectedUpper1))
    {
        return false;
    }


    // test 2: equal conversion rates
    // lift = 0, but uncertainty still exists
    Experiment test2
    {
        {1000, 100, 0.0},
        {1000, 100, 0.0}
    };

    ConfidenceInterval actual2 {
        test2.conversionConfidenceInterval95()
    };

    double expectedLower2 {-0.026296159};
    double expectedUpper2 {0.026296159};

    if (!approximatelyEqual(actual2.lower, expectedLower2) ||
        !approximatelyEqual(actual2.upper, expectedUpper2))
    {
        return false;
    }


    // test 3: negative lift
    Experiment test3
    {
        {1000, 150, 0.0},
        {1000, 120, 0.0}
    };

    ConfidenceInterval actual3 {
        test3.conversionConfidenceInterval95()
    };

    double expectedLower3 {-0.059924521};
    double expectedUpper3 {-0.000075479};

    if (!approximatelyEqual(actual3.lower, expectedLower3) ||
        !approximatelyEqual(actual3.upper, expectedUpper3))
    {
        return false;
    }


    // test 4: zero users in control
    Experiment test4
    {
        {0, 0, 0.0},
        {1000, 100, 0.0}
    };

    ConfidenceInterval actual4 {
        test4.conversionConfidenceInterval95()
    };

    if (!approximatelyEqual(actual4.lower, 0.0) ||
        !approximatelyEqual(actual4.upper, 0.0))
    {
        return false;
    }

    return true;
}

// ===========================================

// test pooled conversion standard error
bool testPooledConversionStandardError()
{
    // test 1: general positive-lift case
    Experiment test1
    {
        {10000, 1000, 0.0},
        {10000, 1150, 0.0}
    };

    double actual1 {test1.pooledConversionStandardError()};
    double expected1 {0.0043804965};

    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }


    // test 2: equal conversion rates
    Experiment test2
    {
        {1000, 100, 0.0},
        {1000, 100, 0.0}
    };

    double actual2 {test2.pooledConversionStandardError()};
    double expected2 {0.0134164079};

    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }


    // test 3: negative lift
    Experiment test3
    {
        {1000, 150, 0.0},
        {1000, 120, 0.0}
    };

    double actual3 {test3.pooledConversionStandardError()};
    double expected3 {0.0152823428};

    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }


    // test 4: different sample sizes
    Experiment test4
    {
        {5000, 500, 0.0},
        {8000, 960, 0.0}
    };

    double actual4 {test4.pooledConversionStandardError()};
    double expected4 {0.0056921674};

    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }


    // test 5: zero users in one group
    Experiment test5
    {
        {0, 0, 0.0},
        {1000, 100, 0.0}
    };

    double actual5 {test5.pooledConversionStandardError()};

    if (!approximatelyEqual(actual5, 0.0))
    {
        return false;
    }


    // test 6: zero conversions in both groups
    Experiment test6
    {
        {1000, 0, 0.0},
        {1000, 0, 0.0}
    };

    double actual6 {test6.pooledConversionStandardError()};

    if (!approximatelyEqual(actual6, 0.0))
    {
        return false;
    }

    return true;
}


// ===========================================

// test conversion z-score
bool testConversionZScore()
{
    // test 1: positive lift
    Experiment test1
    {
        {10000, 1000, 0.0},
        {10000, 1150, 0.0}
    };

    double actual1 {test1.conversionZScore()};
    double expected1 {3.4242693353};

    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }


    // test 2: identical conversion rates
    Experiment test2
    {
        {1000, 100, 0.0},
        {1000, 100, 0.0}
    };

    double actual2 {test2.conversionZScore()};
    double expected2 {0.0};

    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }


    // test 3: negative lift
    Experiment test3
    {
        {1000, 150, 0.0},
        {1000, 120, 0.0}
    };

    double actual3 {test3.conversionZScore()};
    double expected3 {-1.9630498076};

    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }


    // test 4: different sample sizes
    Experiment test4
    {
        {5000, 500, 0.0},
        {8000, 960, 0.0}
    };

    double actual4 {test4.conversionZScore()};
    double expected4 {3.5136001355};

    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }


    // test 5: zero users
    Experiment test5
    {
        {0, 0, 0.0},
        {1000, 100, 0.0}
    };

    double actual5 {test5.conversionZScore()};

    if (!approximatelyEqual(actual5, 0.0))
    {
        return false;
    }


    // test 6: pooled standard error = 0
    Experiment test6
    {
        {1000, 0, 0.0},
        {1000, 0, 0.0}
    };

    double actual6 {test6.conversionZScore()};

    if (!approximatelyEqual(actual6, 0.0))
    {
        return false;
    }

    return true;
}

// ===========================================

// test conversion p-value
bool testConversionPValue()
{
    // test 1: strong positive effect
    Experiment test1
    {
        {10000, 1000, 0.0},
        {10000, 1150, 0.0}
    };

    double actual1 {test1.conversionPValue()};
    double expected1 {0.0006164549};

    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }


    // test 2: identical conversion rates
    Experiment test2
    {
        {1000, 100, 0.0},
        {1000, 100, 0.0}
    };

    double actual2 {test2.conversionPValue()};
    double expected2 {1.0};

    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }


    // test 3: negative effect close to 5% threshold
    Experiment test3
    {
        {1000, 150, 0.0},
        {1000, 120, 0.0}
    };

    double actual3 {test3.conversionPValue()};
    double expected3 {0.0496403869};

    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }


    // test 4: non-significant difference
    Experiment test4
    {
        {1000, 100, 0.0},
        {1000, 110, 0.0}
    };

    double actual4 {test4.conversionPValue()};
    double expected4 {0.4657435879};

    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }

    return true;
}


// ===========================================

// test conversion significance
bool testIsConversionSignificant()
{
    // test 1: highly significant at alpha = 0.05
    Experiment test1
    {
        {10000, 1000, 0.0},
        {10000, 1150, 0.0}
    };

    if (!test1.isConversionSignificant(0.05))
    {
        return false;
    }


    // test 2: identical groups are not significant
    Experiment test2
    {
        {1000, 100, 0.0},
        {1000, 100, 0.0}
    };

    if (test2.isConversionSignificant(0.05))
    {
        return false;
    }


    // test 3: p ≈ 0.04964, significant at 0.05
    Experiment test3
    {
        {1000, 150, 0.0},
        {1000, 120, 0.0}
    };

    if (!test3.isConversionSignificant(0.05))
    {
        return false;
    }


    // test 4: same experiment is not significant at alpha = 0.01
    if (test3.isConversionSignificant(0.01))
    {
        return false;
    }


    // test 5: clearly non-significant
    Experiment test5
    {
        {1000, 100, 0.0},
        {1000, 110, 0.0}
    };

    if (test5.isConversionSignificant(0.05))
    {
        return false;
    }

    return true;
}

// ===========================================

// test filtering users by device
bool testFilterUsersByDevice()
{
    std::vector<UserRecord> users
    {
        {1, "Mobile", "A", 0, 0.0},
        {2, "Desktop", "B", 1, 49.99},
        {3, "Mobile", "B", 1, 39.50},
        {4, "Desktop", "A", 0, 0.0},
        {5, "Mobile", "A", 1, 29.99}
    };


    // test 1: filter Mobile users
    std::vector<UserRecord> mobileUsers {
        filterUsersByDevice(users, "Mobile")
    };

    if (mobileUsers.size() != 3)
    {
        return false;
    }

    if (mobileUsers[0].userId != 1 ||
        mobileUsers[1].userId != 3 ||
        mobileUsers[2].userId != 5)
    {
        return false;
    }

    for (const UserRecord& user : mobileUsers)
    {
        if (user.device != "Mobile")
        {
            return false;
        }
    }


    // test 2: filter Desktop users
    std::vector<UserRecord> desktopUsers {
        filterUsersByDevice(users, "Desktop")
    };

    if (desktopUsers.size() != 2)
    {
        return false;
    }

    if (desktopUsers[0].userId != 2 ||
        desktopUsers[1].userId != 4)
    {
        return false;
    }

    for (const UserRecord& user : desktopUsers)
    {
        if (user.device != "Desktop")
        {
            return false;
        }
    }


    // test 3: device does not exist
    std::vector<UserRecord> tabletUsers {
        filterUsersByDevice(users, "Tablet")
    };

    if (!tabletUsers.empty())
    {
        return false;
    }


    // test 4: empty input vector
    std::vector<UserRecord> emptyUsers {};

    std::vector<UserRecord> filteredEmpty {
        filterUsersByDevice(emptyUsers, "Mobile")
    };

    if (!filteredEmpty.empty())
    {
        return false;
    }

    return true;
}

// ===========================================

// test required sample size per group
bool testRequiredSampleSizePerGroup()
{
    // test 1: detect 10% -> 11%
    ExperimentPlan test1
    {
        0.10,
        0.11,
        0.05,
        0.80
    };

    int actual1 {
        requiredSampleSizePerGroup(test1)
    };

    int expected1 {14751};

    if (actual1 != expected1)
    {
        return false;
    }


    // test 2: larger effect should require fewer users
    // detect 10% -> 12%
    ExperimentPlan test2
    {
        0.10,
        0.12,
        0.05,
        0.80
    };

    int actual2 {
        requiredSampleSizePerGroup(test2)
    };

    int expected2 {3841};

    if (actual2 != expected2)
    {
        return false;
    }


    // test 3: same absolute effect at a higher baseline
    // detect 20% -> 21%
    ExperimentPlan test3
    {
        0.20,
        0.21,
        0.05,
        0.80
    };

    int actual3 {
        requiredSampleSizePerGroup(test3)
    };

    int expected3 {25583};

    if (actual3 != expected3)
    {
        return false;
    }


    // test 4: treatment can also be worse than baseline
    // 11% -> 10% should require the same sample size
    ExperimentPlan test4
    {
        0.11,
        0.10,
        0.05,
        0.80
    };

    int actual4 {
        requiredSampleSizePerGroup(test4)
    };

    int expected4 {14751};

    if (actual4 != expected4)
    {
        return false;
    }


    // test 5: invalid baseline rate
    ExperimentPlan test5
    {
        0.0,
        0.10,
        0.05,
        0.80
    };

    if (requiredSampleSizePerGroup(test5) != 0)
    {
        return false;
    }


    // test 6: invalid target rate
    ExperimentPlan test6
    {
        0.10,
        1.0,
        0.05,
        0.80
    };

    if (requiredSampleSizePerGroup(test6) != 0)
    {
        return false;
    }


    // test 7: baseline and target are identical
    ExperimentPlan test7
    {
        0.10,
        0.10,
        0.05,
        0.80
    };

    if (requiredSampleSizePerGroup(test7) != 0)
    {
        return false;
    }

    return true;
}

// ===========================================

// test statistical power calculation
bool testCalculatePower()
{
    // test 1: sample size previously calculated for ~80% power
    ExperimentPlan test1
    {
        0.10,
        0.11,
        0.05,
        0.80
    };

    double actual1 {
        calculatePower(test1, 14751)
    };

    double expected1 {0.80000557};

    if (!approximatelyEqual(actual1, expected1))
    {
        return false;
    }


    // test 2: smaller sample size should produce lower power
    ExperimentPlan test2
    {
        0.10,
        0.11,
        0.05,
        0.80
    };

    double actual2 {
        calculatePower(test2, 5000)
    };

    double expected2 {0.37108893};

    if (!approximatelyEqual(actual2, expected2))
    {
        return false;
    }


    // test 3: larger sample size should produce higher power
    ExperimentPlan test3
    {
        0.10,
        0.11,
        0.05,
        0.80
    };

    double actual3 {
        calculatePower(test3, 30000)
    };

    double expected3 {0.97910048};

    if (!approximatelyEqual(actual3, expected3))
    {
        return false;
    }


    // test 4: larger treatment effect with its calculated sample size
    ExperimentPlan test4
    {
        0.10,
        0.12,
        0.05,
        0.80
    };

    double actual4 {
        calculatePower(test4, 3841)
    };

    double expected4 {0.80001558};

    if (!approximatelyEqual(actual4, expected4))
    {
        return false;
    }


    // test 5: negative treatment effect should have same power
    // as an effect of the same magnitude in the other direction
    ExperimentPlan test5
    {
        0.11,
        0.10,
        0.05,
        0.80
    };

    double actual5 {
        calculatePower(test5, 14751)
    };

    double expected5 {0.80000557};

    if (!approximatelyEqual(actual5, expected5))
    {
        return false;
    }


    // test 6: higher baseline rate example
    ExperimentPlan test6
    {
        0.20,
        0.21,
        0.05,
        0.80
    };

    double actual6 {
        calculatePower(test6, 25583)
    };

    double expected6 {0.80001158};

    if (!approximatelyEqual(actual6, expected6))
    {
        return false;
    }


    // test 7: invalid sample size
    ExperimentPlan test7
    {
        0.10,
        0.11,
        0.05,
        0.80
    };

    if (!approximatelyEqual(
            calculatePower(test7, 0),
            0.0))
    {
        return false;
    }


    // test 8: invalid baseline rate
    ExperimentPlan test8
    {
        0.0,
        0.11,
        0.05,
        0.80
    };

    if (!approximatelyEqual(
            calculatePower(test8, 14751),
            0.0))
    {
        return false;
    }


    // test 9: invalid target rate
    ExperimentPlan test9
    {
        0.10,
        1.0,
        0.05,
        0.80
    };

    if (!approximatelyEqual(
            calculatePower(test9, 14751),
            0.0))
    {
        return false;
    }


    // test 10: no treatment effect
    ExperimentPlan test10
    {
        0.10,
        0.10,
        0.05,
        0.80
    };

    if (!approximatelyEqual(
            calculatePower(test10, 14751),
            0.0))
    {
        return false;
    }

    return true;
}

// ===========================================

// test configurable experiment-planning parameters
bool testExperimentPlanningParameters()
{
    // test 1: original baseline case
    // alpha = 0.05, desired power = 0.80
    ExperimentPlan test1
    {
        0.10,
        0.11,
        0.05,
        0.80
    };

    int sampleSize1 {
        requiredSampleSizePerGroup(test1)
    };

    if (sampleSize1 != 14751)
    {
        return false;
    }

    double achievedPower1 {
        calculatePower(test1, sampleSize1)
    };

    if (achievedPower1 < 0.80 ||
        achievedPower1 > 0.801)
    {
        return false;
    }

    // test 2: stricter alpha should require more users
    ExperimentPlan test2
    {
        0.10,
        0.11,
        0.01,
        0.80
    };

    int sampleSize2 {
        requiredSampleSizePerGroup(test2)
    };

    if (sampleSize2 != 21950)
    {
        return false;
    }

    if (sampleSize2 <= sampleSize1)
    {
        return false;
    }

    double achievedPower2 {
        calculatePower(test2, sampleSize2)
    };

    if (achievedPower2 < 0.80 ||
        achievedPower2 > 0.801)
    {
        return false;
    }

    // test 3: higher desired power should require more users
    ExperimentPlan test3
    {
        0.10,
        0.11,
        0.05,
        0.90
    };

    int sampleSize3 {
        requiredSampleSizePerGroup(test3)
    };

    if (sampleSize3 != 19747)
    {
        return false;
    }

    if (sampleSize3 <= sampleSize1)
    {
        return false;
    }

    double achievedPower3 {
        calculatePower(test3, sampleSize3)
    };

    if (achievedPower3 < 0.90 ||
        achievedPower3 > 0.901)
    {
        return false;
    }

    // test 4: lower desired power should require fewer users
    ExperimentPlan test4
    {
        0.10,
        0.11,
        0.05,
        0.70
    };

    int sampleSize4 {
        requiredSampleSizePerGroup(test4)
    };

    if (sampleSize4 != 11600)
    {
        return false;
    }

    if (sampleSize4 >= sampleSize1)
    {
        return false;
    }

    double achievedPower4 {
        calculatePower(test4, sampleSize4)
    };

    if (achievedPower4 < 0.70 || 
        achievedPower4 > 0.701)
    {
        return false;
    }

    // test 5: invalid alpha
    ExperimentPlan test5
    {
        0.10,
        0.11,
        0.0,
        0.80
    };

    if (requiredSampleSizePerGroup(test5) != 0)
    {
        return false;
    }


    // test 6: alpha above valid range
    ExperimentPlan test6
    {
        0.10,
        0.11,
        1.0,
        0.80
    };

    if (requiredSampleSizePerGroup(test6) != 0)
    {
        return false;
    }


    // test 7: invalid desired power
    ExperimentPlan test7
    {
        0.10,
        0.11,
        0.05,
        0.0
    };

    if (requiredSampleSizePerGroup(test7) != 0)
    {
        return false;
    }


    // test 8: desired power above valid range
    ExperimentPlan test8
    {
        0.10,
        0.11,
        0.05,
        1.0
    };

    if (requiredSampleSizePerGroup(test8) != 0)
    {
        return false;
    }

    return true;
}

// ===========================================

// call all functions in main
int main()
{
    if (
        testConversionRate() &&
        testAbsoluteLift() &&
        testRelativeLift() &&
        testRevPerUser() &&
        testAbsRevLift() &&
        testRelRevLift() &&
        testConversionStandardError() &&
        testConversionConfidenceInterval95() &&
        testPooledConversionStandardError() &&
        testConversionZScore() &&
        testConversionPValue() &&
        testIsConversionSignificant() &&
        testFilterUsersByDevice() &&
        testRequiredSampleSizePerGroup() &&
        testCalculatePower() &&
        testExperimentPlanningParameters()
    )
    {
        std::cout << "PASS" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
        return 1;
    }
}