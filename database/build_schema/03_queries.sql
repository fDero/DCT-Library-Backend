CREATE OR REPLACE FUNCTION num_loans_for_account(ID_in account.account_id%type)
  RETURNS INT
	AS $$
	SELECT 
		COUNT(*) 
	FROM 
		Loan  L 
	WHERE 
		L.account_id = ID_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION num_loans_for_book(ID_in book.book_id%type)
  RETURNS INT
	AS $$
	SELECT 
		COUNT(*) 
	FROM 
		Loan  L 
	WHERE 
		L.book_id = ID_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION account_by_id (ID_in account.account_id%type)
	RETURNS TABLE (
		LIKE account
	)
	AS $$
	SELECT
		*
	FROM
		account
	WHERE
		account_id = ID_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION account_by_email (email_in account.email%type)
	RETURNS TABLE (
		LIKE account
	)
	AS $$
	SELECT
		*
	FROM
		account
	WHERE
		email = email_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION accounts_by_book_id (id_in book.book_id%type)
	RETURNS TABLE (
		LIKE account
	)
	AS $$
	SELECT
		A.*
	FROM
		account A
	NATURAL JOIN loan L
	WHERE
		L.book_id = id_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION account_by_loan_id (id_in loan.loan_id%type)
	RETURNS TABLE (
		LIKE account
	)
	AS $$
	SELECT
		A.*
	FROM
		account A
	NATURAL JOIN loan L
	WHERE
		L.loan_id = id_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION book_by_id (id_in loan.loan_id%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		book_id = id_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_account_id (id_in account.account_id%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		B.*
	FROM
		book B
	NATURAL JOIN loan L
	WHERE
		L.account_id = id_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION book_by_loan_id (id_in loan.loan_id%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		B.*
	FROM
		book B
	NATURAL JOIN loan L
	WHERE
		L.loan_id = id_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_title (title_in book.title%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		title = title_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_author (author_in book.author%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		author = author_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_publisher (publisher_in book.publisher%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		publisher = publisher_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_release_date (release_date_in book.release_date%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		release_date = release_date_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_title_and_author (title_in book.title%type, author_in book.author%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		title = title_in AND
		author = author_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_title_and_publisher (title_in book.title%type, pub_in book.publisher%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		title = title_in AND
		publisher = pub_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_title_and_release_date (title_in book.title%type, release_date_in book.release_date%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		title = title_in AND
		release_date = release_date_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_author_and_publisher (author_in book.author%type, pub_in book.publisher%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		author = author_in AND
		publisher = pub_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_author_and_release_date (author_in book.author%type, release_date book.release_date%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		author = author_in AND
		release_date = release_date
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_publisher_and_release_date (pub_in book.publisher%type, release_date book.release_date%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		publisher = pub_in AND
		release_date = release_date
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_title_and_author_and_publisher (title_in book.title%type, author_in book.author%type, pub_in book.publisher%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		title = title_in AND
		author = author_in AND
		publisher = pub_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_title_and_author_and_release_date (title_in book.title%type, author_in book.author%type, release_date_in book.release_date%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		title = title_in AND
		author = author_in AND
		release_date = release_date_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_title_and_publisher_and_release_date (title_in book.title%type, pub_in book.publisher%type, release_date_in book.release_date%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		title = title_in AND
		publisher = pub_in AND
		release_date = release_date_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION books_by_author_and_publisher_and_release_date (author_in book.author%type, pub_in book.publisher%type, release_date_in book.release_date%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		author = author_in AND
		publisher = pub_in AND
		release_date = release_date_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION loan_by_id (id_in loan.loan_id%type)
	RETURNS TABLE (
		LIKE Loan
	)
	AS $$
		SELECT
		*
		FROM
		loan
		WHERE
		loan_id = id_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION loans_by_account_id (id_in account.account_id%type)
	RETURNS TABLE (
		LIKE Loan
	)
	AS $$
		SELECT
		*
		FROM
		loan
		WHERE
		account_id = id_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION loans_by_book_id (id_in book.book_id%type)
	RETURNS TABLE (
		LIKE Loan
	)
	AS $$
		SELECT
		*
		FROM
		loan
		WHERE
		book_id = id_in
$$
LANGUAGE SQL;