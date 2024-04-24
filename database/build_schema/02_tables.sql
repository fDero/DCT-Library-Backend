
CREATE TABLE Account (
	account_id       SERIAL      PRIMARY KEY,
	name             VARCHAR(30) NOT NULL,
	surname          VARCHAR(40) NOT NULL,
	email            VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE Password (
	account_id	   INT NOT NULL UNIQUE,
	password_hash  VARCHAR(32) NOT NULL,
	password_salt  VARCHAR(32) NOT NULL,

	FOREIGN KEY (account_id) 
	REFERENCES Account(account_id)
);

CREATE TYPE genre_enum AS ENUM (
	'Action fiction','Adventure fiction','Autobiography','Biography', 'Classic',
	'Comedy','Coming-of-age story','Contemporary literature','Contemporary romance','Crime fiction',
	'Detective fiction','Education','Essay','Fairy tale','Fantasy','Fantasy fiction','Fiction',
	'Genre fiction','Graphic novel','Historical fiction','Historical fantasy','Historical romance',
	'History','Horror fiction','Humor','Legal drama','Literary fiction','Literary realism','Magical Realism',
	'Memoir','Mystery','Narrative','New adult fiction','Non-fiction','Novel','Philosophy','Poetry', 'Romance',
	'Romance novel','Satire','Science','Science fiction','Self-help book','Short story','Social science',
	'Speculative fiction','Spirituality','Thriller','Tragedy','Travel literature','True crime','Urban fiction',
	'Western fiction','Young adult literature'
);

CREATE TABLE Book (
	book_id          SERIAL       PRIMARY KEY,
	title            VARCHAR(150) NOT NULL,
	author           VARCHAR(100) NOT NULL,
	publisher        VARCHAR(100) NOT NULL,
	genres           VARCHAR(150) NOT NULL,
	release_date     TIMESTAMP    NOT NULL,
	total_copies     INT          NOT NULL
);

CREATE TABLE Loan (
	loan_id       SERIAL    PRIMARY KEY,
	starting_time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
	ending_time   TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP + INTERVAL '1 month',
	account_id    INT       NOT NULL,
	book_id       INT       NOT NULL,

	FOREIGN KEY (account_id)
    REFERENCES Account(account_id),

	FOREIGN KEY (book_id)
	REFERENCES Book(book_id)
);


CREATE TABLE PastLoan (
	loan_id       SERIAL    PRIMARY KEY,
	starting_time TIMESTAMP NOT NULL,
	ending_time   TIMESTAMP NOT NULL,
	account_id    INT       NOT NULL,
	book_id       INT       NOT NULL,
	return_time   TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,

	FOREIGN KEY (account_id)
    REFERENCES Account(account_id),

	FOREIGN KEY (book_id)
	REFERENCES Book(book_id)
);
