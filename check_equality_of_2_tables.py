from datetime import datetime
from connect_db import connect
from faker import Faker

db_connection = connect()
db_cursor = db_connection.cursor() 

# Create 2 tables with attributes (ID(int), Name(string), DOB(date), city(string)) with mostly same data except a few differences sparsely distributed in the whole table.

create_command = "CREATE TABLE {}(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), dob DATE,city VARCHAR(255))"
delete_command = "TRUNCATE TABLE "

try:
  db_cursor.execute(create_command.format("student1"))
except:
  db_cursor.execute(delete_command+"student1")
  pass # table already exists

try:
  db_cursor.execute(create_command.format("student2"))
except:
  db_cursor.execute(delete_command+"student2")
  pass # table already exists

# db_cursor.execute("SHOW TABLES")
# for table in db_cursor:
# 	print(table)	

""" Create N number of rows and insert into both tables """
N = 1000
fake = Faker()
for i in range(1,1001):
  idx = i 
  name = fake.name()
  date = fake.date_between(date_start=datetime(1960, 1, 1), date_end=datetime(2000, 1, 1))
