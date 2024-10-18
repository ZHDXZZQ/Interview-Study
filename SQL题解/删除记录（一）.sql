-- 删除记录的方式汇总：

-- 根据条件删除：DELETE FROM tb_name [WHERE options] [ [ ORDER BY fields ] LIMIT n ]
-- 全部删除（表清空，包含自增计数器重置）：TRUNCATE tb_name


-- 时间差：
-- TIMESTAMPDIFF(interval, time_start, time_end)可计算time_start-time_end的时间差，单位以指定的interval为准，常用可选：
-- SECOND 秒
-- MINUTE 分钟（返回秒数差除以60的整数部分）
-- HOUR 小时（返回秒数差除以3600的整数部分）
-- DAY 天数（返回秒数差除以3600*24的整数部分）
-- MONTH 月数
-- YEAR 年数

DELETE FROM exam_record
WHERE TIMESTAMPDIFF(MINUTE, start_time, submit_time) < 5 AND score < 60;