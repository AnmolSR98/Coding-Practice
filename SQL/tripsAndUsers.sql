# selecting the request at as day
SELECT T.request_at as Day, 
# the cancellation rate is the sum of all cases where cancelled divided by total trip ids for that given day
ROUND((SUM(CASE WHEN (status = 'cancelled_by_driver' OR status = 'cancelled_by_client') THEN 1 ELSE 0 END) / COUNT(request_at)), 2) 
# had to use quotes to avoid prompting the wrath of sql gods UwU
AS 'Cancellation Rate'
FROM Trips as T
# filter out cases where users are not allowed to book trips
WHERE T.client_id NOT IN(SELECT users_id FROM Users WHERE banned='Yes')
AND T.driver_id NOT IN(SELECT users_id FROM Users WHERE banned='Yes')
# group by day
GROUP BY Day;
