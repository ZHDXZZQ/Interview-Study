# Write your MySQL query statement below
select query_name, 
       round(avg(rating / position), 2) as quality,     -- as可以省略
       round(avg(rating < 3) * 100, 2) as poor_query_percentage -- avg可以直接跟条件筛选求平均值
from Queries
where query_name is not null
group by query_name