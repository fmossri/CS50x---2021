SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE people.id = (SELECT person_id WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004))
ORDER BY birth;