# Write your MySQL query statement below
SELECT Users.name as NAME, SUM(Transactions.amount) as BALANCE
FROM Transactions
LEFT JOIN Users ON Transactions.account = Users.account
GROUP BY Transactions.account
HAVING BALANCE > 10000;
