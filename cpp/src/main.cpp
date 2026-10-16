#include <iostream>
#include "../include/experiment.hpp"

int main() {
    ExperimentGroup control{1000, 0, 5000.0};
    ExperimentGroup treatment{1000, 10, 5000.0};
    Experiment Test{control, treatment};


    std::cout << "Control conversion: "
              << control.conversionRate()
              << '\n'
              << "Treatment conversion: "
              << treatment.conversionRate()
              << '\n'
              << "Absolute Lift: "
              << Test.absoluteLift()
              << '\n'
              << "Relative Lift: "
              << Test.relativeLift()
              << std::endl;

    return 0;
}