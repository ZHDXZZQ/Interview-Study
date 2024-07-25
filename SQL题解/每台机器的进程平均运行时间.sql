# Write your MySQL query statement below

SELECT machine_id, (ROUND(  -- round(a,n)函数，a保留n位小数
                        SUM( IF(activity_type='start',-timestamp,timestamp))    -- SUM是求和，IF(COND, A, B)函数为如果COND成立，返回A，否则返回B，这里求所有进程的end-start的运行时间的和
                            / 
                                COUNT(DISTINCT process_id)  -- 所有进程的运行数量，除以进程的id去重后的个数。也可以不用DISTINCT，但是要*2，因为每个进程id都有start和end两种type
                                    ,3) -- 进程的平均运行时间，保留3位小数
                                        ) AS processing_time
FROM Activity
GROUP BY machine_id
