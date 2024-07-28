# Please write a DELETE statement and DO NOT write a SELECT statement.
# Write your MySQL query statement below

#解法1：会产生笛卡尔积，不好想，不建议
DELETE p1 
FROM Person as p1, Person as p2       /*把一张表用作两张，内连接，利用别名，as可以省略，逗号可以变成cross join*/ 
WHERE p1.email = p2.email AND p1.id > p2.id  /*删除的条件：邮件重复并且id更大就要被删*/

#解法2：好用，子查询
/*
DELETE from Person
WHERE id NOT IN #不在满足条件内的肯定就是不满足的，直接删除
(  #子查询
    SELECT ID #先把满足条件的找出来
    From
    (
     SELECT  MIN(id) as ID  #min函数
     From Person
     Group by Email  #分组
    ) cur   #必须要给表起一个别名，否则建立不出视图，跟管道不同
)
*/