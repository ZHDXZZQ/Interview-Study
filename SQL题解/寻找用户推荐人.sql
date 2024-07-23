# Write your MySQL query statement below
select name
from Customer
where referee_id != 2 or referee_id is null
-- is 不可以写成 =
-- != 可以写成 <>