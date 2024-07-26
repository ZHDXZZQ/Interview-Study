# Write your MySQL query statement below
select id, movie, description, round(rating, 2) as rating
from cinema
where description != 'boring' and id % 2 = 1
order by rating desc
-- desc为降序排序
-- %为取模