
CREATE TABLE Account ( 
    name     VARCHAR(30) NOT NULL,
	surname  VARCHAR(40) NOT NULL,
	email    VARCHAR(50) NOT NULL,
	id       SERIAL      NOT NULL
);

INSERT INTO Account (name, surname, email)
VALUES
('John',    'Smith',    'john.smith@example.com'       ),
('Emma',    'Johnson',   'emma.johnson@example.com'    ),
('William', 'Brown',    'william.brown@example.com'    ),
('Olivia',  'Williams', 'olivia.williams@example.com'  ),
('James',   'Jones',    'james.jones@example.com'      ),
('Sophia',  'Davis',    'sophia.davis@example.com'     );
