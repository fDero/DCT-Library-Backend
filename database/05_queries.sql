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

CREATE OR REPLACE FUNCTION loan_by_id (id_in loan.loan_id%type)
	RETURNS TABLE (
		LIKE PastLoan
	)
	AS $$
		SELECT
		*, NULL AS return_time
		FROM
		loan
		WHERE
		loan_id = id_in
	UNION
		SELECT
		*
		FROM
		Pastloan
		WHERE
		loan_id = id_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION loans_by_account_id (id_in account.account_id%type)
	RETURNS TABLE (
		LIKE PastLoan
	)
	AS $$
		SELECT
		*, NULL AS return_time
		FROM
		loan L
		WHERE
		account_id = id_in
	UNION
		SELECT
		*
		FROM
		Pastloan
		WHERE
		account_id = id_in
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION loans_by_book_id (id_in book.book_id%type)
	RETURNS TABLE (
		LIKE PastLoan
	)
	AS $$
		SELECT
		*, NULL AS return_time
		FROM
		loan L
		WHERE
		book_id = id_in
	UNION
		SELECT
		*
		FROM
		Pastloan
		WHERE
		book_id = id_in
$$
LANGUAGE SQL;