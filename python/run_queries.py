"""Run every query in sql/queries.sql against generated_users.db and print the results.

Run from the repo root, after generate_data.py and load_db.py:
    python python/run_queries.py
"""
import sqlite3
import pandas as pd

queries_path = "sql/queries.sql"
db_path = "generated_users.db"

# Read the queries file and split it into separate queries on the semicolons
with open(queries_path) as file:
    queries_text = file.read()

queries = [query.strip() for query in queries_text.split(";") if query.strip()]

connection = sqlite3.connect(db_path)

for query in queries:
    # The first line of each query is a comment holding its title
    title = query.splitlines()[0].lstrip("- ").strip()
    print("" + title)
    print(pd.read_sql_query(query, connection).to_string(index=False))

connection.close()
