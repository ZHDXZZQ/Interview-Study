# Write your MySQL query statement below
select max(salary) as SecondHighestSalary
from Employee
where salary < (
    select max(salary) as money
    from Employee
)

-- select ifnull(
--     (select distinct salary
--     from Employee
--     order by salary desc
--     limit 1, 1)
--     , null
-- ) as SecondHighestSalary

/*
ifnull就是如果为不为空，返回第一个，否则返回第二个
limit总结
1.单参数：limit x，返回前x个
2.双参数使用：limit [offset] [count]，跳过头offset个，返回其后的count个
3.搭配OFFSET使用：limit [count] offset [offset]，跳过offset个，返回气候count个
*/