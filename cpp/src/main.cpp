#include <iostream>
#include "../include/experiment.hpp"

int main() {
    ExperimentGroup control{1000, 100, 5000.0};

    std::cout << "Conversion rate: "
              << control.conversionRate()
              << std::endl;

    return 0;
}