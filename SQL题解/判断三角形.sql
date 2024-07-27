# Write your MySQL query statement below
select x, y, z, if(x + y > z && x + z > y && y + z > x, 'Yes', "No") as triangle
from Triangle

-- 字符串用单引号双引号都可以，且运算是&&不是&，或者用and，也可以用case
/*
SELECT 
    x,
    y,
    z,
    CASE
        WHEN x + y > z AND x + z > y AND y + z > x 
            THEN 'Yes'
        ELSE 'No'
    END AS 'triangle'
FROM
    triangle
;

*/