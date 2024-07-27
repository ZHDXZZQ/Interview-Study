# Write your MySQL query statement below
select employee_id
from Employees
where salary < 30000 and manager_id not in (
    select employee_id
    from Employees
)
order by employee_id

-- not in结果不在某个子查询中
-- order by执行的位置应该是查询出来后，根据select的对象选择根据谁排序，可以有排序先后优先级