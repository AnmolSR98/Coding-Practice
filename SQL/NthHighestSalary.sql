# Standard SQL function layout
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  # returns the value where the rank is equivalent to the n that was entered
  RETURN (
      SELECT salary FROM
      # used dense_rank where to order, unclear what the specification was 
      (SELECT id, salary, DENSE_RANK() OVER(ORDER BY salary DESC) as salaryRank
      FROM Employee) as Salaries
      # ensures that only one salary will be returned
      WHERE salaryRank = N  
      );
END
