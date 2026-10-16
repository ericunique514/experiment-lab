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

### Next Steps
- Add CMake build configuration.
- Build and run the project using CMake.
- Add revenue-per-user calculations.