-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
SELECT name from people JOIN stars ON people.id = stars.person_id WHERE people.name != "Kevin Bacon" AND stars.movie_id IN
(SELECT stars.movie_id from stars JOIN people ON stars.person_id = people.id WHERE people.name = "Kevin Bacon" AND people.birth = 1958) GROUP BY name;