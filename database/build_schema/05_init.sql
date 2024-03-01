
INSERT INTO Account(name,surname,email, password) VALUES
	('John',    'Smith',    'john.smith@example.com'       , 'ABCDEFGH'),
	('Emma',    'Johnson',  'emma.johnson@example.com'     , 'ABCDEFGH'),
	('William', 'Brown',    'william.brown@example.com'    , 'ABCDEFGH'),
	('Olivia',  'Williams', 'olivia.williams@example.com'  , 'ABCDEFGH'),
	('James',   'Jones',    'james.jones@example.com'      , 'ABCDEFGH'),
	('Sophia',  'Davis',    'sophia.davis@example.com'     , 'ABCDEFGH');


INSERT INTO Book(title,author,publisher, genres,release_date,total_copies) VALUES
	('Harry Potter','J.K. Rowling','Bloomsbury', 'Fantasy,Young adult literature,Adventure fiction','1997-06-26 00:00:00', 10),
	('1984', 'G. Orwell','Secker & Warburg', 'Fiction,Science fiction,Mystery', '1949-06-08 00:00:00', 6),
	('Karamazov Brothers','F. Dostoevskij','The Russian Messenger', 'Fiction,Novel,Mystery,Historical fiction,Literary fiction','1980-11-01 00:00:00', 4);


INSERT INTO Loan(starting_time, ending_time, account_id, book_id) VALUES
	('2024-04-02 00:00:00','2024-04-14 00:00:00', 6, 1),
	('2024-04-07 00:00:00','2024-04-14 00:00:00', 3, 2),
	('2024-04-09 00:00:00','2024-04-14 00:00:00', 4, 1),
	('2021-04-02 00:00:00','2021-04-14 00:00:00', 6, 1);