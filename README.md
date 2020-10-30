# DBMS_algorithms

Using MySQL and Python to implement some interesting DBMS algorithms listed in later section of this ReadMe.

--------------------------------------------

### Setup
1. Install MySQL and python package for connecting to MySQL. <a href="https://www.guru99.com/python-mysql-example.html" target="_blank">Guide</a>

2. Initialize a python3 virtual environment and install packages from the `requirements.txt` file.

### Implementations : 

1. **check_equality_of_2_tables.py**: Using 2 methods to compare 2 tables with sparesely different values and observing which of the 2 methods(UNION method and Hashing method) is faster.

2.  **closure. py** : Implementing a quadratic and a liner time complexity algorithm to find closure of an attribute set in a given Functional Dependency. Also, an algorithm to find closure of a set of Functional Dependencies using the above implemented attribute set closure algorithm. 

3. **check_for_superkey.py**: Given an attribute set, check if it is a superkey of the given set of Functional Dependencies. Uses the closure for attribute set algorithm done in `closure.py`