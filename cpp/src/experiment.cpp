//standard libraries
#include <iostream>
#include <cmath>

// project headers
#include "experiment.hpp"

// =================================================
/* 
calculates the proportion of users in an experiment
group who completed a conversion.

returns 0.0 if the group contains no users.
*/
double ExperimentGroup::conversionRate() 
const {
    if (users == 0) {
        return 0.0;
    }

    return static_cast<double>(conversions) / users;
};

// =================================================
/*
calculates the revenue per user.

returns 0.0 if the group contains no users.
*/
double ExperimentGroup::revenuePerUser()
const {
    if (users == 0) {
        return 0.0; // avoid division by zero
    }
    return revenue/users;
}

// =================================================
/*
calculates the absolute change in conversion rate
between the treatment and control groups.

absolute lift = treatment conversion rate
                - control conversion rate

returns 0.0 if either experiment group has no users.
*/
double Experiment::absoluteLift()
const {
    if(control.users == 0 || treatment.users == 0)
    {
        return 0.0; 
        // does not mean lift is actually 0, just returning
        // 0 for now to avoid error
    }
    double convRateControl {control.conversionRate()};
    double convRateTreatment {treatment.conversionRate()};
    return convRateTreatment - convRateControl;
};

// =================================================

/*
calculates the treatment's conversion-rate change
relative to the control group's conversion rate.

relative lift = (treatment rate - control rate)
                / control rate

the relative lift is undefined if the control
conversion rate is zero.
*/
double Experiment::relativeLift()
const {
    if(control.users == 0 || treatment.users == 0)
    {
        return 0.0;
        // does not mean lift is actually 0, just returning
        // 0 for now to avoid error
    }
    double convRateControl {control.conversionRate()};
    double convRateTreatment {treatment.conversionRate()};
    if (convRateControl == 0.0)
    {
        std::cerr 
        << "control group conversion rate results in undefined relative lift"
        << '\n';
        return 0.0;
    }
    return (convRateTreatment - convRateControl)/convRateControl;  
};

// ===========================================================
/*
calculates the absolute change in revenue per user
between the control and treatment groups.

absolute revenue lift = (treatment revenue per user)
                        - (control revenue per user)
*/
double Experiment::absoluteRevenueLift()
const {
    if(control.users == 0 || treatment.users == 0)
    {
        return 0.0; 
        // does not mean lift is actually 0, just returning
        // 0 for now to avoid error
    }
    double revPerUserControl {control.revenuePerUser()};
    double revPerUserTreatment {treatment.revenuePerUser()};
    return revPerUserTreatment - revPerUserControl;
}

// =================================================
/*
calculates the treatment's revenue per user change
relative to the control group's revenue per user.

relative revenue lift = (treatment revenue per user - control revenue per user)
                / control revenue per user

the relative revenue lift is undefined if the control
revenue per user is zero.
*/
double Experiment::relativeRevenueLift()
const {
    if(control.users == 0 || treatment.users == 0)
    {
        return 0.0;
        // does not mean lift is actually 0, just returning
        // 0 for now to avoid error
    }
    double revPerUserControl {control.revenuePerUser()};
    double revPerUserTreatment {treatment.revenuePerUser()};
    if (revPerUserControl == 0.0)
    {
        std::cerr 
        << "control group revenue per user results in undefined relative revenue lift"
        << '\n';
        return 0.0;
    }
    return (revPerUserTreatment - revPerUserControl)/revPerUserControl;  
}

// =========================================================
/*
creates an experiment by separating a user record into
the control and treatment group
*/
Experiment createExperiment(
    const std::vector<UserRecord>& users
)
{
    ExperimentGroup control{0, 0, 0.0};
    ExperimentGroup treatment{0, 0, 0.0};

    for (const UserRecord& user: users)
    {
        if (user.variant == "A")
        {
            ++control.users;
            control.conversions += user.purchased;
            control.revenue += user.orderPrice;

        }
        else if (user.variant == "B")
        {
            ++treatment.users;
            treatment.conversions += user.purchased;
            treatment.revenue += user.orderPrice;
        }
    }
    ;
    return Experiment{control, treatment};
}

// =========================================================
/*
calculates the standard error of the difference
between the control and treatment conversion rates.

returns 0.0 if either group contains no users.
*/
double Experiment::conversionStandardError() const
{
    if(control.users == 0 || treatment.users == 0)
    {
        std::cerr << "Absence of users in either group makes "
                  << "it impossible to calculate standard error."
                  << '\n';
        return 0.0;           
    }
    double pA {control.conversionRate()};
    double nA {static_cast<double>(control.users)};
    double pB {treatment.conversionRate()};
    double nB {static_cast<double>(treatment.users)};
    return std::sqrt(((pA * (1 - pA))/nA)+((pB * (1 - pB))/nB));
}

// =========================================================
/*
calculates the 95% confidence interval for the
absolute difference in conversion rates.

returns {0.0, 0.0} if either group contains no users.
*/
ConfidenceInterval Experiment::conversionConfidenceInterval95() const
{
    if(control.users == 0 || treatment.users == 0)
    {
        std::cerr << "Absence of users in either group makes "
                  << "it impossible to build 95% CI."
                  << '\n';
        return {0.0, 0.0};           
    }
    double lower {absoluteLift() - 1.96*conversionStandardError()};
    double upper {absoluteLift() + 1.96*conversionStandardError()};
    return {lower,upper};
}


// =========================================================
/*
calculates the pooled standard error for the difference
between the control and treatment conversion rates.

the pooled proportion assumes the null hypothesis that
both groups have the same underlying conversion rate.

returns 0.0 if either group contains no users.
*/
double Experiment::pooledConversionStandardError() const
{
    if(control.users == 0 || treatment.users == 0)
    {
        std::cerr << "Absence of users in either group makes "
                  << "it impossible to calculate pooled "
                  << "conversion standard error"
                  << '\n';
        return 0.0;           
    }  
    double pPool 
    {
        static_cast<double>(control.conversions + treatment.conversions)/
        (control.users + treatment.users)
    };
    return std::sqrt(pPool*(1-pPool)*((1.0/control.users) + (1.0/treatment.users)));
}

// =========================================================
/*
calculates the z-score for the difference between the
control and treatment conversion rates.

the z-score measures the observed conversion lift
relative to the pooled standard error under the null
hypothesis.

returns 0.0 if either group contains no users.
*/
double Experiment::conversionZScore() const
{
    double pooledSE {pooledConversionStandardError()};
    if
    (
        control.users == 0 || 
        treatment.users == 0
    )
    {
        std::cerr << "Absence of users in either group makes "
                  << "it impossible to calculate a Z score."
                  << '\n';
        return 0.0;           
    }  
    if (pooledSE == 0.0)
    {
        std::cerr << "A pooled standard error of zero makes "
                  << "it impossible to calculate a Z score."
                  << '\n';
        return 0.0;
    }
    return absoluteLift()/pooledSE;
}

// =========================================================
/*
calculates the two-sided p-value for the difference
between the control and treatment conversion rates.

the p-value is derived from the absolute z-score and
represents how extreme the observed difference would
be under the null hypothesis that both groups have the
same underlying conversion rate.
*/
double Experiment::conversionPValue() const
{
    double zScore {conversionZScore()};
    return std::erfc(std::abs(zScore)/std::sqrt(2));
}

// =========================================================
/*
determines whether the difference between the control
and treatment conversion rates is statistically significant.

returns true when the conversion p-value is less than
the supplied significance level alpha.
*/
bool Experiment::isConversionSignificant(double alpha) const
{
    return conversionPValue() < alpha;
}

// =========================================================
/*
Filters user records by the specified device type.

Returns a vector containing only users whose device
matches the supplied device string.
*/
std::vector<UserRecord> filterUsersByDevice(
    const std::vector<UserRecord>& users,
    const std::string& device
)
{
    std::vector<UserRecord> filteredUsers {};
    for (const UserRecord& user: users)
    {
        if(user.device == device)
        {
            filteredUsers.push_back(user);
        }
    }
    return filteredUsers;
}

// =========================================================
/*
Calculates the minimum required sample size per experiment
group for detecting a difference between the baseline and
target conversion rates.

Uses a two-sided significance level of 0.05 and statistical
power of 0.80 for the current implementation.

Returns 0 if either conversion rate is outside the range
(0, 1), or if the baseline and target rates are equal.
*/
int requiredSampleSizePerGroup(
    const ExperimentPlan& experimentPlan
)
{
    double pA {experimentPlan.baselineRate};
    double pB {experimentPlan.targetRate};
    // return early if the input conditions are invalid
    if (!(0.0 < pA && pA < 1.0))
    {
        std::cerr << "baseline rate must be between 0 and 1";
        return 0;
    }
    if (!(0.0 < pB && pB < 1.0))
    {
        std::cerr << "target rate must be between 0 and 1";
        return 0;
    }
    if (experimentPlan.baselineRate == experimentPlan.targetRate)
    {
        std::cerr << "target rate must be different from baseline rate";
        return 0;
    }
    /*
    double alpha {experimentPlan.alpha}; 
    double power {experimentPlan.desiredPower}; 
    these will be used when using the generalized 
    zAlpha and zScore
    */
    double zAlpha {1.96}; // hardcoded for now
    double zPower {0.8416}; // hardcoded for now
    double avrgRate {(pA + pB)/2};
    double significanceTerm
    {
        zAlpha * std::sqrt(
            2.0 * avrgRate * (1.0 - avrgRate)
        )

    };
    double powerTerm 
    {
        zPower * std::sqrt(
            pA * (1.0 - pA) + 
            pB * (1.0 - pB)
        )
    };
    double effectSize {pB - pA};
    int requiredSampleSize 
    {
        static_cast<int>
        (
            std::ceil
            (
               ((significanceTerm + powerTerm) *
                (significanceTerm + powerTerm))
                /
                (effectSize * effectSize)
            )
        )
    };
    return requiredSampleSize;
}

// =========================================================
/*
Calculates the approximate statistical power for detecting
the difference between the baseline and target conversion
rates at a specified sample size per group.

The current implementation assumes equally sized control
and treatment groups and a two-sided significance level
of alpha = 0.05.

Returns 0.0 if the conversion rates are invalid, the
sample size is non-positive, or there is no treatment
effect to detect.
*/
double calculatePower(
    const ExperimentPlan& experimentPlan,
    int sampleSizePerGroup
)
{
    double pA {experimentPlan.baselineRate};
    double pB {experimentPlan.targetRate};
    int n {sampleSizePerGroup}; // shorter name to call
    // return early if input conditions are invalid
    if (!(0.0 < pA && pA < 1.0))
    {
        std::cerr << "baseline rate must be between 0 and 1";
        return 0.0;
    }
    if (!(0.0 < pB && pB < 1.0))
    {
        std::cerr << "target rate must be between 0 and 1";
        return 0.0;
    }
    if (n <= 0)
    {
        std::cerr << "must have a sample size";
        return 0.0;
    }
    if (pA == pB)
    {
        std::cerr << "No treatment effect to detect";
        return 0.0;
    }
    double avrgRate {(pA + pB) / 2.0};
    double zAlpha {1.96}; // hardcoded for now
    double zPower 
    {
        ((std::sqrt(n) * std::abs(pB - pA))
        - (zAlpha * std::sqrt(2.0 * avrgRate * (1 - avrgRate))))
        /
        (std::sqrt((pA * (1 - pA)) + (pB * (1 - pB))))
    };
    double power 
    {
        0.5 * (1.0 + std::erf(zPower / std::sqrt(2.0)))
    };
    if (!(0.0 <= power && power <= 1.0))
    {
        std::cerr << "Invalid Power";
        return 0.0;
    }
    return power;
}