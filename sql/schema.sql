
DROP TABLE IF EXISTS purchases;
DROP TABLE IF EXISTS experiment_assignments;
DROP TABLE IF EXISTS users;

CREATE TABLE users (
   user_id INTEGER PRIMARY KEY, 
   device TEXT,
   user_type TEXT,
   traffic_source TEXT
);


CREATE TABLE experiment_assignments (
   user_id INTEGER PRIMARY KEY,
   variant TEXT,
   FOREIGN KEY (user_id) REFERENCES users(user_id)
);


CREATE TABLE purchases (
   user_id INTEGER PRIMARY KEY, 
   purchased INTEGER,
   order_price REAL,
   FOREIGN KEY (user_id) REFERENCES users(user_id)
);