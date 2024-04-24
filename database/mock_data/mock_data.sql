delete from loan cascade;
delete from pastloan cascade;
delete from account cascade;
delete from book cascade;

INSERT INTO Account(name,surname,email) VALUES
	('John',    'Smith',    'john.smith@example.com'     ),
	('Emma',    'Johnson',  'emma.johnson@example.com'   ),
	('William', 'Brown',    'william.brown@example.com'  ),
	('Olivia',  'Williams', 'olivia.williams@example.com'),
	('James',   'Jones',    'james.jones@example.com'    ),
	('Sophia',  'Davis',    'sophia.davis@example.com'   );


INSERT INTO Password (account_id, password_hash, password_salt) VALUES 
	(1, 'Q<3z^5J|0QMHKh>IMPk3@}P=|yx`k9g]', '2EwktavImkW7s0jSoJrI0YKqeS1y42pR'),
	(2, 'IU=};5AMf4gvJsphEpD=cDX_`h40W5oT', 'bElHgqeGDyl2zPKEe0t9XDRgom9iGpla'),
	(3, '5zqig;301W[>QBXg?r=D<W[S`:SpdoBu', '4gBLdGm4aXNTrHy2Jx20etMvvfhPrYXv'),
	(4, 'q@EvQ<Ng1IOfSA]ZoC8<UGDccP2DT2ky', 'GRPXUkAgBa4hD6zoeTKbL8M53d49527a'),
	(5, 'l:Esws<nLmurM_Ne}zt`jCC7k]X75{4D', 'qzxWCdkIiO1omJV4gIWLnUrx9M9chuvE'),
	(6, 'R2=VJwANkNaEVp4x}E3S>Eepa^EiGP[V', 'vwUebiufy3mYQ7t0cTH8xr8Dxzo08Plp');


INSERT INTO Book(title,author,publisher,genres,release_date,total_copies) VALUES
	('Harry Potter','J.K. Rowling','Bloomsbury', 'Fantasy,Young adult literature,Adventure fiction','1997-06-26 00:00:00', 10),
	('1984', 'G. Orwell','Secker & Warburg', 'Fiction,Science fiction,Mystery', '1949-06-08 00:00:00', 6),
	('Karamazov Brothers','F. Dostoevskij','The Russian Messenger', 'Fiction,Novel,Mystery,Historical fiction,Literary fiction','1980-11-01 00:00:00', 4),
	('Programming Principles and Practices Using C++','Bjarne Stroustrup','Pearson', 'Education','2014-05-15 00:00:00',3),
	('The Lord of the Rings','John Ronald Reuel Tolkien','George Allen and Unwin (UK) Houghton Mifflin (US)', 'Fantasy fiction,Adventure fiction', '1954-07-29 00:00:00', 2),
	('The Hunger Games','Suzanne Collins','Scholastic Press','Science fiction,Adventure fiction,Young adult literature','2008-09-14 00:00:00', 7),
    ('To Kill a Mockingbird','Harper Lee','J. B. Lippincott & Co.','Fiction,Legal drama','1960-07-11 00:00:00', 5),
    ('Pride and Prejudice','Jane Austen','T. Egerton,Whitehall','Romance,Classic','1813-01-28 00:00:00', 8),
    ('The Great Gatsby','F. Scott Fitzgerald','Charles Scribner','Fiction,Tragedy','1925-04-10 00:00:00', 3),
    ('Moby-Dick','Herman Melville','Richard Bentley','Adventure fiction,Novel','1851-10-18 00:00:00', 4),
    ('The Catcher in the Rye','J.D. Salinger','Little,Brown and Company','Fiction,Coming-of-age story','1951-07-16 00:00:00', 5),
    ('The Chronicles of Narnia','C.S. Lewis','Geoffrey Bles','Fantasy','1950-10-16 00:00:00', 6),
    ('The Hobbit','J.R.R. Tolkien','George Allen & Unwin','Fantasy,Adventure fiction','1937-09-21 00:00:00', 4),
    ('The Alchemist','Paulo Coelho','HarperOne','Fiction','1988-01-01 00:00:00', 3);
    


INSERT INTO Loan(starting_time, ending_time, account_id, book_id) VALUES
	('2024-02-15 00:00:00','2024-02-22 00:00:00', 1, 1),
	('2024-04-05 00:00:00','2024-04-18 00:00:00', 2, 2),
	('2024-04-08 00:00:00','2024-04-12 00:00:00', 3, 4),
	('2024-04-10 00:00:00','2024-04-20 00:00:00', 3, 2),
	('2024-04-11 00:00:00','2024-04-16 00:00:00', 4, 5),
	('2024-04-12 00:00:00','2024-04-18 00:00:00', 5, 1);

