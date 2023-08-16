# Write your MySQL query statement below
SELECT num as ConsecutiveNums 
FROM 
# creating a table that contains data on the previous values found
(SELECT id, num, 
LAG(num, 2, 0) OVER (ORDER BY id) AS N2,
LAG(num, 1, 0) OVER (ORDER BY id) AS N1,
LEAD(num, 1, 0) OVER (ORDER BY id) AS P1,
LEAD(num, 2, 0) OVER (ORDER BY id) AS P2
FROM Logs) AS C
# same cases as the human traffic problem
WHERE (C.N2 = num AND C.N1 = num )
    OR (C.N1 = num AND C.P1 = num )
    OR (C.P1 = num AND C.P2 = num )
GROUP BY ConsecutiveNums;
