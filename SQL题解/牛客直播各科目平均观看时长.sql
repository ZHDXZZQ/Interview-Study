SELECT 
    c.course_name,
    ROUND(AVG(TIMESTAMPDIFF(MINUTE, a.in_datetime, a.out_datetime)), 2) AS avg_Len  -- timestampdiff在分钟级别的应用
FROM 
    course_tb AS c
    LEFT JOIN 
    attend_tb AS a
    ON c.course_id = a.course_id
GROUP BY 
    c.course_name
ORDER BY 
    avg_Len DESC;
