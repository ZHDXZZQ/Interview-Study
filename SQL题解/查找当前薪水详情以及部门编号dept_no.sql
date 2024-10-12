select
    s.emp_no,
    salary,
    from_date,
    d.to_date,
    dept_no
from dept_manager as d
    left join
    salaries as s
    using(emp_no)
order by s.emp_no