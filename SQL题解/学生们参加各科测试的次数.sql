# Write your MySQL query statement below
select stu.student_id, stu.student_name, sub.subject_name, count(exa.subject_name) as attended_exams    -- 次数求的是exa表中的sub的和，是根据id分组后的和
from Students as stu 
cross join Subjects as sub  -- 求笛卡尔积
left join Examinations as exa   -- 结果再做左连接
on exa.student_id = stu.student_id and exa.subject_name = sub.subject_name
group by stu.student_id, sub.subject_name   -- 根据id和sub name来分组，即id相同的放一起，sub name相同的放一起，不会只根据id把所有sub name都放一起
order by stu.student_id, sub.subject_name

-- cross join为两个表做笛卡尔积，没有on来进行条件判断，而是会一一拼接