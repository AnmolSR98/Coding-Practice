# Setting up the initial table 
SELECT S.id, S.visit_date, S.people
FROM Stadium as S
INNER JOIN 
# Creating the table that keeps track of the previous day, filtering the ones with less than 100
(SELECT id, LAG(people, 2, NULL) OVER (ORDER BY id) AS peopleN2,
            LAG(people, 1, NULL) OVER (ORDER BY id) AS peopleN1,
            LEAD(people, 1, NULL) OVER (ORDER BY id) AS peopleP1,
            LEAD(people, 2, NULL) OVER (ORDER BY id) AS peopleP2 FROM Stadium) 
AS SP
ON S.id = SP.id AND S.people >= 100
# checking the intervals where their could be a stream of more than 100 people to check for consecutives
WHERE (SP.peopleN2 >= 100 AND SP.peopleN1 >= 100)
    OR (SP.peopleN1 >= 100 AND SP.peopleP1 >= 100)
    OR (SP.peopleP1 >= 100 AND SP.peopleP2 >= 100);
