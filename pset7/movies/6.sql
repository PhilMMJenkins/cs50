--write a SQL query to determine the average rating of all movies released in 2012.
SELECT AVG(ratings.rating) FROM movies JOIN ratings ON id = ratings.movie_id;