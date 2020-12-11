# Robbie Korneta
# Z1816167
# CSCI 466 - 1
# Assignment 6
# 10/23 11:59 PM

USE BabyName; # Switch to BabyName Database

SHOW TABLES;  # Show the tables in BabyName

SHOW COLUMNS FROM BabyName;  # Display the columns from the BabyName database

SELECT DISTINCT year FROM BabyName WHERE name = 'Robbie';  # Display the years where my name shows up

SELECT DISTINCT name FROM BabyName WHERE year = '1999';  # Show names only once from the year 1999

SELECT name FROM BabyName WHERE year = '1999' AND gender = 'M' ORDER BY count DESC LIMIT 10;  # Show most popular names from the year 1999 that were males
SELECT name FROM BabyName WHERE year = '1999' AND gender = 'F' ORDER BY count DESC LIMIT 10;  # Show Show most popular names from the year 1999 that were females

SELECT * FROM BabyName WHERE name LIKE 'Rob___' AND name != 'Robbie' ORDER BY name, count DESC, year;  # Show names and the information of each name that is similar to my name

SELECT COUNT(*) FROM BabyName;  # Show total count of all rows in database

SELECT COUNT(*) FROM BabyName WHERE year = '1972';  # Show total count of names in the year 1972

SELECT gender, COUNT(name) FROM BabyName WHERE year = '1953' GROUP BY gender;  # Show total count of names in the year 1953 of each gender

SELECT place, COUNT(name) FROM BabyName GROUP BY place;  # Show count of names by each place
