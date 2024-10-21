-- 1.1 直接创建表：
-- CREATE TABLE
-- [IF NOT EXISTS] tb_name -- 不存在才创建，存在就跳过
-- (column_name1 data_type1 -- 列名和类型必选
--   [ PRIMARY KEY -- 可选的约束，主键
--    | FOREIGN KEY -- 外键，引用其他表的键值
--    | AUTO_INCREMENT -- 自增ID
--    | COMMENT comment -- 列注释（评论）
--    | DEFAULT default_value -- 默认值
--    | UNIQUE -- 唯一性约束，不允许两条记录该列值相同
--    | NOT NULL -- 该列非空
--   ], ...
-- ) [CHARACTER SET charset] -- 字符集编码
-- [COLLATE collate_value] -- 列排序和比较时的规则（是否区分大小写等）

-- 1.2 从另一张表复制表结构创建表： CREATE TABLE tb_name LIKE tb_name_old

-- 1.3 从另一张表的查询结果创建表： CREATE TABLE tb_name AS SELECT * FROM tb_name_old WHERE options

-- 2.1 修改表：ALTER TABLE 表名 修改选项 。选项集合：

-- { ADD COLUMN <列名> <类型>  -- 增加列
--  | CHANGE COLUMN <旧列名> <新列名> <新列类型> -- 修改列名或类型
--  | ALTER COLUMN <列名> { SET DEFAULT <默认值> | DROP DEFAULT } -- 修改/删除 列的默认值
--  | MODIFY COLUMN <列名> <类型> -- 修改列类型
--  | DROP COLUMN <列名> -- 删除列
--  | RENAME TO <新表名> -- 修改表名
--  | CHARACTER SET <字符集名> -- 修改字符集
--  | COLLATE <校对规则名> } -- 修改校对规则（比较和排序时用到）

-- 3.1 删除表：DROP TABLE [IF EXISTS] 表名1 [ ,表名2]。

-- 细节剖析：
-- 自增ID：AUTO_INCREMENT；
-- 设置主键：PRIMARY KEY；
-- 唯一性约束：UNIQUE
-- 非空约束：NOT NULL
-- 设置默认值：DEFAULT 0
-- 当前时间戳：CURRENT_TIMESTAMP
-- 评论/注释：COMMENT
-- 如果该表已创建过，正常返回：IF NOT EXISTS

-- 思路实现：
-- 本题采用第1种创建方式，根据细节剖析中的点组织完整创建语句:
CREATE TABLE IF NOT EXISTS user_info_vip (
    id int PRIMARY KEY AUTO_INCREMENT COMMENT '自增ID',
    uid int UNIQUE NOT NULL COMMENT '用户ID',
    nick_name varchar(64) COMMENT '昵称',
    achievement int DEFAULT 0 COMMENT '成就值',
    `level` int COMMENT '用户等级',
    job varchar(32) COMMENT '职业方向',
    register_time datetime DEFAULT CURRENT_TIMESTAMP COMMENT '注册时间'
) CHARACTER SET utf8 COLLATE utf8_general_ci;