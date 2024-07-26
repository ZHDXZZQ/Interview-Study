# Write your MySQL query statement below
select contest_id, round( count(u.user_id) * 100 / 
    (select count(user_id) -- count为统计个数，如果写明了列名，则不会统计为null的行，如果为*，则会统计为null的行
    from Users), 2) as percentage
from Register as r left join Users as u
on r.user_id = u.user_id
group by r.contest_id
order by percentage desc, r.contest_id  -- r.可加可不加，因为在最后的表中仅这一列为contest_id