select
    "北京" as city,
    round(avg(order_num), 3) as avg_order_num,
    round(avg(income), 3) as avg_income
from (
    select
        driver_id, count(o.order_id) as order_num, sum(fare) as income
    from
        tb_get_car_record as r
        right join
        tb_get_car_order as o
        on r.order_id = o.order_id
    where city = "北京" and order_time >= "2021-10-01" and order_time <= "2021-10-07"
    group by driver_id
    having count(o.order_id) >= 3
) as t_driver_info