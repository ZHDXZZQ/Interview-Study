# Write your MySQL query statement below
select U.name, ifnull(sum(R.distance), 0) as travelled_distance
from Rides as R 
right join Users as U
on R.user_id = U.id
group by R.user_id
order by travelled_distance desc, U.name asc