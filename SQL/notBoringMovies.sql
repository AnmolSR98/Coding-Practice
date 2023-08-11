# Write your MySQL query statement below
SELECT id, movie, description, rating
FROM Cinema
WHERE rating >= 8.0
AND MOD(id, 2) = 1
ORDER BY rating
DESC, rating;
