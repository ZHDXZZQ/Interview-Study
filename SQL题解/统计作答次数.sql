select
    count(*) as total_pv,
    sum(score is not null) as complete_pv,
    # count(submit_time) as complete_pv,
    count(distinct if(submit_time is not null, exam_id, null)) as complete_exam_cnt
from exam_record
