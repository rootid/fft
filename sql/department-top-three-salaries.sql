#The Employee table holds all employees. Every employee has an Id, and there is also a column for the department Id.
#+----+-------+--------+--------------+
#| Id | Name  | Salary | DepartmentId |
#+----+-------+--------+--------------+
#| 1  | Joe   | 70000  | 1            |
#| 2  | Henry | 80000  | 2            |
#| 3  | Sam   | 60000  | 2            |
#| 4  | Max   | 90000  | 1            |
#| 5  | Janet | 69000  | 1            |
#| 6  | Randy | 85000  | 1            |
#+----+-------+--------+--------------+
#The Department table holds all departments of the company.
#+----+----------+
#| Id | Name     |
#+----+----------+
#| 1  | IT       |
#| 2  | Sales    |
#+----+----------+
#Write a SQL query to find employees who earn the top three salaries in each of the department. For the above tables, your SQL query should return the following rows.
#+------------+----------+--------+
#| Department | Employee | Salary |
#+------------+----------+--------+
#| IT         | Max      | 90000  |
#| IT         | Randy    | 85000  |
#| IT         | Joe      | 70000  |
#| Sales      | Henry    | 80000  |
#| Sales      | Sam      | 60000  |
#+------------+----------+--------+
#With Subquery

select d.Name Department, e1.Name Employee, e1.Salary
from Employee e1 
join Department d
on e1.DepartmentId = d.Id
where 3 > (select count(distinct(e2.Salary)) 
                  from Employee e2 
                  where e2.Salary > e1.Salary 
                  and e1.DepartmentId = e2.DepartmentId
                  );

#1. Read about correlated sub queries here :http://beginner-sql-tutorial.com/sql-subquery.htm
#2. Now, for each row of the outer query:
#OuterDepartmentId, OuterEmployeeSalary is available to the inner query. The inner query will fetch all the salaries that are greater then OuterEmployeeSalary for department matching OuterDepartmentId and return a count of such distinct salaries
#3. This count can be 0,1 or 2
#if 0 -> that means there are no salaries greater then the OuterDepartmentSalary in that department. Hence, it is the greatest salary for that department. And outer query will include that OuterDepartmentId, OuterEmployeeSalary in the output.
#if 1 -> there is one salary bigger then OuterEmployeeSalary (it is the second largest salary)
#similarly for count 2, there are two larger salaries.

# With Variables
select d.Name as Department, e.Name as Employee, computed.Salary as Salary
from Employee e, 
	(
		select Salary, DepartmentId, @row := IF(DepartmentId=@did, @row + 1,1) as Rank , @did:=DepartmentId
		from (
			select distinct Salary, DepartmentId
			from Employee
			order by DepartmentId, Salary desc
			) ordered, (select @row:=0, @did:=0) variables
	) computed,
	Department d
where e.Salary=computed.Salary 
and e.DepartmentId=computed.DepartmentId 
and computed.DepartmentId=d.Id
and computed.Rank<=3
order by computed.DepartmentId, Salary desc

# Subquery
SELECT
    d.Name Department, e.Name Employee, e.Salary Salary
FROM
    (
        SELECT DepartmentId, Name, Salary 
        FROM Employee 
        WHERE 3 > (
            SELECT COUNT(e1.Salary)
            FROM (
                SELECT DISTINCT Salary, DepartmentId 
                FROM Employee 
            ) e1
            WHERE
                Employee.DepartmentId = e1.DepartmentId 
            AND
                Employee.Salary < e1.Salary
        )
        ORDER BY DepartmentId ASC, Salary DESC
    ) e 
LEFT JOIN
    Department d
ON 
    e.DepartmentId = d.Id
WHERE
    d.Name IS NOT NULL







#Schema :
Create table If Not Exists Employee (Id int, Name varchar(255), Salary int, DepartmentId int);
Create table If Not Exists Department (Id int, Name varchar(255));
Truncate table Employee;
insert into Employee (Id, Name, Salary, DepartmentId) values ('1', 'Joe', '70000', '1');
insert into Employee (Id, Name, Salary, DepartmentId) values ('2', 'Henry', '80000', '2');
insert into Employee (Id, Name, Salary, DepartmentId) values ('3', 'Sam', '60000', '2');
insert into Employee (Id, Name, Salary, DepartmentId) values ('4', 'Max', '90000', '1');
Truncate table Department;
insert into Department (Id, Name) values ('1', 'IT');
insert into Department (Id, Name) values ('2', 'Sales');
