# 我的解法1：内联结，时间 408 ms 55.97%，空间 0 B 100%
SELECT e1.name AS 'Employee'
FROM Employee AS e1 INNER JOIN Employee AS e2
ON e1.managerId IS NOT NULL AND
  e1.salary > e2.salary AND
  e1.managerId = e2.id;

# 我的解法2：子查询，时间 908 ms 9.84%，空间 0 B 100%
SELECT e1.name AS 'Employee'
FROM Employee AS e1
WHERE e1.managerId IS NOT NULL AND e1.salary >
(
   SELECT salary
   FROM Employee
   WHERE id = e1.managerId
);