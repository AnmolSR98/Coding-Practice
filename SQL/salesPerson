# Write your MySQL query statement below
SELECT name
FROM SalesPerson
WHERE sales_id NOT IN
(
SELECT sales_id 
FROM Orders
WHERE com_id = 1
GROUP BY sales_id 
)
