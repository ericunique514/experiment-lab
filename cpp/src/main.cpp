#include <iostream>
#include "experiment.hpp"

int main() {
    ExperimentGroup control{1000, 0, 50000.0};
    ExperimentGroup treatment{1000, 10, 55000.0};
    Experiment Test{control, treatment};


    std::cout << "Control conversion: "
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

    return 0;
}