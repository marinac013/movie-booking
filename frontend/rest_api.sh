BASE_URL="http://localhost:8080"

# 1. Health Check (Expected: 200 OK)
curl -i "$BASE_URL/api/health"

# 2. Movies List (Expected: 200 OK)
curl -i "$BASE_URL/api/movies"

# 3. Movie by ID (Expected: 200 OK)
curl -i "$BASE_URL/api/movies/1"

# 4. Movie Not Found (Expected: 404 Not Found)
curl -i "$BASE_URL/api/movies/999"

# 5. Movie Theaters (Expected: 200 OK)
curl -i "$BASE_URL/api/movies/1/theaters"

# 6. Movie Screenings (Expected: 200 OK)
curl -i "$BASE_URL/api/movies/1/screenings"

# 7. Theater Screenings (Expected: 200 OK)
curl -i "$BASE_URL/api/theaters/1/screenings"

# 8. Screening Seats (Expected: 200 OK)
curl -i "$BASE_URL/api/screenings/1/seats"

# 9. Create Booking (Expected: 201 Created)
curl -i -X POST "$BASE_URL/api/screenings/1/bookings" \
  -H "Content-Type: application/json" \
  -d '{"seatIds": [1, 2]}'

# 10. Book Already Reserved Seats (Expected: 409 Conflict)
curl -i -X POST "$BASE_URL/api/screenings/1/bookings" \
  -H "Content-Type: application/json" \
  -d '{"seatIds": [1, 2]}'

# 11. Get Booking by ID (Expected: 200 OK)
curl -i "$BASE_URL/api/bookings/1"

# 12. Booking Not Found (Expected: 404 Not Found)
curl -i "$BASE_URL/api/bookings/999"