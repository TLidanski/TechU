CREATE DATABASE IF NOT EXISTS TechTinder;
USE TechTinder;

CREATE TABLE Users (
	id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name varchar(255),
	gender varchar(10),
	isInRealationship int,
	eyeColor varchar(25),
	hairColor varchar(25),
	skinColor varchar(25),
	height varchar(25),
	weight varchar(25),
	education varchar(30),
	occupation varchar(30)
);

CREATE TABLE Interests (
	id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
	interest varchar(100)
);

CREATE TABLE User_interests (
	id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
	userId int NOT NULL,
	interestId int NOT NULL,
	CONSTRAINT FOREIGN KEY (userId) REFERENCES Users(id),
	CONSTRAINT FOREIGN KEY (interestId) REFERENCES Interests(id)
);

CREATE TABLE User_dates (
	id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
	guyId int NOT NULL,
	girlId int NOT NULL,
	dateLocation varchar(175),
	dateDuration int NOT NULL,
	haveMetAgain int,
	CONSTRAINT FOREIGN KEY (guyId) REFERENCES Users(id),
	CONSTRAINT FOREIGN KEY (girlId) REFERENCES Users(id)
);

CREATE TABLE Weddings (
	id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
	groomId int NOT NULL,
	brideId int NOT NULL,
	location varchar(125),
	CONSTRAINT FOREIGN KEY (groomId) REFERENCES Users(id),
	CONSTRAINT FOREIGN KEY (brideId) REFERENCES Users(id)
);

CREATE TABLE Wedding_guests (
	id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
	weddingId int NOT NULL,
	guestId int NOT NULL,
	CONSTRAINT FOREIGN KEY (weddingId) REFERENCES Weddings(id),
	CONSTRAINT FOREIGN KEY (guestId) REFERENCES Users(id)
);