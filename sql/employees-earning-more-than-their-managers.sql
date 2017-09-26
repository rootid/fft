#The Employee table holds all employees including their managers. Every employee has an Id, and there is also a column for the manager Id.
#+----+-------+--------+-----------+
#| Id | Name  | Salary | ManagerId |
#+----+-------+--------+-----------+
#| 1  | Joe   | 70000  | 3         |
#| 2  | Henry | 80000  | 4         |
#| 3  | Sam   | 60000  | NULL      |
#| 4  | Max   | 90000  | NULL      |
#+----+-------+--------+-----------+
#Given the Employee table, write a SQL query that finds out employees who earn more than their managers. For the above table, Joe is the only employee who earns more than his manager.
#+----------+
#| Employee |
#+----------+
#| Joe      |
#+----------+

#https://stackoverflow.com/questions/2726657/inner-join-vs-left-join-performance-in-sql-server

#Self join
select E1.Name 
from Employee as E1, Employee as E2 
where E1.ManagerId = E2.Id and E1.Salary > E2.Salary

#Inner join (Faster)
select a.Name 
from Employee a inner join Employee b on a.ManagerId=b.Id 
where a.Salary>b.Salary 


#Schema
Create table If Not Exists Employee (Id int, Name varchar(255), Salary int, ManagerId int);
Truncate table Employee;
insert into Employee (Id, Name, Salary, ManagerId) values ('1', 'Joe', '70000', '3');
insert into Employee (Id, Name, Salary, ManagerId) values ('2', 'Henry', '80000', '4');
insert into Employee (Id, Name, Salary, ManagerId) values ('3', 'Sam', '60000', 'None');
insert into Employee (Id, Name, Salary, ManagerId) values ('4', 'Max', '90000', 'None');
