select t1.video_id,
       round(
            sum(end_time - start_time >= duration) / count(t1.video_id), 3
       ) as avg_comp_play_rate
from tb_user_video_log as t1 left join tb_video_info as t2
on t1.video_id = t2.video_id
where year(start_time) = 2021
group by t1.video_id
order by avg_comp_play_rate desc