# Write your MySQL query statement below

select c1.visited_on, sum(c2.amount) as amount, round(sum(c2.amount) / 7, 2) as average_amount
from (      -- 构造新表，每个日期都对应列出7天内的所有日期
    (select distinct visited_on
    from Customer) c1
    inner join Customer c2  -- 即join
    on datediff(c1.visited_on, c2.visited_on) between 0 and 6
)
where c1.visited_on >= (    
    select min(visited_on)  -- 这可以加个date强制类型转换
    from Customer
) + 6
group by c1.visited_on
order by c1.visited_on