# Write your MySQL query statement below
SELECT AllEmp.employee_id
# Table for all employees
FROM (SELECT * FROM Employees LEFT JOIN Salaries USING(employee_id) 
    UNION 
  SELECT * FROM Employees RIGHT JOIN Salaries USING(employee_id)) as AllEmp
WHERE AllEmp.salary IS NULL OR AllEmp.name IS NULL
ORDER BY AllEmp.employee_id;
