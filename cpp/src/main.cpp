#include <iostream>
#include <iomanip>
#include <string>

#include "experiment.hpp"
#include "csv_reader.hpp"


// =========================================================
/*
Prints a summary of conversion and revenue results
for a given A/B experiment.
*/
void printExperimentReport(
    const std::string& name,
    const Experiment& experiment)
{
    ConfidenceInterval ci {
        experiment.conversionConfidenceInterval95()
    };

    std::cout
        << "\n========== " << name << " ==========\n\n"

        << "Sample Size\n"
        << "Control users:             "
        << experiment.control.users << '\n'
        << "Treatment users:           "
        << experiment.treatment.users << "\n\n"

        << std::fixed << std::setprecision(2)

        << "Conversion Results\n"
        << "Control conversion:        "
        << experiment.control.conversionRate() * 100
        << "%\n"

        << "Treatment conversion:      "
        << experiment.treatment.conversionRate() * 100
        << "%\n"

        << "Absolute lift:             "
        << experiment.absoluteLift() * 100
        << " percentage points\n"

        << "Relative lift:             "
        << experiment.relativeLift() * 100
        << "%\n"

        << "95% confidence interval:   ["
        << ci.lower * 100
        << ", "
        << ci.upper * 100
        << "] percentage points\n\n"

        << "Statistical Analysis\n"
        << "Z-score:                   "
        << experiment.conversionZScore()
        << '\n';

    std::cout
        << std::scientific
        << "P-value:                   "
        << experiment.conversionPValue()
        << '\n';

    std::cout
        << std::defaultfloat
        << std::boolalpha
        << "Significant (alpha=0.05):  "
        << experiment.isConversionSignificant(0.05)
        << "\n\n"

        << std::fixed << std::setprecision(2)

        << "Revenue Results\n"
        << "Control revenue/user:      $"
        << experiment.control.revenuePerUser()
        << '\n'

        << "Treatment revenue/user:    $"
        << experiment.treatment.revenuePerUser()
        << '\n'

        << "Absolute revenue lift:     $"
        << experiment.absoluteRevenueLift()
        << '\n'

        << "Relative revenue lift:     "
        << experiment.relativeRevenueLift() * 100
        << "%\n";
}


// =========================================================

int main()
{
    // Load the full generated dataset
    std::vector<UserRecord> users =
        loadUsersFromCsv("generated_users.csv");


    // Overall experiment
    Experiment overallExperiment =
        createExperiment(users);


    // Mobile experiment
    std::vector<UserRecord> mobileUsers =
        filterUsersByDevice(users, "Mobile");

    Experiment mobileExperiment =
        createExperiment(mobileUsers);


    // Desktop experiment
    std::vector<UserRecord> desktopUsers =
        filterUsersByDevice(users, "Desktop");

    Experiment desktopExperiment =
        createExperiment(desktopUsers);


    // Print reports
    printExperimentReport(
        "OVERALL",
        overallExperiment
    );

    printExperimentReport(
        "MOBILE",
        mobileExperiment
    );

    printExperimentReport(
        "DESKTOP",
        desktopExperiment
    );


    return 0;
}