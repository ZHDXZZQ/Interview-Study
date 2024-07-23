# Write your MySQL query statement below
select tweet_id
from Tweets
where length(content) > 15
-- length函数写成CHAR_LENGTH(content) > 15也可以，用于统计VARCHAR的字符数量