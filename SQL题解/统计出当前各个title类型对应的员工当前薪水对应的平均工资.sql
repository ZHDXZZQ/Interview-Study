select
    t.title,
    avg(salary)
from
    titles as t
        left join
    salaries as s
    using (emp_no)  -- 注意using要加括号
group by t.title    -- 这里为什么一定要t.？明明只有一个title列