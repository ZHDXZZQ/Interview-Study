# Write your MySQL query statement below
select customer_id
from Customer
-- 这里只能用分组时筛选having，而不能用分组后筛选where
-- where count(*) = (
--     select count(*)
--     from Product
-- )
group by customer_id
having count(distinct product_key) = (  -- 这里必须要去重，因为是对客户表的判断
    select count(*)
    from Product
)