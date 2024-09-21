SELECT tag, CONCAT(avg_play_progress, "%") as avg_play_progress -- 结果是百分号，拼接一下字符串
FROM (
    SELECT tag, 
        ROUND(AVG(  -- 所有行的结果取平均取两位小数
            IF(TIMESTAMPDIFF(SECOND, start_time, end_time) > duration, 1,   -- 完播的都按1处理
               TIMESTAMPDIFF(SECOND, start_time, end_time) / duration)      -- 计算进度比率，也可以end_time - start_time
        ) * 100, 2) as avg_play_progress
    FROM tb_user_video_log
    LEFT JOIN tb_video_info 
    USING(video_id) -- 等同于on
    GROUP BY tag
    HAVING avg_play_progress > 60   -- 筛选大于60的，降序排序
    ORDER BY avg_play_progress DESC
) as t_progress;
