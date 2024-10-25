-- 索引创建、删除与使用：

-- 1.1 create方式创建索引：
-- CREATE
--   [UNIQUE -- 唯一索引
--   | FULLTEXT -- 全文索引
--   ] INDEX index_name ON table_name -- 不指定唯一或全文时默认普通索引
--   (column1[(length) [DESC|ASC]] [,column2,...]) -- 可以对多列建立组合索引 

-- 1.2 alter方式创建索引：ALTER TABLE tb_name ADD [UNIQUE | FULLTEXT] [INDEX] index_content(content)

-- 2.1 drop方式删除索引：DROP INDEX <索引名> ON <表名>

-- 2.2 alter方式删除索引：ALTER TABLE <表名> DROP INDEX <索引名>

-- 3.1 索引的使用：

-- 索引使用时满足最左前缀匹配原则，即对于组合索引(col1, col2)，在不考虑引擎优化时，条件必须是col1在前col2在后，或者只使用col1，索引才会生效；
-- 索引不包含有NULL值的列
-- 一个查询只使用一次索引，where中如果使用了索引，order by就不会使用
-- like做字段比较时只有前缀确定时才会使用索引
-- 在列上进行运算后不会使用索引，如year(start_time)<2020不会使用start_time上的索引

-- 细节剖析：
-- 在duration列创建普通索引idx_duration；
-- 在exam_id列创建唯一性索引uniq_idx_exam_id；
-- 在tag列创建全文索引full_idx_tag；

-- 思路实现：
-- 本题可采用第1种创建方式，根据细节剖析中的点组织完整语句:

CREATE INDEX idx_duration ON examination_info(duration);
CREATE UNIQUE INDEX uniq_idx_exam_id ON examination_info(exam_id);
CREATE FULLTEXT INDEX full_idx_tag ON examination_info(tag);