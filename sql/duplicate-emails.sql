#Write a SQL query to find all duplicate emails in a table named Person.
#+----+---------+
#| Id | Email   |
#+----+---------+
#| 1  | a@b.com |
#| 2  | c@d.com |
#| 3  | a@b.com |
#+----+---------+
#For example, your query should return the following for the above table:
#+---------+
#| Email   |
#+---------+
#| a@b.com |
#+---------+

# Self join 
 SELECT DISTINCT a.Email
 FROM Person a JOIN Person b
 ON (a.Email = b.Email)
 WHERE a.Id <> b.Id

# Group by 
select Email
from Person
group by Email
having count(*) > 1

# Basic Idea
 SELECT DISTINCT Email FROM Person
 MINUS
 (SELECT Id, Email FROM Person GROUP BY Email)

# For Mysql  ( Minus operation replacement)
 SELECT DISTINCT a.Email FROM Person a
 LEFT JOIN (SELECT Id, Email from Person GROUP BY Email) b
 ON (a.email = b.email) AND (a.Id = b.Id)
 WHERE b.Email IS NUL


# Schema
Create table If Not Exists Person (Id int, Email varchar(255));
Truncate table Person;
insert into Person (Id, Email) values ('1', 'a@b.com');
insert into Person (Id, Email) values ('2', 'c@d.com');
insert into Person (Id, Email) values ('3', 'a@b.com');
