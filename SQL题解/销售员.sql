# Write your MySQL query statement below
select distinct S.name
from Orders as O right join SalesPerson as S
on O.sales_id = S.sales_id 
left join Company as C
on O.com_id = C.com_id
where S.name not in (
    select S.name
    from Orders as O right join SalesPerson as S
    on O.sales_id = S.sales_id 
    left join Company as C
    on O.com_id = C.com_id
    where C.name = "RED"
)