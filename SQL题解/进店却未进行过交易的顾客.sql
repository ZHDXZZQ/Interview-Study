# Write your MySQL query statement below
select V.customer_id, count(V.customer_id) as count_no_trans
from Visits as V left join Transactions as T
on V.visit_id = T.visit_id
where T.transaction_id is null  -- 必须用is不能用=，因为null是一个特殊的值，表示缺失或未知，因此必须写成is null 或is not null
group by V.customer_id