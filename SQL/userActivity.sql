# Write your MySQL query statement below
SELECT activity_date as day, COUNT(DISTINCT user_id) as active_users
FROM Activity
WHERE activity_date <= '2019-07-27' AND activity_date >= ADDDATE('2019-07-27', INTERVAL -30 DAY)
GROUP BY day;
