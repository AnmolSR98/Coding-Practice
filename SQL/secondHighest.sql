# converting that empty value to a null
SELECT IFNULL(
# created a table where it will leave a blank if there is no 2nd highest
(SELECT salary
FROM Employee 
ORDER BY salary DESC LIMIT 1 OFFSET 1), NULL)
AS SecondHighestSalary;
