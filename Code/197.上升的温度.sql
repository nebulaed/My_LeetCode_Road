# 我的解法：内联结，时间 494 ms 48.61%，空间 0 B 100%
SELECT w1.id AS id
FROM Weather AS w1 INNER JOIN Weather AS w2
ON DATEDIFF(w1.recordDate, w2.recordDate) = 1 AND w2.Temperature < w1.Temperature;