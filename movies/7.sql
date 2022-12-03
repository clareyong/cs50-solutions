SELECT title, rating
FROM (
    movies JOIN ratings
    ON movies.id = ratings.movie_id
)
WHERE year = 2010
ORDER BY rating DESC, title;

-- SELECT songs.name
-- FROM (
--     songs JOIN artists
--     ON songs.artist_id = artists.id
-- )
-- WHERE artists.name='Post Malone';