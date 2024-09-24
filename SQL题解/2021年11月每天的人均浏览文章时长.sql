select
    date(in_time) dt,
    round(sum(timestampdiff(second, in_time, out_time)) / count(distinct uid), 1) avg_view_len_sec  -- timestampdiff与second求时间diff
from tb_user_log
where date_format(in_time, "%Y-%m") = "2021-11" and artical_id != 0 -- 筛选时间是2021年11月的记录，采用date_format
group by dt                 -- 根据日期分类
order by avg_view_len_sec 