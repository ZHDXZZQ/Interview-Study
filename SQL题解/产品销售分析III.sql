# Write your MySQL query statement below
select 
    product_id,
    year as first_year,
    quantity,
    price
from sales
where (product_id, year) in (
    select 
        product_id, 
        min(year) as min_year
    from Sales
    group by product_id
) 
-- 灵活运用where 组合 in 的子查询