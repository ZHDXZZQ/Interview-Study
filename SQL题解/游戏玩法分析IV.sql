# Write your MySQL query statement below
select round(
    count(*) / 
    (
        select count(distinct player_id) -- 统计所有玩家数
        from Activity
    )
    ,2
) as fraction
from Activity
where (player_id, event_date) 
in (
    select player_id as id, date_add(min(event_date), interval 1 day) as first_date 
    -- date_add解决隔月加天的问题，也可以不加，也可以改为类型转换函数date，因为本来里面就是加了1day，而不是数字1
    from Activity
    group by player_id
)