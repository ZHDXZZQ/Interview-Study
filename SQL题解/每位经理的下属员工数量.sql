# Write your MySQL query statement below
select b.reports_to as employee_id, a.name, count(a.employee_id) as reports_count, round(avg(b.age), 0) as average_age
from Employees as a join Employees as b
on a.employee_id = b.reports_to
group by b.reports_to   -- 根据经理分组，统计经理相同的人的平均年龄，注意select中的a和b的表的不同点
order by employee_id

-- join 即inner join，仅连接两边都不为null的项