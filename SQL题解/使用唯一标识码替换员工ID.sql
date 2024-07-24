# Write your MySQL query statement below
select ifnull(U.unique_id, null) as unique_id, E.name 
from Employees as E left join EmployeeUNI as U
on E.id = U.id

-- left join为左连接，会显示左边表的全部列，根据on关键字连接两张表
-- 通过其别名的形式对两个表的同名列做条件，即对于左右表id相同的列拼接
-- 如果有右表中多的id，不管；左表中多的id，会出现在结果中，并且右表信息为null
-- as起别名，方便判断
-- ifnull函数为如果某字段为null，要给出的默认值，这里可以不需要ifnull函数
-- U.unique_id和E.name可以不用加，直接用unique和name是一样的