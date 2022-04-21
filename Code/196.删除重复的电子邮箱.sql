# 我的解法：自联结，时间 977 ms 18.47%，空间 0 B 100%
# 自己想时没有想到删除+自联结需要在DELETE和FROM之间写上要删除的那个表别名
# 原因：如果使用了表别名，删除时需要在DELETE和FROM之间写上表别名
DELETE p1 FROM Person AS p1 INNER JOIN Person AS p2
ON p1.id > p2.id AND p1.email = p2.email;