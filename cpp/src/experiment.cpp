//standard libraries
#include <iostream>

// project headers
#include "../include/experiment.hpp"

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