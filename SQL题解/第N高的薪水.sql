CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  DECLARE offset INT;       -- 声明一个变量
  SET offset = N - 1;       -- 定义变量的值
  
  RETURN (
    SELECT DISTINCT salary
    FROM Employee
    ORDER BY salary DESC    -- 默认asc升序
    LIMIT offset, 1     -- limit x 为返回前x行。 limit y x为从第y+1行开始，返回x行。  如果没有则返回null
  );
END;
