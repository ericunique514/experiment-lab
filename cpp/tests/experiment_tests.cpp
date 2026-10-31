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

// call all functions in main
int main()
{
    if (
        testConversionRate() &&
        testAbsoluteLift() &&
        testRelativeLift() &&
        testRevPerUser() &&
        testAbsRevLift() &&
        testRelRevLift()
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