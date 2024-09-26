select
    style_id,
    count(*) as SPU_num
from product_tb
group by style_id
order by SPU_num desc