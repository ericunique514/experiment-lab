#include <iostream>
#include "experiment.hpp"
#include "csv_reader.hpp"

int main() {
    auto testUsers = loadUsersFromCsv("generated_users.csv");
    Experiment testExperiment{createExperiment(testUsers)};
    ConfidenceInterval ci {testExperiment.conversionConfidenceInterval95()};

    std::cout << "Control info: "
             << '\n'
             << "Control users: "   
             << testExperiment.control.users
             << '\n'
             << "Control conversions: "
             << testExperiment.control.conversions
             << '\n'
             << "Control conversion rate:"
             << testExperiment.control.conversionRate()
             << '\n'
             << "Control revenue: "
             << testExperiment.control.revenue
             << '\n'
             << "Control revenue per user: "
             << testExperiment.control.revenuePerUser()
             << '\n' << '\n'
             << "Treatment info: "
             << '\n'
             << "Treatment users: "
             << testExperiment.treatment.users
             << '\n'
             << "Treatment conversions: "
             << testExperiment.treatment.conversions
             << '\n'
             << "Treatent conversion rate: "
             << testExperiment.treatment.conversionRate()
             << '\n'
             << "Treatment revenue: "
             << testExperiment.treatment.revenue
             << '\n'
             << "Treatment revenue per user: "
             << testExperiment.treatment.revenuePerUser()
             << '\n' << '\n'
             << "Absolute conversion lift: "
             << testExperiment.absoluteLift()
             << '\n'
             << "Relative conversion lift:"
             << testExperiment.relativeLift()
             << '\n'
             << "Absolute revenue lift: "
             << testExperiment.absoluteRevenueLift()
             << '\n'
             << "Relative revenue lift: "
             << testExperiment.relativeRevenueLift()
             << '\n'
             << "Confidence interval: ["
             << ci.lower
             << ", "
             << ci.upper
             << "]\n"
             << "Z Score: "
             << testExperiment.conversionZScore()
             << '\n'
             << "P Value: "
             << testExperiment.conversionPValue()
             << '\n'
             << "Statistically significant (alpha = 0.05): "
             << std::boolalpha
             << testExperiment.isConversionSignificant(0.05)
             << '\n'
             << std::endl;

    return 0;
}