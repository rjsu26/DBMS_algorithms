#! venv/bin/python
""" 
Aim: Using 2 methods to compare 2 tables with sparesely different values and observing which of the 2 methods(UNION method and Hashing method) is faster

Observation: Hashing approach clearly becomes more efficient as the size of table reaches 10^5. 
"""


import random 
import time 
import resource
from datetime import datetime

from connect_db import connect
from faker import Faker

db_connection = connect()
db_cursor = db_connection.cursor() 

"""   Create 2 tables with attributes (ID(int), Name(string), DOB(date), city(string)) with mostly same data except a few differences sparsely distributed in the whole table.
"""
def create_table():
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

def populate():
  """ Create N number of rows and insert into both tables """
  print("Populating N = ",N)
  probability = 0.1 # probability of a row being changed before inserting into student2 table
  fake = Faker()
  insert_command = """INSERT INTO {} VALUES ({}, "{}", "{}", "{}");"""
  for i in range(1,N+1):
    if(i%10000==0):
      print("populated ",i)
    idx = i 
    name = fake.name()
    date = fake.date_between(datetime(1990, 1, 1), datetime(1999, 12, 31))
    city = fake.city()
    row = [idx, name, date, city]
    row2 = row[:]
    # print(row)
    # print(insert_command.format("student1", idx, name, date,city))
    db_cursor.execute(insert_command.format("student1", idx, name, date,city))
    if(random.random() <= probability):
      name = fake.name()
      city = fake.city()
      # print("Inserting different value: ",i)
    db_cursor.execute(insert_command.format("student2", idx, name, date,city))

  db_connection.commit()


  # db_cursor.execute("select * from student1;")
  # for row in db_cursor:
  #   print(row)
  # db_cursor.execute("select * from student2;")
  # for row in db_cursor:
  #   print(row)

""" SQL based UNION method """
def compare_union():
  print("Using UNION method..")
  union_command = "select count(*) from (select t.id, count(*) from (select * from student1 union all select * from student2) t group by t.id, t.name, t.dob, t.city having count(*)=1 order by NULL) p order by NULL;"
  
  start = time.time()
  db_cursor.execute(union_command)
  row_count = db_cursor.fetchone()[0]
  end = time.time()
  # print("row_count = ",row_count)
  if row_count>0:
    return [0, end-start]
  else: 
    return [1,end-start]

def compare_checksum():
  # referred from : https://mariadb.com/resources/blog/a-hash-based-group-by-strategy-for-mysql/
  print("Hashing method..")
  start = time.time()
  create_temporary_table = "CREATE TEMPORARY TABLE tmp (id INT , hash BINARY(16)) ;" # a temporary table to contain the id and hash value
  db_cursor.execute(create_temporary_table)
  db_cursor.execute( "INSERT INTO tmp SELECT id, UNHEX(MD5(CONCAT_WS('~',name,dob, city))) FROM student1;") # concat columns with a delimiter to avoid confusion from student1
  db_cursor.execute( "INSERT INTO tmp SELECT id, UNHEX(MD5(CONCAT_WS('~',name,dob, city))) FROM student2;") # from student2
  db_cursor.execute("SELECT id, hash FROM tmp  GROUP BY id,hash HAVING COUNT(*)=1 order by NULL;")

  # for row in db_cursor:
  #   print(row)
  row_count = db_cursor.fetchone()[0]
  end = time.time() 
  if row_count>0:
    return [0, end-start]
  else: 
    return [1,end-start]



if __name__=="__main__":
  random.seed(time.time())
  global N
  N = 100000 # number of tuples in the tables
  # comment bottom 2 lines after 1st run of this program
  create_table()
  populate()

  res = compare_union()
  if res[0]==0:
    print("Not Matching")
  else:
    print("Matching")

  print("N = {}, time for comparison: {:.5f}s".format(N, res[1]))

  res = compare_checksum()
  if res[0]==0:
    print("Not Matching")
  else:
    print("Matching")
  print("N = {}, time for comparison: {:.5f}s".format(N, res[1]))
