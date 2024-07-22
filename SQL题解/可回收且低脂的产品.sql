-- select 语句用于查找结果表的列
-- from 为查询的表
-- where 为条件查询
# Write your MySQL query statement below
select product_id
from Products
where low_fats = 'Y' and recyclable = 'Y'