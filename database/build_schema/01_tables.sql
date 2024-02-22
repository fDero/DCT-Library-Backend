
CREATE TABLE Account (
	account_id       SERIAL      PRIMARY KEY,
	name             VARCHAR(30) NOT NULL,
	surname          VARCHAR(40) NOT NULL,
	email            VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE Book (
	book_id          SERIAL       PRIMARY KEY,
	title            VARCHAR(150) NOT NULL,
	author           VARCHAR(100) NOT NULL,
	publisher        VARCHAR(100) NOT NULL,
	release_date     TIMESTAMP    NOT NULL,
	total_copies     INT          NOT NULL
);

CREATE TABLE Loan (
	loan_id       SERIAL    PRIMARY KEY,
	starting_time TIMESTAMP NOT NULL,
	ending_time   TIMESTAMP NOT NULL,
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