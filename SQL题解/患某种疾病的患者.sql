# Write your MySQL query statement below
select patient_id, patient_name, conditions
from Patients
where conditions like '% DIAB1%' or conditions like 'DIAB1%'
-- 模糊匹配，要匹配中间的DIAB1，即前一个病症后有一个空格
-- 同时匹配作为开头的DIAB1