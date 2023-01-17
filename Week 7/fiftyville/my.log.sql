-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Since all we know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street,
-- lets first check the crime scene reports on that date and location:
SELECT description FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- There were 2 crimes that took place on humphrey street on the day, one was littering and the other was the relevant crime:
-- "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery."
-- "Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery."

-- Since we're told there is three witnesses, that would be a good place to continue.
-- The "interviews" table, contains both a transcript and a name of the witness, so we choose to connect a name to the testomony.
SELECT name, transcript FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%';
-- Ruth: Tells us the thief got in a car and left within 10 minutes of the theft. We should check security footage.
-- Eugene: Recognized the thief, using an ATM on Legget Street to withdraw cash, before he arrived at the bakery.
-- Raymond: Says the thief made a call lasting under 1 min on the phone as they were leaving. Planned to take the earliest flight out tomorrow. The reciever bought the tickets.

-- Allright, so this gave us some very good leads. Let's start with the security footage at the bakery.
-- We will get the licence plate number from the security log, and cross reference them with the names of the owners of the licence place.
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute, bakery_security_logs.activity FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25;
-- 8 People left the bakery in the relevant timeframe. They have been added to the list of suspects.

-- Next we'll follow up on Eugene and the ATM.
-- We will connect the transactions to their accounts, get the person id if the account holders, and connect that to their name.
SELECT name, atm_transactions.amount FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.transaction_type = "withdraw";
AND atm_transactions.atm_location = 'Leggett Street'
-- Another list of 8 suspects, some who also appeared on the previous list.

-- Let's follow up on Raymond next. First he said he saw the thief made a phone call that lasted under 1 minute, as he was leaving.
SELECT name, phone_calls.duration FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60;
-- This further narrows down the list of suspects. Two people have been on all lists.

-- Now lets see where was the first plane out of Fiftyville the day after the theft was headed.
SELECT airports.full_name, city, hour, minute, flights.id FROM flights
JOIN airports ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour, flights.minute
LIMIT 1;
-- Turns out the first plane was headed for New Yorkm and it's ID was 36. Now can we see who was on it?
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id = 36;
-- Another list of suspect to narrow it down.

-- If we put it all together it should be narrowed down to one suspect:
SELECT name FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25
AND atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.transaction_type = "withdraw"
AND atm_transactions.atm_location = 'Leggett Street'
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60
AND flights.id = 36;
-- Leaves us with only one candidate for being thief: Bruce! We know who is the thief, and where he left to.

-- Now lets find his accomplice by checking the recieved phone calls, of the same duration as Bruces' outgoing call.
SELECT name, phone_calls.duration FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration = 45;
-- Robin is the only person who recieved a phone call lastig exactly as long a Bruces outgoing.

-- The THIEF is: Bruce
-- The city the thief ESCAPED TO: New York
-- The ACCOMPLICE is: Robin