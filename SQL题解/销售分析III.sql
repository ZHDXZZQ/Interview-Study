# Write your MySQL query statement below
select s.product_id, p.product_name
from Sales as s left join Product as p
on s.product_id = p.product_id
group by s.product_id   -- 要先分组再求min和max，否则不行
having min(sale_date) >= '2019-01-01' and max(sale_date) <= '2019-03-31'    -- 这里日期要加引号，且只有having而不能是where

-- WHERE 子句用于过滤从数据库中选择的行。它在数据分组 (GROUP BY) 和聚合函数（如 MIN()、MAX() 等）之前过滤行。
-- WHERE 子句不能用于过滤聚合结果。
-- HAVING 子句用于过滤分组后的结果。它在 GROUP BY 子句和聚合函数之后应用。
-- HAVING 子句可以用于过滤基于聚合函数的条件。