# Development Log

## 2026-10-15 — Initial C++ Experiment Model

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

The next stage will introduce an `Experiment` object containing both a control group and a treatment group.

### First Implementations
- Implemented `Experiment` with control and treatment groups.
- Added `absoluteLift()` and `relativeLift()`.
- Handled empty groups and zero control conversion rate.
- Manually tested positive lift, negative lift, equal performance, and zero control conversions.

### Revenue Metrics
- Added `revenuePerUser()` to `ExperimentGroup`.
- Added `absoluteRevenueLift()` and `relativeRevenueLift()` to `Experiment`.
- Handled zero-user cases to avoid division by zero.
- Handled zero control revenue per user, where relative revenue lift is undefined.
- Manually tested positive, negative, equal, and zero-control revenue cases.
- Confirmed the project builds and runs successfully with CMake.

### Next Steps
- Add automated unit tests for experiment metrics.
- Integrate testing into the CMake build.
- Begin implementing statistical analysis, starting with standard error and confidence intervals.