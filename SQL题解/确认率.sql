# Write your MySQL query statement below
select s.user_id, round(
    sum(CASE WHEN c.action = 'confirmed' THEN 1 ELSE 0 END) / count(*)
    , 2) as confirmation_rate
from Signups as s left join Confirmations as c
on s.user_id = c.user_id
group by s.user_id

-- 巧用case when then else end语句，记住count和sum的区别，这里要用sum，为什么？
-- CASE WHEN c.action = 'confirmed' THEN 1 ELSE 0 END


-- 之前的写法
-- select user_id, 
--     ifnull(
--         round(
--         sum(action = 'confirmed') / (sum(action = 'confirmed') + sum(action = 'timeout'))
--         , 2), 
--         0.00) as confirmation_rate from  #为什么这里得用sum，用count为什么不行
-- (select s.user_id, c.time_stamp as times, action
-- from Signups as s left join Confirmations as c
-- on s.user_id = c.user_id) as cur
-- group by user_id
-- # (sum(action = 'confirmed') + sum(action = 'timeout') 可以简化成count(action)