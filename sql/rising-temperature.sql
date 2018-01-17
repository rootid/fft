#Given a Weather table, write a SQL query to find all dates' Ids with higher temperature compared to its previous (yesterday's) dates.
#+---------+------------+------------------+
#| Id(INT) | Date(DATE) | Temperature(INT) |
#+---------+------------+------------------+
#|       1 | 2015-01-01 |               10 |
#|       2 | 2015-01-02 |               25 |
#|       3 | 2015-01-03 |               20 |
#|       4 | 2015-01-04 |               30 |
#+---------+------------+------------------+
#For example, return the following Ids for the above Weather table:
#+----+
#| Id |
#+----+
#|  2 |
#|  4 |
#+----+

# Self join

SELECT wt1.Id 
FROM Weather wt1, Weather wt2
WHERE wt1.Temperature > wt2.Temperature AND 
      TO_DAYS(wt1.DATE)-TO_DAYS(wt2.DATE)=1;

# Different date function
SELECT w1.Id FROM Weather w1, Weather w2
WHERE subdate(w1.Date, 1)=w2.Date AND w1.Temperature>w2.Temperature


# With syntactic sugar interval 1 day
select cur.Id
from Weather cur
join Weather prev
on prev.Date + interval 1 day = cur.Date
where cur.Temperature > prev.Temperature


# Schema
Create table If Not Exists Weather (Id int, Date date, Temperature int);
Truncate table Weather;
insert into Weather (Id, Date, Temperature) values ('1', '2015-01-01', '10');
insert into Weather (Id, Date, Temperature) values ('2', '2015-01-02', '25');
insert into Weather (Id, Date, Temperature) values ('3', '2015-01-03', '20');
insert into Weather (Id, Date, Temperature) values ('4', '2015-01-04', '30');
