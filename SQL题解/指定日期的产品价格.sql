# Write your MySQL query statement below

select p1.product_id, ifnull(p2.new_price, 10) as price
from (
    select distinct product_id
    from Products
) as p1     -- 先列出所有产品，作为左连接，没有更新价格的则会为null
left join (
    select product_id, new_price    -- 拿出所有产品的该日期前的最后更新价格
    from Products
    where (product_id, change_date) in (    -- 选出每个产品的指定日期前的最后更新日期
        select product_id, max(change_date) as update_date
        from Products
        where change_date <= '2019-08-16'
        group by product_id
    )
) as p2
on p1.product_id = p2.product_id