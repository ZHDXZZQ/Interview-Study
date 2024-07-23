# Write your MySQL query statement below
select author_id as id # id是起别名
from Views
where author_id = viewer_id # 只要该行的这俩id相等，就被选中
group by viewer_id   # 这里根据author_id或id分组也可以，目的是为了结果去重
order by id # 根据id（或author_id）升序排列
-- 直接采用distinct关键字也可去重，如SELECT DISTINCT author_id AS id 。当前版本group by更快，但是8.0之后速度相当
-- 也可以使用group by 和 having来组合判断，这个之后碰到再说，降序排列也之后再说
-- 我们后面可以分析一下各用法的耗时，mysql执行每个命令的顺序以及字符类型如varchar等