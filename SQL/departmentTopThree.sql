SELECT Department, Employee, Salary
FROM 
# getting the three highest salaries from the IT deparment using dense rank so it is inclusive
((SELECT (CASE WHEN departmentId = 1 THEN 'IT' 
        WHEN departmentId = 2 THEN "Sales"
        ELSE NULL END) AS Department,
        name AS Employee, salary as Salary, 
        DENSE_RANK() OVER(ORDER BY salary DESC) as SalaryRanking
FROM Employee
WHERE departmentId = 1
ORDER BY salary DESC)
# uniting with the equivalent table from the Sales department
UNION
(SELECT (CASE WHEN departmentId = 1 THEN 'IT' 
        WHEN departmentId = 2 THEN "Sales"
        ELSE NULL END) AS Department,
        name AS Employee, salary as Salary, 
        DENSE_RANK() OVER(ORDER BY salary DESC) as SalaryRanking
FROM Employee
WHERE departmentId = 2
ORDER BY salary DESC)) AS TopSalaries
# filtering out rank more than 3
WHERE SalaryRanking <= 3;
