# 3 and 6
delimiter |
create procedure updateDatesAndWeddings() 
begin
	DECLARE isFinished int DEFAULT 0;
	DECLARE count int DEFAULT 0;
	DECLARE guy int DEFAULT 0;
	DECLARE girl int DEFAULT 0;
	DEClARE date_cursor CURSOR FOR SELECT COUNT(*), guyId, girlId FROM User_dates GROUP BY guyId, girlId;

	DECLARE CONTINUE HANDLER FOR NOT FOUND SET isFinished = 1;

	OPEN date_cursor;
 	iterate_dates: LOOP

 		FETCH date_cursor INTO count, guy, girl;
 		IF(isFinished = 1) THEN 
 			LEAVE iterate_dates; 
 		END IF;

		IF(count >= 3) THEN 
			INSERT INTO Weddings (groomId, brideId) VALUES (guy, girl);
		END IF;

		IF(count > 1) THEN 
			UPDATE User_dates SET haveMetAgain = 1 WHERE guyId = guy AND girlId = girl;
		END IF;

	END LOOP iterate_dates;
	CLOSE date_cursor;

end;
|
delimiter ;

call updateDatesAndWeddings();