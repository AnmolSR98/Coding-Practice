# Write your MySQL query statement below
SELECT Employee.name as Employee
FROM Employee, 
(SELECT id, salary 
FROM Employee 
WHERE ManagerId IS NULL) as Manager
WHERE Employee.managerId = Manager.id AND Employee.salary >= Manager.salary;
