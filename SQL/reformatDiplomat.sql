# Write your MySQL query statement below
SELECT id, 
  SUM(CASE WHEN month = 'jan' THEN revenue ELSE NULL END) as Jan_Revenue,
  SUM(CASE WHEN month = 'feb' THEN revenue ELSE NULL END) as Feb_Revenue,
  SUM(CASE WHEN month = 'mar' THEN revenue ELSE NULL END) as Mar_Revenue,
  SUM(CASE WHEN month = 'apr' THEN revenue ELSE NULL END) as Apr_Revenue,
  SUM(CASE WHEN month = 'may' THEN revenue ELSE NULL END) as May_Revenue,
  SUM(CASE WHEN month = 'jun' THEN revenue ELSE NULL END) as Jun_Revenue,
  SUM(CASE WHEN month = 'jul' THEN revenue ELSE NULL END) as Jul_Revenue,
  SUM(CASE WHEN month = 'aug' THEN revenue ELSE NULL END) as Aug_Revenue,
  SUM(CASE WHEN month = 'sep' THEN revenue ELSE NULL END) as Sep_Revenue,
  SUM(CASE WHEN month = 'oct' THEN revenue ELSE NULL END) as Oct_Revenue,
  SUM(CASE WHEN month = 'nov' THEN revenue ELSE NULL END) as Nov_Revenue,
  SUM(CASE WHEN month = 'dec' THEN revenue ELSE NULL END) as Dec_Revenue
FROM Department
GROUP BY id
ORDER BY id;
