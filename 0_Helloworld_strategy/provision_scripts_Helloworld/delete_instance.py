import sqlite3
import sys

# Getting the instance name
instance_name = sys.argv[1]

# Connect to the SQLite database
conn = sqlite3.connect('strategy.db')
cursor = conn.cursor()

# # Query the sqlite_master table to get all table names
# cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
# tables = cursor.fetchall()

# # Print the table names
# for table in tables:
#     print(table[0])

# Delete the row where instName = 'InstanceName'
# If there is no row, nothing will happen
cursor.execute("DELETE FROM StrategyInstance WHERE instName = instance_name")

# Commit the changes to the database
conn.commit()

# Close the connection
conn.close()