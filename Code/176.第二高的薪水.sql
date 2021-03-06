# Write your MySQL query statement below

# 官方解法一：时间 248 ms 22.01%，空间 0 B 100%
SELECT
    (SELECT DISTINCT salary
     FROM Employee
     ORDER BY salary DESC
     LIMIT 1, 1) AS SecondHighestSalary;


# 官方解法二：时间 120 ms 99.90%，空间 0 B 100%
SELECT
    IFNULL(
            (SELECT DISTINCT salary
             FROM Employee
             ORDER BY salary DESC
             LIMIT 1, 1),
    NULL) AS SecondHighestSalary;