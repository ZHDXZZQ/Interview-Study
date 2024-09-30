select 
    answer_date,
    round(count(*) / count(distinct author_id), 2) as per_num
from answer_tb
where answer_date >= "2021-11-01" and answer_date <= "2021-11-30"   -- 判断日期范围判断
group by answer_date