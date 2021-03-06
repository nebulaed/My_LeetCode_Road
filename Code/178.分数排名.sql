# 题解一：自联结+子查询，时间 807 ms 13.55%，空间 0 B 100%
# Write your MySQL query statement below
SELECT score, (SELECT COUNT(DISTINCT s2.score)
               FROM Scores AS s2
               WHERE s2.score >= s1.score) AS 'rank'
FROM Scores AS s1
ORDER BY score DESC;


# 使用API，常用的计算序号函数，时间 309 ms 61.82%，空间 0 B 100%
# 1. rank() over: 数值相同的两位并列，但占用相应的两个名次，如 1 1 3 4 4 6
# 2. dense_rank() over: 数值相同的两位并列，共占一个名次，如 1 1 2 3 3 4
# 3. row_number() over: 不并列，即使数值相同也分名次，如 1 2 3 4 5 6
SELECT score, (dense_rank() OVER (ORDER BY score DESC)) AS 'rank'
FROM Scores;