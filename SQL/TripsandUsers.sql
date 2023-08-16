# Rough draft, sign off for tonight, look with fresh eyes
SELECT request_at AS Day,  
ROUND((SUM(CASE WHEN (status = 'cancelled_by_driver' OR status = 'cancelled_by_client') THEN 1 ELSE 0 END) / COUNT(request_at)), 2) 
AS 'Cancellation Rate'
FROM Trips
GROUP BY Day;
