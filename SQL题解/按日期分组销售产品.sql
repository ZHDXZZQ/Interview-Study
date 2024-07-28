# Write your MySQL query statement below
select sell_date, 
    count(distinct product) as num_sold, 
    group_concat(
        distinct product
        order by product asc
        separator ",") as products
from Activities
group by sell_date
order by sell_date

-- ORDER BY要放在group by的后面
-- DISTINCT 要去重，默认就要先排序

/*
group_concat(【distinct】 要合并的列 【order by 要排序的列 asc/desc】 【separator","】 )
SEPARATOR "," 表示返回的字段之间用逗号隔开
distinct去重  asc升序  desc降序
*/