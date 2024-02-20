
CREATE OR REPLACE FUNCTION loan_deletion()
RETURNS trigger AS $$
	BEGIN
		UPDATE Account
		SET borrowed_books = borrowed_books - 1
		WHERE account_id = old.account_id;

		UPDATE Book
		SET borrowed_copies = borrowed_copies - 1
		WHERE book_id = old.book_id;

		INSERT INTO PastLoan VALUES (old.*);
		RETURN NULL;
	END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER loan_deletion_trigger
AFTER DELETE ON Loan
FOR EACH ROW EXECUTE FUNCTION loan_deletion();


