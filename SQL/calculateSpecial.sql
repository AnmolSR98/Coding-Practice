# Write your MySQL query statement below
SELECT employee_id, 
  CASE WHEN (MOD(employee_id, 2) = 1 AND SUBSTRING(name, 1, 1) != 'M') THEN salary ELSE 0 END as bonus
FROM Employees;
