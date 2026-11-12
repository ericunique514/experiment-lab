-- 1. Users per variant
SELECT
    a.variant,
    COUNT(*) AS users
FROM experiment_assignments AS a
GROUP BY a.variant
ORDER BY a.variant;

-- 2. Purchases per variant
SELECT
    a.variant,
    SUM(p.purchased) AS purchases
FROM experiment_assignments AS a
JOIN purchases AS p ON p.user_id = a.user_id
GROUP BY a.variant
ORDER BY a.variant;

-- 3. Conversion rate per variant
SELECT
    a.variant,
    ROUND(AVG(p.purchased), 4) AS conversion_rate
FROM experiment_assignments AS a
JOIN purchases AS p ON p.user_id = a.user_id
GROUP BY a.variant
ORDER BY a.variant;

-- 4. Revenue per user per variant
SELECT
    a.variant,
    ROUND(AVG(p.order_price), 4) AS revenue_per_user
FROM experiment_assignments AS a
JOIN purchases AS p ON p.user_id = a.user_id
GROUP BY a.variant
ORDER BY a.variant;

-- 5. Average order value per variant (buyers only)
SELECT
    a.variant,
    ROUND(AVG(p.order_price), 2) AS average_order_value
FROM experiment_assignments AS a
JOIN purchases AS p ON p.user_id = a.user_id
WHERE p.purchased = 1
GROUP BY a.variant
ORDER BY a.variant;

-- 6. Conversion by device and variant
SELECT
    u.device,
    a.variant,
    COUNT(*) AS users,
    ROUND(AVG(p.purchased), 4) AS conversion_rate
FROM users AS u
JOIN experiment_assignments AS a ON a.user_id = u.user_id
JOIN purchases AS p ON p.user_id = u.user_id
GROUP BY u.device, a.variant
ORDER BY u.device, a.variant;

-- 7. Conversion by user type and variant
SELECT
    u.user_type,
    a.variant,
    COUNT(*) AS users,
    ROUND(AVG(p.purchased), 4) AS conversion_rate
FROM users AS u
JOIN experiment_assignments AS a ON a.user_id = u.user_id
JOIN purchases AS p ON p.user_id = u.user_id
GROUP BY u.user_type, a.variant
ORDER BY u.user_type, a.variant;

-- 8. Conversion by traffic source and variant
SELECT
    u.traffic_source,
    a.variant,
    COUNT(*) AS users,
    ROUND(AVG(p.purchased), 4) AS conversion_rate
FROM users AS u
JOIN experiment_assignments AS a ON a.user_id = u.user_id
JOIN purchases AS p ON p.user_id = u.user_id
GROUP BY u.traffic_source, a.variant
ORDER BY u.traffic_source, a.variant;
