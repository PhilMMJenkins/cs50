--write a SQL query to list the titles and release years of all Harry Potter movies, in chronological order.
SELECT title, year FROM movies WHERE TITLE LIKE "Harry Potter%" ORDER BY year;