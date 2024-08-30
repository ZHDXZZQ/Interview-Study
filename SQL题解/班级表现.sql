# Write your MySQL query statement below
select max(assignment1 + assignment2 + assignment3) - min(assignment1 + assignment2 + assignment3) as difference_in_score
from Scores