# Write your MySQL query statement below
select round(
    sum(order_date = customer_pref_delivery_date) * 100 / count(*)  -- 利用sum求条件，利用count*求所有列和，会包含null情况
    , 2
) as immediate_percentage
from Delivery
where (customer_id, order_date) 
in (    -- 双重查询
    select customer_id as id, min(order_date) as first_date
    from Delivery
    group by customer_id
)   -- 无需表别名