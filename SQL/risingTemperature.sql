# Write your MySQL query statement below
SELECT Weather.id 
FROM Weather, 
(SELECT id, LAG(Weather.temperature, 1, 0) OVER (ORDER BY Weather.id) as last_temp
FROM Weather) as prev
WHERE Weather.id = prev.id 
AND prev.last_temp != 0 
AND Weather.temperature > prev.last_temp;
