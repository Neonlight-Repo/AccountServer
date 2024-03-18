-- User account table
DROP TABLE UserAccount;
CREATE TABLE UserAccount (
	uniqueId BINARY(16) NOT NULL,
	nickname VARCHAR(32) NOT NULL,
	pwdhash VARCHAR(32) NOT NULL,
	PRIMARY KEY (uniqueId)
);