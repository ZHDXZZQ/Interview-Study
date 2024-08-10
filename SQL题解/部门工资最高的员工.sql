# Write your MySQL query statement below
select D.name as Department, E.name as Employee, E.salary as Salary -- 获取部门和薪资在部门薪资表中的员工信息
from Employee as E
left join Department as D
on E.departmentId = D.id
where (D.name, E.salary) in (       -- 子查询获取每个部门的最高薪资
    select D.name, max(salary) as top_salary
    from Employee as E
    left join Department as D
    on E.departmentId = D.id
    group by E.departmentId
)