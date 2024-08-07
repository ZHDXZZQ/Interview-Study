# Write your MySQL query statement below
(
    select name as results
    from MovieRating as MR
    left join Users as U
    on MR.user_id = U.user_id
    group by MR.user_id
    order by count(*) desc, name
    limit 1
)
union all
(
    select M.title as results
    from MovieRating as MR
    left join Movies as M
    on MR.movie_id = M.movie_id
    where created_at > "2020-01-31" and created_at < "2020-03-01"
    group by MR.movie_id
    order by avg(rating) desc, title
    limit 1
)