# Write your MySQL query statement below
select D.name as Department, E.name as Employee, E.salary as Salary
from Employee as E 
left join   -- 也可以使用join自连接
Department as D
on E.departmentId = D.id
where ( -- 根据该条件筛选外层的行
    select count(DISTINCT EE.salary)
    from Employee as EE
    where EE.salary > E.salary and E.departmentId = EE.departmentId -- 统计子查询中，该部门的工资比该员工的工资高的种类的总数
) < 3
-- 统计子表中该员工同部门的所有工资，如果该部门比该员工的工资高的薪水种类<3，即只有0，1，2种工资比他高，说明他的工资位列前三，筛选出
-- 应该也可以先统计出来每个部门的前三工资，然后匹配是否属于该部门的前三工资。