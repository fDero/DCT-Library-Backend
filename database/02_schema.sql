
CREATE TABLE Account (
	name             VARCHAR(30) NOT NULL,
	surname          VARCHAR(40) NOT NULL,
	email            VARCHAR(50) NOT NULL,
	borrowed_books   INT         NOT NULL DEFAULT 0,
	id               SERIAL      PRIMARY KEY
);

CREATE TABLE Book (
	title            VARCHAR(150) NOT NULL,
	author           VARCHAR(100) NOT NULL,
	publisher        VARCHAR(100) NOT NULL,
	release_date     TIMESTAMP    NOT NULL,
	total_copies     INT          NOT NULL,
	borrowed_copies  INT          NOT NULL DEFAULT 0,
	id               SERIAL       PRIMARY KEY,

	CHECK(total_copies >= borrowed_copies)
);

CREATE TABLE Loan (
	starting_time TIMESTAMP NOT NULL,
	ending_time   TIMESTAMP NOT NULL,
	account_id    INT       NOT NULL,
	book_id       INT       NOT NULL,
	id            SERIAL    PRIMARY KEY,

	FOREIGN KEY (account_id)
    	REFERENCES Account(id),

	FOREIGN KEY (book_id)
	REFERENCES Book(id)
);


CREATE TABLE PastLoan (
	return_time TIMESTAMP NOT NULL
	DEFAULT CURRENT_TIMESTAMP
) INHERITS (Loan);
