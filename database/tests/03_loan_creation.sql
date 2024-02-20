
CREATE OR REPLACE FUNCTION loan_creation()
RETURNS trigger AS $$
	BEGIN

		-- ensures that the user can still afford to
		-- make at least one book loan
		IF EXISTS (
			SELECT * FROM Account
			WHERE Account.account_id = new.account_id
			AND Account.borrowed_books >=
				get_global('max_num_of_loans_per_user')
		)
		THEN
			RAISE EXCEPTION
				'max number of loans per user exceeded'
				USING ERRCODE = get_global('max_loans_per_user_error')::VARCHAR(10);
		END IF;

		-- ensure that there are still available copies
		-- of the book the user is requesting a loan for
		IF EXISTS (
			SELECT * FROM Book
			WHERE Book.book_id = new.book_id
			AND Book.borrowed_copies >= Book.total_copies
		)
		THEN
			RAISE EXCEPTION
				'max number of loans per book exceeded'
				USING ERRCODE = get_global('max_loans_per_book_error')::VARCHAR(10);
		END IF;

		UPDATE Account
		SET borrowed_books = borrowed_books + 1
		WHERE account_id = new.account_id;

		UPDATE Book
		SET borrowed_copies = borrowed_copies + 1
		WHERE book_id = new.book_id;


			RETURN new;
	END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER loan_creation_trigger
BEFORE INSERT OR UPDATE ON Loan
FOR EACH ROW EXECUTE FUNCTION loan_creation();


