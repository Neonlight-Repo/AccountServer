-- User Check
DROP PROCEDURE IF EXISTS SP_CheckUser;
DELIMITER $$
CREATE PROCEDURE SP_CheckUser(
	IN nickname VARCHAR(32)
)
BEGIN
	SELECT COUNT(*)
	FROM UserAccount AS account
	WHERE account.nickname = nickname;
END $$

-- Login
DROP PROCEDURE IF EXISTS SP_Login;
CREATE PROCEDURE SP_Login(
	IN nickname VARCHAR(32),
	IN pwdhash VARCHAR(32)
)
BEGIN
	SELECT BIN_TO_UUID(uniqueId)
	FROM UserAccount AS account
	WHERE account.nickname = nickname AND account.pwdhash = pwdhash;
END $$

-- Register
DROP PROCEDURE IF EXISTS SP_Register;
CREATE PROCEDURE SP_Register(
	IN uniqueId VARCHAR(36),
	IN nickname VARCHAR(32),
	IN pwdhash VARCHAR(32)
)
BEGIN
	INSERT INTO UserAccount VALUES(UUID_TO_BIN(uniqueId), nickname, pwdhash);
END $$
DELIMITER ;

commit;