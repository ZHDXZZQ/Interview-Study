# Write your MySQL query statement below
select DATE_FORMAT(trans_date, '%Y-%m') AS month,  -- 精确到月
       country,
       count(*) as trans_count,
       sum(state = "approved") as approved_count,       -- COUNT(IF(state = 'approved', 1, NULL)) AS approved_count,
       sum(amount) as trans_total_amount,
       sum(if(state = "approved", amount, 0)) as approved_total_amount
from Transactions
group by month, country