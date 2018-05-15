# 2
SELECT name FROM users WHERE gender = "Male" AND id NOT IN (
	SELECT guyId FROM User_dates
);

# 4
SELECT u.name, i.interest FROM users as u
LEFT JOIN user_interests as ui ON ui.userId = u.id
LEFT JOIN interests as i ON i.id = ui.interestId
INNER JOIN weddings as w on u.id = w.groomId;

# 5
SELECT COUNT(*), w.location FROM Wedding_guests as wg
JOIN Weddings as w ON w.id = wg.weddingId
GROUP BY w.id;