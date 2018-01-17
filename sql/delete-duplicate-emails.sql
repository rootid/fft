#Write a SQL query to delete all duplicate email entries in a table named Person, keeping only unique emails based on its smallest Id.
#+----+------------------+
#| Id | Email            |
#+----+------------------+
#| 1  | john@example.com |
#| 2  | bob@example.com  |
#| 3  | john@example.com |
#+----+------------------+
#Id is the primary key column for this table.
#For example, after running your query, the above Person table should have the following rows:
#+----+------------------+
#| Id | Email            |
#+----+------------------+
#| 1  | john@example.com |
#| 2  | bob@example.com  |
#+----+------------------+

# Self join 
DELETE p1
FROM Person p1, Person p2
WHERE p1.Email = p2.Email AND
p1.Id > p2.Id


# Subquery 
DELETE FROM Person
    WHERE Id IN
    (SELECT P1.Id FROM Person AS P1, Person AS P2 
	     WHERE P1.Id > P2.Id AND P1.Email = P2.Email);

# Subquery 
delete from Person where Id not in ( select A.Id from (select min(Id) as Id from Person GROUP BY Email) A )
