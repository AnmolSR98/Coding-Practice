# Write your MySQL query statement below
SELECT Product.product_id, Product.product_name
FROM Product
JOIN Sales
ON Sales.product_id = Product.product_id
GROUP BY Sales.product_id
HAVING EXTRACT(MONTH FROM MAX(Sales.sale_date)) < 4;
