# Write your MySQL query statement below
-- sql schema
-- Create table If Not Exists Weather (id int, recordDate date, temperature int)
-- Truncate table Weather
-- insert into Weather (id, recordDate, temperature) values ('1', '2015-01-01', '10')
-- insert into Weather (id, recordDate, temperature) values ('2', '2015-01-02', '25')
-- insert into Weather (id, recordDate, temperature) values ('3', '2015-01-03', '20')
-- insert into Weather (id, recordDate, temperature) values ('4', '2015-01-04', '30')

-- pandas schema
-- data = [[1, '2015-01-01', 10], [2, '2015-01-02', 25], [3, '2015-01-03', 20], [4, '2015-01-04', 30]]
-- weather = pd.DataFrame(data, columns=['id', 'recordDate', 'temperature']).astype({'id':'Int64', 'recordDate':'datetime64[ns]', 'temperature':'Int64'})

select w1.id
from Weather as w1, Weather as w2
where datediff(w1.recordDate, w2.recordDate) = 1
and w1.temperature > w2.temperature

-- 从两个表中查询
-- datediff计算两个日期的差距，可以是date，datetime和timestamp类型的数据，在mysql中计算的是天数差异