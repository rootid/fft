//Suppose that a website contains two tables, the Customers table and the Orders table. Write a SQL query to find all customers who never order anything.
//Table: Customers.
//+----+-------+
//| Id | Name  |
//+----+-------+
//| 1  | Joe   |
//| 2  | Henry |
//| 3  | Sam   |
//| 4  | Max   |
//+----+-------+
//Table: Orders.
//+----+------------+
//| Id | CustomerId |
//+----+------------+
//| 1  | 3          |
//| 2  | 1          |
//+----+------------+
//Using the above tables as example, return the following:
//+-----------+
//| Customers |
//+-----------+
//| Henry     |
//| Max       |
//+-----------+

#Left join
SELECT A.Name from Customers A
LEFT JOIN Orders B on  a.Id = B.CustomerId
WHERE b.CustomerId is NULL

# Left join v2
select 
c.Name from Customers c 
left join (select distinct CustomerId from Orders) o 
on c.Id=o.CustomerId 
where o.CustomerId is null;

#Subquery
SELECT A.Name from Customers A
WHERE NOT EXISTS (SELECT 1 FROM Orders B WHERE A.Id = B.CustomerId)


#Not in
SELECT A.Name from Customers A
WHERE A.Id NOT IN (SELECT B.CustomerId from Orders B)


# Schema
Create table If Not Exists Customers (Id int, Name varchar(255));
Create table If Not Exists Orders (Id int, CustomerId int);
Truncate table Customers;
insert into Customers (Id, Name) values ('1', 'Joe');
insert into Customers (Id, Name) values ('2', 'Henry');
insert into Customers (Id, Name) values ('3', 'Sam');
insert into Customers (Id, Name) values ('4', 'Max');
Truncate table Orders;
insert into Orders (Id, CustomerId) values ('1', '3');
insert into Orders (Id, CustomerId) values ('2', '1');
