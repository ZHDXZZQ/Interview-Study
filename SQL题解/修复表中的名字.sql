# Write your MySQL query statement below

select user_id, 
concat(upper(left(name, 1)), lower(substring(name,2))) as name
from Users
order by user_id

/*
left（要截取的字符串，从左截取的字符数量）
right（要截取的字符串，从右截取的字符数量）
upper（要全部变成大写字母的字符串）
lower（要全部变成小写的字符串）
substring（要截取的字符串，开始的位置【是个数不是下标】，结束的位置【默认为结尾】）
length（要求长度的字符串）
concat（要拼接的字符串1，要拼接的字符串2）
*/