# Write your MySQL query statement below

select employee_id, department_id
from Employee
where primary_flag = 'Y'
union    -- 联合查询，自动去重
select employee_id, department_id
from Employee
group by employee_id
having count(department_id) = 1

-- UNION
-- 作用: 将两个或多个 SELECT 语句的结果合并为一个结果集，并自动去除重复的行。
-- 性能: 因为需要去除重复的行，所以性能相对 UNION ALL 要差一些。

-- UNION ALL
-- 作用: 将两个或多个 SELECT 语句的结果合并为一个结果集，但不去除重复的行。