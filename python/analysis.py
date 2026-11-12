"""Segment analysis, statistical check and charts for the checkout A/B test.

Run from the repo root, after generate_data.py:
    python python/analysis.py

Reads data/raw/generated_users_full.csv and writes:
    data/processed/segment_results.csv
    docs/images/overall_conversion.png
    docs/images/conversion_by_device.png
    docs/images/lift_by_segment.png
"""
import os

import matplotlib
matplotlib.use("Agg")  # draw to files only, no window needed
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from statsmodels.stats.proportion import confint_proportions_2indep, proportions_ztest

CSV_PATH = "data/raw/generated_users_full.csv"
RESULTS_PATH = "data/processed/segment_results.csv"
IMAGE_DIR = "docs/images"
SEGMENT_COLUMNS = ["device", "user_type", "traffic_source"]

COLOR_A = "#7f8c8d"  # control
COLOR_B = "#2e86c1"  # treatment

os.makedirs(os.path.dirname(RESULTS_PATH), exist_ok=True)
os.makedirs(IMAGE_DIR, exist_ok=True)

def compare_groups(data):
    """Compare variant B (treatment) against variant A (control) for one set of users."""
    group_a = data[data["variant"] == "A"]
    group_b = data[data["variant"] == "B"]

    users_a, users_b = len(group_a), len(group_b)
    buyers_a, buyers_b = int(group_a["purchased"].sum()), int(group_b["purchased"].sum())
    rate_a, rate_b = buyers_a / users_a, buyers_b / users_b

    # Two-proportion z-test (pooled standard error), same test as the C++ engine
    z_score, p_value = proportions_ztest(
        np.array([buyers_b, buyers_a]), np.array([users_b, users_a])
    )

    # 95% confidence interval for the difference B - A (unpooled standard error)
    ci_low, ci_high = confint_proportions_2indep(
        buyers_b, users_b, buyers_a, users_a, method="wald"
    )

    return {
        "users_A": users_a,
        "users_B": users_b,
        "conversion_A": rate_a,
        "conversion_B": rate_b,
        "abs_lift_pp": (rate_b - rate_a) * 100,
        "rel_lift_pct": (rate_b - rate_a) / rate_a * 100,
        "ci_low_pp": ci_low * 100,
        "ci_high_pp": ci_high * 100,
        "z_score": z_score,
        "p_value": p_value,
        "significant": bool(p_value < 0.05),
    }

def build_results(df):
    """One row for the overall experiment, then one row per segment value."""
    rows = [{"segment": "overall", "value": "All users", **compare_groups(df)}]
    for column in SEGMENT_COLUMNS:
        for value in sorted(df[column].unique()):
            rows.append({"segment": column, "value": value, **compare_groups(df[df[column] == value])})
    return pd.DataFrame(rows)

def chart_overall(results):
    row = results.iloc[0]
    rates = [row["conversion_A"] * 100, row["conversion_B"] * 100]

    fig, ax = plt.subplots(figsize=(5, 4))
    bars = ax.bar(["A (control)", "B (simplified checkout)"], rates, color=[COLOR_A, COLOR_B])
    for bar, rate in zip(bars, rates):
        ax.text(bar.get_x() + bar.get_width() / 2, rate + 0.1, f"{rate:.2f}%", ha="center")
    ax.set_ylabel("Purchase conversion rate (%)")
    ax.set_title("Overall conversion: A vs B")
    ax.set_ylim(0, max(rates) * 1.25)
    fig.tight_layout()
    fig.savefig(f"{IMAGE_DIR}/overall_conversion.png", dpi=150)
    plt.close(fig)

def chart_by_device(results):
    devices = results[results["segment"] == "device"].reset_index(drop=True)
    positions = np.arange(len(devices))
    width = 0.35

    fig, ax = plt.subplots(figsize=(6, 4))
    bars_a = ax.bar(positions - width / 2, devices["conversion_A"] * 100, width, label="A (control)", color=COLOR_A)
    bars_b = ax.bar(positions + width / 2, devices["conversion_B"] * 100, width, label="B (simplified checkout)", color=COLOR_B)
    for bars in (bars_a, bars_b):
        for bar in bars:
            height = bar.get_height()
            ax.text(bar.get_x() + bar.get_width() / 2, height + 0.1, f"{height:.2f}%", ha="center")
    ax.set_xticks(positions)
    ax.set_xticklabels(devices["value"])
    ax.set_ylabel("Purchase conversion rate (%)")
    ax.set_title("Conversion by device")
    ax.set_ylim(0, devices[["conversion_A", "conversion_B"]].to_numpy().max() * 100 * 1.25)
    ax.legend()
    fig.tight_layout()
    fig.savefig(f"{IMAGE_DIR}/conversion_by_device.png", dpi=150)
    plt.close(fig)

def chart_lift_by_segment(results):
    labels = [
        "Overall" if row["segment"] == "overall" else f"{row['segment']}: {row['value']}"
        for _, row in results.iterrows()
    ]
    lift = results["abs_lift_pp"].to_numpy()
    lower_error = lift - results["ci_low_pp"].to_numpy()
    upper_error = results["ci_high_pp"].to_numpy() - lift
    positions = np.arange(len(labels))

    fig, ax = plt.subplots(figsize=(7, 5))
    ax.errorbar(lift, positions, xerr=[lower_error, upper_error], fmt="o", color=COLOR_B, capsize=4)
    ax.axvline(0, color="black", linewidth=1)
    ax.set_yticks(positions)
    ax.set_yticklabels(labels)
    ax.invert_yaxis()
    ax.set_xlabel("Absolute lift, B minus A (percentage points) with 95% CI")
    ax.set_title("Treatment effect by segment")
    fig.tight_layout()
    fig.savefig(f"{IMAGE_DIR}/lift_by_segment.png", dpi=150)
    plt.close(fig)

def main():
    df = pd.read_csv(CSV_PATH)
    results = build_results(df)

    pd.set_option("display.width", 200)
    pd.set_option("display.max_columns", None)
    print(results.round(4).to_string(index=False))

    results.to_csv(RESULTS_PATH, index=False)

    chart_overall(results)
    chart_by_device(results)
    chart_lift_by_segment(results)
    print(f"Saved {RESULTS_PATH} and 3 charts in {IMAGE_DIR}/")

if __name__ == "__main__":
    main()
