# Robbie Korneta
# Z1816167
# CSCI 466 - 1
# Assignment 5
# 10/07 11:59 PM

DROP TABLE visits;	-- Remove the table visits
DROP TABLE dogs;	-- Remove the table dogs

# Create dogs table with DOGID as the primary key,
# and BREED and NAME as attributes
CREATE TABLE dogs(

	DOGID INT      PRIMARY KEY AUTO_INCREMENT, 
	BREED CHAR(30) NOT NULL, 
	NAME  CHAR(30) NOT NULL

);

# Insert data into the dogs table
INSERT INTO dogs (BREED, NAME) VALUES 

	('German Shepherd', 	'Lucy'), 
	('Yorkie', 		'Rocky'), 
	('Rotweiler', 		'Rex'), 
	('Brindle', 		'Brinny'), 
	('Dalmation', 		'Spotty');

DESCRIBE dogs;		-- Show the dogs table

SELECT * FROM dogs;	-- Show the data inside dogs table

# Create visits table with VISIT as the primary key,
# and DOGID as a foreign key
# Create attribute DATE representing the date of the visit
CREATE TABLE visits(

	VISITID INT  PRIMARY KEY AUTO_INCREMENT, 
	DOGID   INT  NOT NULL, 
	DATE    DATE NOT NULL, 

	FOREIGN KEY (DOGID) REFERENCES dogs(DOGID)

);

#Insert data into visits
INSERT INTO visits (DOGID, DATE) VALUES 

	(3, '2020-08-22'), 
	(1, '2020-08-22'), 
	(5, '2020-08-22'), 
	(1, '2020-08-28'), 
	(3, '2020-08-29'), 
	(4, '2020-08-30'), 
	(2, '2020-09-02'), 
	(1, '2020-09-05');

DESCRIBE visits;		-- Show the visits table

SELECT * FROM visits;	-- Show the data inside the visits table

ALTER TABLE visits ADD TIME TIME; -- Add a time attribute to visits

# Update the new columns for each visit with the time of the visit
UPDATE visits SET TIME = '12:00:00' WHERE VISITID=1;
UPDATE visits SET TIME = '13:00:00' WHERE VISITID=2;
UPDATE visits SET TIME = '14:00:00' WHERE VISITID=3;
UPDATE visits SET TIME = '09:00:00' WHERE VISITID=4;
UPDATE visits SET TIME = '10:00:00' WHERE VISITID=5;
UPDATE visits SET TIME = '12:00:00' WHERE VISITID=6;
UPDATE visits SET TIME = '11:00:00' WHERE VISITID=7;
UPDATE visits SET TIME = '10:00:00' WHERE VISITID=8;

SELECT * FROM visits; -- Print data in visits
