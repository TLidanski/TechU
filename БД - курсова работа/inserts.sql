INSERT INTO Users VALUES (1, "Vladimir Vladimirovich Putin", "Male", 0, "Blue", "Blonde", "White", "168", "71", "Bachelor", "Prez");
INSERT INTO Users VALUES (2, "Donald J Trump", "Male", 1, "Blue", "Blonde", "White", "190", "107", "Master", "Prez");
INSERT INTO Users VALUES (3, "Dixie B Normous", "Female", 1, "Green", "Blonde", "Black", "160", "120", "Highschool", "Store clerk");
INSERT INTO Users VALUES (4, "Brownie Potty Shytles", "Female", 0, "Blue", "White", "White", "170", "67", "Master", "Retired");
INSERT INTO Users VALUES (5, "Peter M Bonerz", "Male", 1, "Brown", "Brown", "White", "180", "90", "Bachelor", "Director");
INSERT INTO Users VALUES (6, "Mike D Litoris", "Male", 0, "Brown", "Brown", "White", "178", "96", "Highshool", "Neighborhood drunk");
INSERT INTO Users VALUES (7, "Yolanda L Squatpump", "Female", 1, "Brown", "Blonde", "White", "150", "107", "Bachelor", "Actress");

INSERT INTO Interests VALUES (1, "Drinking");
INSERT INTO Interests VALUES (2, "Reading");
INSERT INTO Interests VALUES (3, "Annexing");
INSERT INTO Interests VALUES (4, "Lowering Taxes");
INSERT INTO Interests VALUES (5, "Watching movies");
INSERT INTO Interests VALUES (6, "Driving");
INSERT INTO Interests VALUES (7, "Singing");
INSERT INTO Interests VALUES (8, "Walls");

INSERT INTO User_interests VALUES (1, 1, 2);
INSERT INTO User_interests VALUES (2, 1, 3);
INSERT INTO User_interests VALUES (3, 1, 6);
INSERT INTO User_interests VALUES (4, 2, 4);
INSERT INTO User_interests VALUES (5, 2, 8);
INSERT INTO User_interests VALUES (6, 2, 5);
INSERT INTO User_interests VALUES (7, 2, 2);

INSERT INTO User_interests VALUES (8, 3, 1);
INSERT INTO User_interests VALUES (9, 3, 5);

INSERT INTO User_interests VALUES (10, 4, 5);
INSERT INTO User_interests VALUES (11, 4, 6);
INSERT INTO User_interests VALUES (12, 4, 2);

INSERT INTO User_interests VALUES (13, 5, 5);
INSERT INTO User_interests VALUES (14, 5, 6);

INSERT INTO User_interests VALUES (15, 6, 1);
INSERT INTO User_interests VALUES (16, 6, 2);

INSERT INTO User_interests VALUES (17, 7, 2);
INSERT INTO User_interests VALUES (18, 7, 5);
INSERT INTO User_interests VALUES (19, 7, 7);

INSERT INTO User_dates VALUES (1, 1, 4, "Kremlin", 120, 0) ON DUPLICATE KEY UPDATE haveMetAgain = 1;
INSERT INTO User_dates VALUES (2, 1, 7, "Kremlin", 120, 0) ON DUPLICATE KEY UPDATE haveMetAgain = 1;
INSERT INTO User_dates VALUES (3, 1, 4, "Kremlin", 120, 1) ON DUPLICATE KEY UPDATE haveMetAgain = 1;

INSERT INTO User_dates VALUES (4, 2, 3, "White house", 180, 0) ON DUPLICATE KEY UPDATE haveMetAgain = 1;
INSERT INTO User_dates VALUES (5, 2, 3, "White house", 180, 1) ON DUPLICATE KEY UPDATE haveMetAgain = 1;
INSERT INTO User_dates VALUES (6, 2, 3, "White house", 180, 1) ON DUPLICATE KEY UPDATE haveMetAgain = 1;

INSERT INTO User_dates VALUES (7, 5, 7, "A bar", 60, 0) ON DUPLICATE KEY UPDATE haveMetAgain = 1;
INSERT INTO User_dates VALUES (8, 5, 7, "Another bar", 60, 1) ON DUPLICATE KEY UPDATE haveMetAgain = 1;
INSERT INTO User_dates VALUES (9, 5, 7, "Yet another bar", 60, 1) ON DUPLICATE KEY UPDATE haveMetAgain = 1;

INSERT INTO Wedding_guests (weddingId, guestId) VALUES (1, 1);
INSERT INTO Wedding_guests (weddingId, guestId) VALUES (1, 4);
INSERT INTO Wedding_guests (weddingId, guestId) VALUES (1, 5);
INSERT INTO Wedding_guests (weddingId, guestId) VALUES (1, 6);
INSERT INTO Wedding_guests (weddingId, guestId) VALUES (1, 7);

INSERT INTO Wedding_guests (weddingId, guestId) VALUES (2, 3);
INSERT INTO Wedding_guests (weddingId, guestId) VALUES (2, 4);
INSERT INTO Wedding_guests (weddingId, guestId) VALUES (2, 6);
INSERT INTO Wedding_guests (weddingId, guestId) VALUES (2, 7);

UPDATE Weddings SET location = "White house" WHERE id = 1;
UPDATE Weddings SET location = "The Bar" WHERE id = 2;