# Write your MySQL query statement below
select S1.score, (  -- 外层不去重
    select count(distinct S2.score)     -- 筛选大于等于当前结果数字的去重后的数字个数，即为实际排名
    from Scores S2
    where S2.score >= S1.score
) as 'rank'     
from Scores as S1
order by S1.score desc