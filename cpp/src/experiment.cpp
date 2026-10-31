//standard libraries
#include <iostream>

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