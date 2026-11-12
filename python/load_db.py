import sqlite3
import pandas as pd

schema_path = "sql/schema.sql"
csv_path = "data/raw/generated_users_full.csv"
db_path = "generated_users.db"

# Read the schema file as text
with open(schema_path) as file:
    schema_sql = file.read()

# Connect to the database
connection = sqlite3.connect(db_path)

# Build the tables from the schema
connection.executescript(schema_sql)

# Load the CSV
df = pd.read_csv(csv_path)
print(len(df))

# Split into one DataFrame per table
users_df = df[["user_id", "device", "user_type", "traffic_source"]]
assignments_df = df[["user_id", "variant"]]
purchases_df = df[["user_id", "purchased", "order_price"]]

# Insert into each table (users first)
users_df.to_sql("users", connection, if_exists="append", index=False)
assignments_df.to_sql("experiment_assignments", connection, if_exists="append", index=False)
purchases_df.to_sql("purchases", connection, if_exists="append", index=False)

connection.commit()

# Print the row counts
for table in ["users", "experiment_assignments", "purchases"]:
    print(table, pd.read_sql_query("SELECT COUNT(*) AS rows FROM " + table, connection))

connection.close()
