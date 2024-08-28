# Write your MySQL query statement below
select U.name Name, sum(T.amount) as BALANCE
from Users as U
left join Transactions as T
on U.account = T.account
group by T.account
having sum(amount) > 10000