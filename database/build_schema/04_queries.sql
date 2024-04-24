CREATE OR REPLACE FUNCTION insert_account(name_in account.name%type, surname_in account.surname%type, email_in account.email%type, password_in password.password_hash%type, salt_in password.password_salt%type)
  RETURNS account.account_id%type
    AS $$
    DECLARE
        new_id account.account_id%type;
    BEGIN
        INSERT INTO account(name, surname, email) VALUES(name_in, surname_in, email_in) RETURNING account_id INTO new_id;
        INSERT INTO password(account_id, password_hash, password_salt) VALUES(new_id, password_in, salt_in);
        RETURN new_id;
    EXCEPTION
        WHEN unique_violation THEN
            RAISE EXCEPTION 'Email exists' USING ERRCODE = get_global('account_email_exists');
    END;
$$
LANGUAGE PLPGSQL;

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

CREATE OR REPLACE FUNCTION select_n_accounts (n int)
	RETURNS TABLE (
		LIKE account
	)
	AS $$
	BEGIN
		IF(n IS NOT NULL) THEN
			RETURN QUERY SELECT * FROM account LIMIT n;
		ELSE
			RETURN QUERY SELECT * FROM account;
		END IF;
	END;
$$
LANGUAGE PLPGSQL;

CREATE OR REPLACE FUNCTION select_n_books (n int)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	BEGIN
		IF(n IS NOT NULL) THEN
			RETURN QUERY SELECT * FROM book LIMIT n;
		ELSE
			RETURN QUERY SELECT * FROM book;
		END IF;
	END;
$$
LANGUAGE PLPGSQL;

CREATE OR REPLACE FUNCTION select_n_loans (n int)
	RETURNS TABLE (
		LIKE loan
	)
	AS $$
	BEGIN
		IF(n IS NOT NULL) THEN
			RETURN QUERY SELECT * FROM loan LIMIT n;
		ELSE
			RETURN QUERY SELECT * FROM loan;
		END IF;
	END;
$$
LANGUAGE PLPGSQL;

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

CREATE OR REPLACE FUNCTION books_by_data_match (ids_in integer[], title_in book.title%type, author_in book.author%type, publisher_in book.publisher%type, genres_in book.genres%type, release_date_in book.release_date%type, limit_val int)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	DECLARE
		query_string text;
	BEGIN
		query_string := 'SELECT * FROM book WHERE TRUE';

		IF array_length(ids_in, 1) > 0 THEN
			query_string := query_string || ' AND book_id = ANY(' || quote_literal(ids_in) || ')';
		END IF;

		IF title_in != '' THEN
			query_string := query_string || ' AND title LIKE ' || quote_literal(title_in || '%');
		END IF;

		IF author_in != '' THEN
			query_string := query_string || ' AND author LIKE ' || quote_literal(author_in || '%');
		END IF;

		IF publisher_in != '' THEN
			query_string := query_string || ' AND publisher LIKE ' || quote_literal(publisher_in || '%');
		END IF;

		IF genres_in  != '' THEN
			query_string := query_string || ' AND TRIM(BOTH '','' FROM ' || quote_literal(genres_in) || ') <> '''' AND string_to_array(' || quote_literal(genres_in) || ', '','') ' || ' <@ string_to_array(genres, '','')';
		END IF;

		IF release_date_in IS NOT NULL THEN
			query_string := query_string || ' AND release_date = ' || quote_literal(release_date_in);
		END IF;

		IF limit_val IS NOT NULL THEN
			query_string := query_string || ' LIMIT ' || limit_val;
		END IF;

		RETURN QUERY EXECUTE query_string;
	END;
$$
LANGUAGE PLPGSQL;


CREATE OR REPLACE FUNCTION books_by_ids (ids_in integer[])
	RETURNS TABLE (
		LIKE book
	)
	AS $$
	SELECT
		*
	FROM
		book
	WHERE
		book_id = ANY(ids_in)
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION book_by_id (id_in book.book_id%type)
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

CREATE OR REPLACE FUNCTION books_by_genres (genres_in Book.genres%type)
	RETURNS TABLE (
		LIKE book
	)
	AS $$
		BEGIN
			IF (TRIM(BOTH ',' FROM genres_in) <> '') THEN
				RETURN QUERY
					SELECT
						*
					FROM
						book B
					WHERE
						string_to_array(genres_in, ',') <@ string_to_array(B.genres, ',');
			END IF;
			RETURN;
		END;
$$
LANGUAGE PLPGSQL;

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

CREATE OR REPLACE FUNCTION expired_loans_by_account_id(account_id_in account.account_id%type)
	RETURNS TABLE (
		LIKE Loan
	)
	AS $$
	SELECT
		*
	FROM
		Loan
	WHERE
		Loan.account_id = account_id_in AND
		Loan.ending_time < CURRENT_TIMESTAMP
$$
LANGUAGE SQL;

CREATE OR REPLACE FUNCTION extract_account_salt(in_email Account.email%type)
  RETURNS Password.password_salt%type
	AS $$
	DECLARE
		salt Password.password_salt%type;
	BEGIN
		SELECT Password.password_salt INTO salt 
		FROM Password, Account 
		WHERE Account.email = in_email AND Password.account_id = Account.account_id; 

		RETURN salt;
	END
$$
LANGUAGE PLPGSQL;

CREATE OR REPLACE FUNCTION validate_account(in_email Account.email%type, in_password Password.password_hash%type)
  RETURNS Account.account_id%type
	AS $$
	DECLARE
		selected_account Password%rowtype;
	BEGIN
		SELECT Password.account_id, Password.password_hash INTO selected_account 
		FROM Account, Password 
		WHERE Account.email = in_email AND Account.account_id = Password.account_id;

		IF (selected_account IS NULL) THEN
			RETURN get_global('account_id_not_found');
		END IF; 

		IF (selected_account.password_hash = in_password) THEN
			RETURN selected_account.account_id;
		END IF;
		
		RETURN get_global('account_password_mismatch');
	END
$$
LANGUAGE PLPGSQL;