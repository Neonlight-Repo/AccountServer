USE AccountDB;

-- User Check
DELIMITER $$
DROP PROCEDURE IF EXISTS SP_CheckUser;
CREATE PROCEDURE SP_CheckUser(
	IN nickname VARCHAR(32)
)
BEGIN
	SELECT COUNT(*)
	FROM AccountDB.UserAccount AS account
	WHERE account.nickname = nickname;
END $$

-- Login
DROP PROCEDURE IF EXISTS SP_Login;
CREATE PROCEDURE SP_Login(
	IN nickname VARCHAR(32),
	IN pwdhash VARCHAR(32)
)
BEGIN
	SELECT @uniqueId := BIN_TO_UUID(uniqueId)
	FROM AccountDB.UserAccount AS account
	WHERE account.nickname = nickname AND account.pwdhash = pwdhash;

	-- CALL LogDB.SP_LogLogin(@uniqueId, ipAddress);
END $$

-- Register
DROP PROCEDURE IF EXISTS SP_Register;
CREATE PROCEDURE SP_Register(
	IN uniqueId VARCHAR(36),
	IN nickname VARCHAR(32),
	IN pwdhash VARCHAR(32)
)
BEGIN
	INSERT INTO AccountDB.UserAccount
	VALUES(UUID_TO_BIN(uniqueId), nickname, pwdhash);

	-- CALL LogDB.SP_LogRegister(uniqueId, ipAddress);
END $$

DROP PROCEDURE IF EXISTS SP_Logout;
CREATE PROCEDURE SP_Logout(
	IN uniqueId VARCHAR(36),
	IN ipAddress VARCHAR(16)
)
BEGIN
	CALL LogDB.SP_LogLogout(uniqueId, ipAddress);
END $$

DELIMITER ;
commit;