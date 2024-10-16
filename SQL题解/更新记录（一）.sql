-- 本题采用两种修改方式均可，语义为『当tag为PYTHON时，修改tag为Python』，先用第一种:
UPDATE examination_info
SET tag = "Python"
WHERE tag = "PYTHON";

-- 如果采用第二种，写作：
UPDATE examination_info
SET tag = REPLACE(tag, "PYTHON", "Python")
WHERE tag = "PYTHON";


-- 思维扩展：第二种方式不仅可用于整体替换，还能做子串替换，例如要实现将tag中所有的PYTHON替换为Python（如CPYTHON=>CPython），可写作：
UPDATE examination_info
SET tag = REPLACE(tag, "PYTHON", "Python")
WHERE tag LIKE "%PYTHON%";