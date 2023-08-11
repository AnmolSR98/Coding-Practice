# Write your MySQL query statement below
SELECT cust.name as Customers
FROM Customers cust
LEFT JOIN Orders
ON cust.id = Orders.customerId
WHERE Orders.customerId IS NULL;
