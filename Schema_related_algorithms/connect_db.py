import mysql.connector

def connect():
    db_connection = mysql.connector.connect(
    host="localhost",
    user="root",
    passwd="root"
    )
    db_cursor = db_connection.cursor() # creating database_cursor to perform SQL operation
    try:
        db_cursor.execute("CREATE DATABASE DBMS") # executing cursor with execute method and pass SQL query
    except Exception as e: # database already exists
        # print(e)
        pass

    db_connection = mysql.connector.connect(
    host="localhost",
    user="root",
    passwd="root",
    database="DBMS"
    )

    return db_connection