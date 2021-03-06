# 官方解法一：单表查询，时间 212 ms 99.05%，空间 0 B 100%
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
    SET N := N - 1;
    RETURN (
        # Write your MySQL query statement below.
        SELECT
            (SELECT DISTINCT salary
             FROM Employee
             ORDER BY salary DESC
             LIMIT N, 1)
    );
END