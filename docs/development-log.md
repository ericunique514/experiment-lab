# Development Log

### Implemented
- Created `ExperimentGroup` struct.
- Added fields for:
  - users
  - conversions
  - revenue
- Implemented `conversionRate()`.
- Added protection against division by zero.
- Created a simple `main.cpp` test.
- Successfully compiled and ran the C++ program.

### Current Behavior

Example:

- Users: 1000
- Conversions: 100
- Conversion rate: 0.10

### Design Decision

`ExperimentGroup` represents one side of an A/B experiment.

An `Experiment` contains both a control group and a treatment group and is responsible for comparing their performance.

---

## Experiment Lift Metrics

### Implemented
- Added `Experiment` with control and treatment groups.
- Added `absoluteLift()`.
- Added `relativeLift()`.
- Handled empty experiment groups.
- Handled zero control conversion rate, where relative lift is undefined.

### Testing
Manually tested:
- Positive lift.
- Negative lift.
- Equal conversion rates.
- Zero control conversions.
- Empty experiment groups.

---

## Revenue Metrics

### Implemented
- Added `revenuePerUser()` to `ExperimentGroup`.
- Added `absoluteRevenueLift()` to `Experiment`.
- Added `relativeRevenueLift()` to `Experiment`.
- Handled zero-user cases to avoid division by zero.
- Handled zero control revenue per user, where relative revenue lift is undefined.

### Testing
Manually tested:
- Positive revenue lift.
- Negative revenue lift.
- Equal revenue per user.
- Zero control revenue.
- Empty experiment groups.

---

## Build System and Automated Testing

### Implemented
- Added CMake build configuration.
- Configured the project to use C++17.
- Added separate build targets for:
  - main experiment executable
  - experiment test executable
- Integrated automated testing using CTest.
- Added an `approximatelyEqual()` helper for floating-point comparisons.

### Automated Test Coverage
Added tests for:
- `conversionRate()`
- `absoluteLift()`
- `relativeLift()`
- `revenuePerUser()`
- `absoluteRevenueLift()`
- `relativeRevenueLift()`

Tests include normal cases and important edge cases such as:
- Empty experiment groups.
- Zero conversions.
- Equal control and treatment performance.
- Negative treatment effects.
- Zero control revenue.

---

## CSV Data Integration

### Implemented
- Added `UserRecord` to represent individual experiment users.
- Added `csv_reader.hpp` and `csv_reader.cpp`.
- Implemented `splitCsvLine()` for CSV parsing.
- Implemented `loadUsersFromCsv()` to convert CSV rows into `UserRecord` objects.
- Added a fixed four-user CSV fixture for testing.
- Added `createExperiment()` to aggregate user-level data into control and treatment groups.

### Data Pipeline

The C++ analysis pipeline now supports:

`CSV file → vector<UserRecord> → Experiment → experiment metrics`

### Testing
Added automated tests to verify:
- Correct number of CSV records loaded.
- Correct parsing of user IDs.
- Correct device values.
- Correct experiment variants.
- Correct purchase values.
- Correct order prices.
- Correct aggregation into control and treatment groups.
- Correct user, conversion, and revenue totals.

Example test aggregation:

- Control: 2 users, 0 conversions, $0.00 revenue.
- Treatment: 2 users, 2 conversions, $89.49 revenue.

---

## Conversion Statistical Analysis

### Standard Error
Implemented `conversionStandardError()`.

The function calculates the unpooled standard error for the observed difference between the control and treatment conversion rates.

Added handling for experiments where either group contains no users.

### 95% Confidence Interval
Added `ConfidenceInterval` with:
- `lower`
- `upper`

Implemented `conversionConfidenceInterval95()`.

The confidence interval is calculated using:

`absolute lift ± 1.96 × standard error`

Added tests for:
- Positive treatment effects.
- Equal conversion rates.
- Negative treatment effects.
- Empty experiment groups.

---

## Two-Proportion Z-Test

### Pooled Standard Error
Implemented `pooledConversionStandardError()`.

The pooled calculation assumes the null hypothesis that the control and treatment groups have the same underlying conversion rate.

Fixed integer-division issues by explicitly using floating-point calculations.

### Z-Score
Implemented `conversionZScore()`.

The z-score measures the observed conversion-rate difference relative to the pooled standard error under the null hypothesis.

Handled cases where:
- Either experiment group contains no users.
- The pooled standard error is zero.

### P-Value
Implemented `conversionPValue()`.

The function converts the absolute z-score into a two-sided p-value using the standard normal distribution.

### Statistical Significance
Implemented:

`isConversionSignificant(double alpha)`

The function determines whether the observed conversion-rate difference is statistically significant at a supplied significance level.

For example:

- `alpha = 0.05`
- `p < 0.05` → statistically significant
- `p >= 0.05` → not statistically significant

### Automated Testing
Added tests covering:
- Positive statistically significant effects.
- Negative treatment effects.
- Equal conversion rates.
- Non-significant differences.
- Different control and treatment sample sizes.
- Zero conversions.
- Empty experiment groups.
- Significance at different alpha levels.

All current automated tests pass through CTest.

---

## Current Architecture

The project currently supports:

`Generated user data`
→ `CSV`
→ `loadUsersFromCsv()`
→ `vector<UserRecord>`
→ `createExperiment()`
→ `Experiment`
→ `conversion and revenue metrics`
→ `confidence interval`
→ `z-test`
→ `p-value`
→ `statistical significance`

The synthetic dataset generator currently creates 40,000 users with deterministic output during development using a fixed random seed.

Treatment effects differ by device type, allowing future segment-level analysis.

---

## Next Steps

- Run the complete 40,000-user synthetic experiment through the full C++ statistical pipeline.
- Produce a clean experiment report from `main.cpp`.
- Compare calculated results against the known behavior of the synthetic data.
- Add segment-level analysis for:
  - Mobile users.
  - Desktop users.
- Compare treatment effects across user segments.
- Improve generated order values so revenue analysis is not completely determined by conversion rate.
- Later, apply the same analysis engine to a real randomized A/B testing dataset.