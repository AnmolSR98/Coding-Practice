# Write your MySQL query statement below
SELECT Department, Employee, Salary
FROM
# getting the three highest salaries from the IT deparment
((SELECT id, 
        (CASE WHEN departmentId = 1 THEN 'IT' 
        WHEN departmentId = 2 THEN "Sales"
        ELSE NULL END) AS Department,
        name AS Employee, salary as Salary
FROM Employee
WHERE departmentId = 1
GROUP BY salary
ORDER BY salary
LIMIT 3)
UNION 
# uniting with the three highest from the Sales department
(SELECT id, 
        (CASE WHEN departmentId = 1 THEN 'IT' 
        WHEN departmentId = 2 THEN "Sales"
        ELSE NULL END) AS Department,
        name AS Employee, salary as Salary
FROM Employee
WHERE departmentId = 2
GROUP BY salary
ORDER BY salary
LIMIT 3)) AS Salaries
GROUP BY id
ORDER BY id;
