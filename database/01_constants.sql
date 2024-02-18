
CREATE TABLE GlobalValue (
	name  VARCHAR(50) PRIMARY KEY,
	value INT         NOT NULL
);

INSERT INTO GlobalValue(name, value) VALUES
	('max_loans_per_user_error', 10000),
	('max_loans_per_book_error', 10001),
	('max_num_of_loans_per_user', 5);

CREATE OR REPLACE FUNCTION get_global(var_name VARCHAR(50))
RETURNS INT
AS $$
	DECLARE
		var_value INT;
	BEGIN
		SELECT value INTO var_value
		FROM Globalvalue
		WHERE name = var_name;
		RETURN var_value;
	END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE set_global(var_name VARCHAR(50), var_value INT)
AS $$
	BEGIN
		UPDATE GlobalValue
		SET value = var_value
		WHERE name = var_name;
	END
$$ LANGUAGE plpgsql;
