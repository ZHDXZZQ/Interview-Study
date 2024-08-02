# Write your MySQL query statement below
    select 'Low Salary' as category, count(*) as accounts_count -- where统计总类总数利用count
    from Accounts
    where income < 20000
union
    select 'Average Salary' as category, count(*) as accounts_count
    from Accounts
    where income >= 20000 and income <= 50000
union
    select 'High Salary' as category, sum(income > 50000) as accounts_count -- sum统计种类总数
    from Accounts


-- UNION 的用法和特性
-- 合并结果集：将多个 SELECT 语句的结果合并成一个结果集。
-- 去除重复行：默认情况下，UNION 会去除重复的行。如果希望保留重复行，可以使用 UNION ALL。
-- 列数和类型匹配：所有被合并的 SELECT 语句必须有相同的列数，并且对应列的数据类型必须兼容。