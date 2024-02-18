
CREATE OR REPLACE FUNCTION loan_deletion()
RETURNS trigger AS $$
	BEGIN
		UPDATE Account
		SET borrowed_books = borrowed_books - 1
		WHERE id = old.account_id;

		UPDATE Book
		SET borrowed_copies = borrowed_copies - 1
		WHERE id = old.book_id;

		INSERT INTO PastLoan VALUES (old.*);

			RETURN new;
	END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER loan_deletion_trigger
BEFORE DELETE ON Loan
FOR EACH ROW EXECUTE FUNCTION loan_deletion();


