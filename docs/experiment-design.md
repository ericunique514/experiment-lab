# ExperimentLab — Experiment Design

## 1. Business Question

Does a simplified checkout experience increase the probability that a user completes a purchase?

The project simulates an e-commerce company running an A/B test on its checkout flow.

## 2. Experiment Groups

### Control — Group A
Users see the existing checkout experience.

### Treatment — Group B
Users see a simplified checkout experience designed to reduce friction during checkout.

Users are randomly assigned to either Group A or Group B.

## 3. Hypothesis

### Null Hypothesis

The simplified checkout does not change the purchase conversion rate.

H0: pA = pB

### Alternative Hypothesis

The simplified checkout changes the purchase conversion rate.

H1: pA ≠ pB

Our simulated dataset will be designed so that Group B has a small positive treatment effect.

## 4. Primary Metric

### Purchase Conversion Rate

Conversion Rate = Number of users who purchase / Number of assigned users

This is the primary metric used to determine whether the treatment is successful.

## 5. Secondary Metrics

We will also analyze:

- Checkout completion rate
- Revenue per user
- Average order value
- Add-to-cart rate

These metrics provide additional information about how the treatment affects user behavior.

## 6. Guardrail Metrics

We will monitor metrics that could reveal unintended negative effects, including:

- Cart abandonment rate
- Checkout abandonment rate

A treatment should not be considered successful solely because the primary metric improves if important guardrail metrics become substantially worse.

## 7. User Attributes

Each simulated user may contain:

- user_id
- experiment_group
- device_type
- user_type
- traffic_source

Possible values include:

### device_type
- mobile
- desktop

### user_type
- new
- returning

### traffic_source
- organic
- paid
- direct
- referral

These attributes will allow us to analyze whether the treatment effect differs across user segments.

## 8. User Events

The simulated event funnel will contain:

1. visit
2. product_view
3. add_to_cart
4. checkout
5. purchase

Not every user will reach every stage.

## 9. Simulated Treatment Effect

The treatment will have a modest overall positive effect.

Approximate target conversion rates:

- Group A: ~10%
- Group B: ~11–12%

The treatment effect will not be identical across all users.

For example:

- Mobile users may experience a larger improvement.
- Desktop users may experience little improvement.
- New and returning users may respond differently.

This will allow the project to demonstrate segment-level A/B analysis rather than only an overall comparison.

## 10. Initial Dataset Size

The first simulated experiment will contain approximately:

- 20,000–50,000 users
- Roughly 50% assigned to Group A
- Roughly 50% assigned to Group B

The exact size may be adjusted later when we implement statistical power analysis.

## 11. Technology Responsibilities

### Python / Pandas

Used for:

- generating synthetic users and events
- data cleaning
- exploratory analysis
- visualizations
- validating statistical results

### SQL

Used for:

- storing experiment data
- aggregating users and events
- calculating experiment metrics
- segment-level queries

### C++

Used for:

- experiment metric calculations
- treatment lift calculations
- confidence intervals
- hypothesis testing
- statistical significance
- sample-size and power calculations

## 12. Initial Project Goal

The minimum viable project should be able to take experiment data and produce:

- Group A conversion rate
- Group B conversion rate
- absolute lift
- relative lift
- confidence interval
- p-value
- statistical significance result
- segment-level results
- business recommendation

Advanced features will only be considered after the MVP is complete.
