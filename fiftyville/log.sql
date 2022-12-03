-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Questions to answer:
-- Who the thief is,
-- What city the thief escaped to, and
-- Who the thief’s accomplice is who helped them escape

PRAGMA temp_store = 2;

-- To get details of the crime
SELECT description
FROM crime_scene_reports
WHERE month = 7
AND day = 28
AND street = "Humphrey Street"
AND description LIKE "%CS50%";

-- To get transcript of interviews
SELECT name, transcript
FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28
AND transcript LIKE "%bakery%";

-- Who are the people who own these cars at this time frame?
CREATE TEMP TABLE cars_exit
AS SELECT name as "Cars_exiting"
FROM people
WHERE name IN (
    SELECT name
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND (minute >= 15 AND minute <= 25)
        AND activity='exit')
);

-- Who withdrew money before the theft?
CREATE TEMP TABLE withdrawals
AS SELECT name as "Withdrawals"
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location='Leggett Street'
        AND transaction_type = 'withdraw'
    )
);
-- Who made the phone call?
CREATE TEMP TABLE calls
AS SELECT name AS "Calls"
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
);
CREATE TEMP TABLE passengers_flying
AS SELECT name AS "Passengers_flying"
FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (
        SELECT id
        FROM flights
        WHERE year == 2021
        AND month == 7
        AND day > 28
        AND origin_airport_id IN (
            SELECT id
            FROM airports
            WHERE city='Fiftyville'
        )
        ORDER BY hour
        LIMIT 1
    )
);
CREATE TEMP TABLE suspects
AS SELECT name
FROM people
WHERE name IN (
    SELECT Cars_exiting FROM cars_exit
)
AND
name IN (
    SELECT Withdrawals FROM withdrawals
    )
AND
name IN (
    SELECT Calls FROM calls
    )
AND
name IN (
    SELECT Passengers_flying FROM passengers_flying
);

SELECT name
FROM suspects;

SELECT name
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller IN (
        SELECT phone_number
        FROM people
        WHERE name IN (
            SELECT name FROM suspects
        )
    )
);
SELECT city
FROM airports
WHERE id=(
    SELECT destination_airport_id
    FROM flights
    WHERE year == 2021
    AND month == 7
    AND day > 28
    AND origin_airport_id IN (
        SELECT id
        FROM airports
        WHERE city='Fiftyville'
    )
    ORDER BY hour
    LIMIT 1
);
