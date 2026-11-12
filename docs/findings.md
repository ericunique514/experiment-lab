# Findings: Simplified Checkout A/B Test

All numbers come from the simulated dataset produced by `python/generate_data.py` (seed 1, 40,000 users). They were computed by the C++ engine and the SQL queries, and independently checked with a short script in Python.

## Hypothesis

Does a simplified checkout page increase purchase conversion?

- H0: the conversion rate is the same in A and B (pA = pB).
- H1: the conversion rate differs between A and B (pA ≠ pB).

## Experiment Design

- **A (control):** current checkout. **B (treatment):** simplified checkout.
- Users are randomly assigned to A or B.
- **Primary metric:** purchase conversion rate.
- **Secondary metrics:** revenue per user, average order value.
- **Significance level:** alpha = 0.05, two-sided.

See `experiment-design.md` for the full design.

## Dataset

| Property | Value |
|---|---|
| Users | 40,000 (A: 20,066, B: 19,934) |
| Device | Desktop 40%, Mobile 60% |
| User type | New 70%, Returning 30% |
| Traffic source | Organic 30%, Paid 30%, Referral 40% |
| Order price | fixed at $49.99 |

The data is synthetic. The treatment effect is built in on purpose: B helps mobile users and new users, and does little for desktop and returning users. The analysis checks whether the pipeline finds it.

## Statistical Analysis

Test: two-proportion z-test with a pooled standard error. Confidence interval: 95%, unpooled standard error, on the difference B − A.

| | Control (A) | Treatment (B) | Absolute lift | Relative lift | 95% CI (pp) | z | p-value |
|---|---|---|---|---|---|---|---|
| **Overall** | 10.24% | 11.37% | +1.14 pp | +11.1% | [0.53, 1.74] | 3.66 | 2.5e-04 |

Revenue per user: $5.12 (A) vs $5.69 (B), a lift of $0.57 (+11.1%). Revenue moves with conversion because every order is $49.99.

The overall lift is statistically significant at alpha = 0.05.

## Segment Analysis

| Segment | Value | A | B | Lift (pp) | Relative | 95% CI (pp) | p-value | Significant |
|---|---|---|---|---|---|---|---|---|
| device | Mobile | 9.18% | 11.16% | +1.98 | +21.6% | [1.21, 2.75] | 4.1e-07 | yes |
| device | Desktop | 11.81% | 11.69% | −0.12 | −1.0% | [−1.12, 0.87] | 0.81 | no |
| user_type | New | 10.01% | 11.68% | +1.68 | +16.7% | [0.95, 2.41] | 6.6e-06 | yes |
| user_type | Returning | 10.77% | 10.66% | −0.11 | −1.0% | [−1.21, 0.99] | 0.85 | no |
| traffic_source | Organic | 11.20% | 11.47% | +0.27 | +2.4% | [−0.87, 1.41] | 0.64 | no |
| traffic_source | Paid | 8.83% | 10.59% | +1.76 | +19.9% | [0.70, 2.81] | 1.1e-03 | yes |
| traffic_source | Referral | 10.56% | 11.89% | +1.34 | +12.7% | [0.36, 2.31] | 7.4e-03 | yes |

Charts are produced by `python/analysis.py` and saved in `docs/images/`: overall conversion, conversion by device, and lift by segment with confidence intervals.

## Business Recommendation

Ship the simplified checkout. It raises overall conversion from 10.24% to 11.37% (+11.1% relative) and revenue per user by $0.57.

The gain is concentrated among mobile users (+21.6%) and new users (+16.7%). Desktop and returning users show no measurable change. This suggests the redesign mainly removes friction on the mobile checkout and for first-time buyers. Returning users already know the old flow, so a simpler page adds little for them.

Caveats:

- A segment that is not significant here (desktop, returning, organic) does not prove there is no effect. Their confidence intervals still allow lifts of about +1 pp, so the test may lack the power to detect small effects in those groups. The C++ engine's sample-size and power functions can size a follow-up test.
- Seven segment tests were run at alpha = 0.05, so one false positive is possible by chance. The three segments with very small p-values (mobile, new users, paid) are unlikely to be that.
- The data is simulated and every order is $49.99, so revenue per user and average order value add no information beyond conversion. A real dataset would need variable order values.
- The desktop and returning rates differ slightly from the targets in the generator because of random variation. This is normal for a sample of this size.

## How the results were checked

- The C++ engine and the SQL queries agree on users, conversion and revenue per user for the overall experiment, mobile, and desktop.
- A separate Python calculation gives the same z-scores, p-values and confidence intervals as the C++ engine.
- `python/analysis.py` computes the same tests with `statsmodels`, so the Python side does not depend on the C++ code.
