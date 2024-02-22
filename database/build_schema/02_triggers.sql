
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


