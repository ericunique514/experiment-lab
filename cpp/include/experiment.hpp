#ifndef EXPERIMENT_HPP
#define EXPERIMENT_HPP

struct ExperimentGroup 
{
    int users;
    int conversions;
    double revenue;

    double conversionRate() const;
    double revenuePerUser() const;
};

struct Experiment 
{
    ExperimentGroup control;
    ExperimentGroup treatment;

    double absoluteLift() const;
    double relativeLift() const;

    double absoluteRevenueLift() const;
    double relativeRevenueLift() const;
};
#endif