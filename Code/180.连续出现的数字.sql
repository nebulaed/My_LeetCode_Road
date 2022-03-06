# 官方解法：自联结，时间 562 ms 41.61%，空间 0 B 100%
SELECT DISTINCT l1.Num AS ConsecutiveNums
FROM Logs AS l1, Logs AS l2, Logs AS l3
WHERE l1.Id = l2.Id - 1 AND l2.Id = l3.Id - 1 AND l1.Num = l2.Num AND l2.Num = l3.Num;