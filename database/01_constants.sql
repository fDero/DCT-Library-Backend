
CREATE TABLE GlobalValue (
	name  VARCHAR(50) PRIMARY KEY,
	value INT         NOT NULL
);

INSERT INTO GlobalValue(name, value) VALUES
	('max_loans_per_user_error', 10),
	('max_loans_per_book_error', 11),
	('max_num_of_loans_per_user', 5);

CREATE FUNCTION get_global(var_name VARCHAR(50))
RETURNS INT
AS $$
	DECLARE
		var_value INT;
	BEGIN
		SELECT value INTO var_value
		FROM Globalvalue
		WHERE GlobalValue.name = var_name;
		RETURN var_value;
	END
$$ LANGUAGE plpgsql;

CREATE PROCEDURE set_global(var_name VARCHAR(50), var_value INT)
AS $$
	BEGIN
		UPDATE GlobalValue
		SET GlobalValue.value = var_value
		WHERE GlobalValue.name = var_name;
	END
$$ LANGUAGE plpgsql;
