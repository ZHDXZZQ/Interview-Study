# Write your MySQL query statement below
select b.name
from Employee as a left join Employee as b
on a.managerId = b.id
where b.id is not null  -- where语句是在group by且having执行之后的
group by a.managerId
having count(*) >= 5