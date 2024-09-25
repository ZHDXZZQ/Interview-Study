select
    date_format(event_time, "%Y-%m") as month,
    sum(total_amount) as GMV
from tb_order_overall
where year(event_time) = 2021 and (status = 1 or status = 0)
group by date_format(event_time, "%Y-%m")   -- 注意不能简单根据月份分类
having sum(total_amount) > 100000   -- 注意having语句的用法
order by GMV