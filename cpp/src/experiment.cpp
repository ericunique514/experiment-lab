#include "../include/experiment.hpp"

double ExperimentGroup::conversionRate() const {
    if (users == 0) {
        return 0.0;
    }

    return static_cast<double>(conversions) / users;
}