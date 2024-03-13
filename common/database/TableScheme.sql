-- User account table
CREATE TABLE UserAccount (
  uniqueId binary(16) NOT NULL,
  nickname varchar(32) NOT NULL,
  pwdhash varchar(32) NOT NULL,
  PRIMARY KEY (uniqueId)
);