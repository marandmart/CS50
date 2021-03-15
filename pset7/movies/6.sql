SELECT AVG(rating)
FROM ratings, movies
ON ratings.movie_id = movies.id
WHERE year = 2012;