# Write your MySQL query statement below
SELECT U.user_id as buyer_id, U.join_date, IFNULL(B.orders_in_2019, 0) as orders_in_2019
FROM Users as U
LEFT JOIN
# Table of all the users who purchased items in 2019 and the amount they bought
(SELECT buyer_id, COUNT(order_id) as orders_in_2019
FROM Orders
WHERE EXTRACT(YEAR FROM order_date) = '2019'
GROUP BY buyer_id) AS B
# Now finally uniting them 
ON U.user_id = B.buyer_id; 
