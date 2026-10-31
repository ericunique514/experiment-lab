#include <iostream>
#include "experiment.hpp"
#include "csv_reader.hpp"

int main() {
    ExperimentGroup control{1000, 0, 50000.0};
    ExperimentGroup treatment{1000, 10, 55000.0};
    Experiment Test{control, treatment};
    
    std::vector<UserRecord> testUsers 
    {
        loadUsersFromCsv("generated_users.csv")
    };
    Experiment testExperiment{createExperiment(testUsers)};

    /*std::cout << "Control conversion: "
              << control.conversionRate()
              << '\n'
              << "Treatment conversion: "
              << treatment.conversionRate()
              << '\n'
              << "Revenue per user (control): "
              << control.revenuePerUser()
              << '\n'
              << "Revenue per user (treatment): "
              << treatment.revenuePerUser()
              << '\n'
              << "Absolute Lift: "
              << Test.absoluteLift()
              << '\n'
              << "Relative Lift: "
              << Test.relativeLift()
              << '\n'
              << "Absolute Revenue Lift: "
              << Test.absoluteRevenueLift()
              << '\n'
              << "Relative Revenue Lift: "
              << Test.relativeRevenueLift()
              << std::endl;
    */
   std::cout << "Control info: "
             << '\n'   
             << testExperiment.control.users
             << '\n'
             << testExperiment.control.conversions
             << '\n'
             << testExperiment.control.conversionRate()
             << '\n'
             << testExperiment.control.revenue
             << '\n'
             << testExperiment.control.revenuePerUser()
             << '\n'
             << "Treatment info: "
             << '\n'
             << testExperiment.treatment.users
             << '\n'
             << testExperiment.treatment.conversions
             << '\n'
             << testExperiment.treatment.conversionRate()
             << '\n'
             << testExperiment.treatment.revenue
             << '\n'
             << testExperiment.treatment.revenuePerUser()
             << '\n'
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
             << std::endl;

    return 0;
}