# Write your MySQL query statement below
select e1.name as Employee
from Employee as e1 -- 将两个表合并，比较列的值
left join Employee as e2
on e1.managerId = e2.id
where e1.salary > e2.salary