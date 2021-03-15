SELECT people.name
FROM people, movies, stars
ON people.id = stars.person_id and stars.movie_id = movies.id
WHERE movies.title = "Toy Story";