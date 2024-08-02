# Write your MySQL query statement below
select if(id % 2 = 1, 
            if(id + 1 in (select id from Seat), 
                id + 1, 
                id), 
            id - 1) as id, student
from Seat
order by id

-- if(condition, true_value, false_value)