# Write your MySQL query statement below
select id, count(*) as num
from (
    select requester_id as id
    from RequestAccepted
    union all   -- 必须使用all，因为union会去除重复的行
    select accepter_id as id
    from RequestAccepted
) as union_table
group by id
order by num desc 
limit 1