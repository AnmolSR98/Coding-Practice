# Write your MySQL query statement below
SELECT Tree.id,
# Creating my case for whether root, inner, or leaf, referencing the Parents table to see whether a given node is in that list
(CASE WHEN Tree.p_id IS NULL THEN 'Root' # The root will always have a null p_id
      WHEN Tree.id = Parents.id AND Tree.p_id IS NOT NULL THEN 'Inner'
      ELSE 'Leaf'
      END) AS type
FROM Tree
# Creating a table of values that contains all ones that are parents
LEFT JOIN
(SELECT T1.id, T2.p_id AS parent
FROM Tree AS T1
INNER JOIN Tree AS T2 ON T1.id = T2.p_id
GROUP BY T1.id) AS Parents
ON Tree.id = Parents.id; 
