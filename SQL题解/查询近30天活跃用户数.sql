# Write your MySQL query statement below
select activity_date as day, count(distinct user_id) as active_users
from Activity
-- WHERE DATEDIFF('2019-07-27', activity_date) between 0 and 29  -- where 和 having都可以，二选一
group by activity_date
having DATEDIFF('2019-07-27', activity_date) between 0 and 29