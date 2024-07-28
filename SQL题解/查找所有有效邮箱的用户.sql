# Write your MySQL query statement below
select * 
from Users
where mail REGEXP '^[a-zA-Z][a-zA-Z0-9_\\./\\-]*@leetcode\\.com$';

-- 正则表达式匹配
/*
REGEXP 就是 regular expression 正则表达式 的意思

^ 表示以后面的字符为开头
[] 表示括号内任意字符
- 表示连续
* 表示重复前面任意字符任意次数
\\ 用来转义后面的特殊字符，以表示字符原本的样子，而不是将其作为特殊字符使用
$ 表示以前面的字符为结尾

前缀名以字母开头：^[a-zA-Z]
前缀名包含字母（大写或小写）、数字、下划线_、句点. 和 或 横杠-：[a-zA-Z0-9\_\.\-]*
以域名'@leetcode.com'结尾：@leetcode\.com$
*/