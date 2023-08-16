# Converting dep ID to a string instead 
SELECT (CASE  WHEN E.departmentId = 1 THEN 'IT'
              WHEN E.departmentId = 2 THEN 'Sales'
              ELSE NULL
              END) AS Department, 
E.name AS Employee, E.salary AS Salary
FROM Employee AS E
INNER JOIN 
# Creating a table that contains the departments maxed out salaries
(SELECT id, MAX(salary) AS Salary, departmentId FROM Employee GROUP BY departmentId) as Maxes
# Finally filtering out the rows without that salary given the dep IDs match
ON E.departmentId = Maxes.departmentId AND E.Salary = Maxes.Salary;
