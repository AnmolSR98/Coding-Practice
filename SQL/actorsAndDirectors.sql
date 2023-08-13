# Write your MySQL query statement below
SELECT actor_id, director_id
FROM ActorDirector
HAVING count(director_id) >= 3;s
