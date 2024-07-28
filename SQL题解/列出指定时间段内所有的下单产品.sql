# Write your MySQL query statement below
select p.product_name, sum(o.unit) as unit
from Products as p right join Orders as o
on p.product_id = o.product_id
where order_date like "2020-02-%"
group by product_name
having sum(unit) >= 100

-- 先模糊匹配筛选，再分组，分组后通过和筛选，分组也可以通过id筛选
-- 这里使用right join，就是右边全部保留
-- 结果中有重复列名的需要加表名，否则不需要