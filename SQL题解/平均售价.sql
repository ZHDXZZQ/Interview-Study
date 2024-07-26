# Write your MySQL query statement below
select
     product_id, 
     ifnull(round(sum(money) / sum(cnt), 2), 0) as average_price
from (
    select 
        p.product_id,
        p.price * u.units as money, 
        u.units as cnt
    from Prices as p left join UnitsSold as u
    on  p.product_id = u.product_id
    and u.purchase_date between p.start_date and p.end_date   
    -- 这里的and不能换成where，当使用and的时候，between...and..语句在left join作用的范围内，
    -- left join具有保留左侧表的特性，UnitsSold中不存在的id也能被保留，否则null的情况将被删掉
) as id_all
group by product_id

-- 纯join为inner join 返回的是两个表中连接条件匹配的行。
-- union all是 SQL 中的一种集合操作符，用于合并两个或多个 SELECT 语句的结果集。
-- 与 UNION 不同，UNION ALL 不会去除重复的行，因此它会包含所有的行，包括重复的。