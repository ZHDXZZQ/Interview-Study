-- 这题很简单，主要考察的是SQL插入多行数据的方法，为了方便理解后面用中文进行填写（不是很规范），即：

-- INSERT INTO tab_name (col_name) VALUES (要插入的数据,这里是第一行数据), (要插入的数据,这里是第二行数据)...(要插入的数据，第n行数据);
-- 但是我们要注意题目中的两个小细节：

-- 第一个就是插入的表格存在自增主键alt 这里的id是自增主键（PRIMARY KEY)，这就意味着不需要你自己手动填入，它会跟随表格行数进行自己增加（比如这样增加id值 1，2，3...n）。
-- 所以我们在插入数据的时候，方法之一： 可以指定插入的列名， 这样就不用填写id这一列的数据，让他自增。具体插入代码如下：

INSERT INTO exam_record (uid, exam_id, start_time, submit_time, score) VALUES
(1001, 9001, '2021-09-01 22:11:12', '2021-09-01 23:01:12', 90),
(1002, 9002, '2021-09-04 07:01:02', NULL, NULL);

-- 方法之二：把id的值设置为NULL或0，这样MySQL会自己处理这个自增的id列。 具体代码如下：

-- INSERT INTO exam_record VALUES
-- (NULL, 1001, 9001, '2021-09-01 22:11:12', '2021-09-01 23:01:12', 90),
-- (NULL, 1002, 9002, '2021-09-04 07:01:02', NULL, NULL);


-- 其实还有一个方法三：直接填入id值，不过仅针对插入数据不多的时候使用，大家了解一下：

-- INSERT INTO exam_record VALUES
-- (1, 1001, 9001, '2021-09-01 22:11:12', '2021-09-01 23:01:12', 90),
-- (2, 1002, 9002, '2021-09-04 07:01:02', NULL, NULL);

-- 第二个细节就是这句“在10分钟后退出了平台”，以及表格创建的这里的YES
-- 这两个地方都表明了用户1002是没有做完试卷就结束了考试。 所以submit_time 和score这两列都填NULL即可。