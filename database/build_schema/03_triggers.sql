CREATE OR REPLACE FUNCTION loan_insertion()
RETURNS trigger AS $$
	BEGIN
		IF (num_loans_for_account(new.account_id) >= get_global('max_num_of_loans_per_user')) THEN
			RAISE EXCEPTION 'max number of loans per user exceeded'
				USING ERRCODE = get_global('max_loans_per_user_error')::VARCHAR(10);
		ELSIF ((SELECT COUNT(*) FROM Loan L WHERE L.book_id = new.book_id) >= 
					 (SELECT total_copies FROM Book B WHERE B.book_id = new.book_id)) THEN
			RAISE EXCEPTION 'max number of loans per book exceeded'
				USING ERRCODE = get_global('max_loans_per_book_error')::VARCHAR(10);
		END IF;
		RETURN new;
	END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER loan_insertion_trigger
BEFORE INSERT ON Loan
FOR EACH ROW EXECUTE FUNCTION loan_insertion();

------------------------------------------------

CREATE OR REPLACE FUNCTION loan_deletion()
RETURNS trigger AS $$
	BEGIN
		INSERT INTO PastLoan VALUES (old.*);
		RETURN NULL;
	END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER loan_deletion_trigger
AFTER DELETE ON Loan
FOR EACH ROW EXECUTE FUNCTION loan_deletion();

-----------------------------------------------

CREATE OR REPLACE FUNCTION book_insert()
RETURNS trigger AS $$
	BEGIN
		IF EXISTS(
			SELECT 1
			FROM UNNEST(string_to_array(new.genres, ',')) AS V
			WHERE V::genre_enum IS NULL
		) THEN
			RAISE EXCEPTION 'Invalid genres';
		END IF;
		RETURN new;
	EXCEPTION
		WHEN OTHERS THEN
			RAISE EXCEPTION 'Invalid genres'
			USING ERRCODE = get_global('invalid_book_genres_error')::VARCHAR(10);
	END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER book_insert
BEFORE INSERT ON Book
FOR EACH ROW EXECUTE FUNCTION book_insert();