#ifndef EXPERIMENT_HPP
#define EXPERIMENT_HPP

struct ExperimentGroup {
    int users;
    int conversions;
    double revenue;

    double conversionRate() const;
};

#endif