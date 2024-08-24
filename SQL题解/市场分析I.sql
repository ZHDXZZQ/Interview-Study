# Write your MySQL query statement below
select  U.user_id as buyer_id, 
        U.join_date, 
        ifnull(
            sum(year(O.order_date) = '2019'), 
            0) as orders_in_2019
from Users as U
left join Orders as O
on U.user_id = O.buyer_id
group by U.user_id