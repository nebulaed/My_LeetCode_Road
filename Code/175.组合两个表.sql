# Write your MySQL query statement below
# 时间 209 ms 99.97%，空间 0 B 100%
SELECT FirstName, LastName, City, State
FROM Person LEFT OUTER JOIN Address
ON Person.PersonId = Address.PersonId;