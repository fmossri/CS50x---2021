SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
JOIN ratings ON ratings.movie_id = movies.id
WHERE person_id = (SELECT id FROM people WHERE name LIKE 'Chadwick Boseman')
ORDER BY rating DESC LIMIT 5;