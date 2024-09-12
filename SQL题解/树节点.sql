SELECT id, 
       CASE 
           WHEN p_id IS NULL THEN 'Root'
           WHEN id NOT IN (SELECT DISTINCT p_id FROM Tree WHERE p_id IS NOT NULL) THEN 'Leaf'
           ELSE 'Inner'
       END AS type
FROM Tree;
-- 巧妙应用case when then else end语法