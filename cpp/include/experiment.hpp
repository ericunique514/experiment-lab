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

struct ConfidenceInterval
{
    double lower;
    double upper;
};

struct Experiment 
{
    ExperimentGroup control;
    ExperimentGroup treatment;

    double absoluteLift() const;
    double relativeLift() const;

    double absoluteRevenueLift() const;
    double relativeRevenueLift() const;

    double conversionStandardError() const;
    ConfidenceInterval conversionConfidenceInterval95() const;
    double pooledConversionStandardError() const;
    double conversionZScore() const;
    double conversionPValue() const;
    bool isConversionSignificant(double alpha) const;
};

struct UserRecord
{
    int userId;
    std::string device;
    std::string variant;
    int purchased;
    double orderPrice;
};

Experiment createExperiment(
    const std::vector<UserRecord>& users
);

std::vector<UserRecord> filterUsersByDevice(
    const std::vector<UserRecord>& users,
    const std::string& device 
);

struct ExperimentPlan
{
    double baselineRate;
    double targetRate;
    double alpha;
    double desiredPower;
};

int requiredSampleSizePerGroup(
    const ExperimentPlan& experimentPlan
);
#endif