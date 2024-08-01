# Write your MySQL query statement below

-- 半连接：返回第一个表中满足条件的行
select person_name
from Queue q
where (
    select sum(weight)
    from Queue
    where turn <= q.turn
) <= 1000
order by turn desc
limit 1

-- 在这段 SQL 中，半连接体现在通过子查询进行过滤，仅返回 Queue 表中满足累积权重条件的行。
-- 子查询对于 Queue 表中的每一行 q 来说，计算了 turn 小于或等于当前行 q 的 turn 值的所有行的 weight 总和（累积权重）。
-- 外部查询将上述子查询结果与 1000 进行比较，并筛选出所有累积权重小于或等于 1000 的行。

-- 相当于是基于q种的每一行的turn进行计算，对于符合要求的行保留下来