/* Acts as black box to the client which can make a new profile which gets saved to the MySQL database. Client's requests for profiles will be first looked into the cache. If not found, it will be searched in the MySQL db, and brought into cache from there and then sent to the user. */

#include <iostream>
#include <ctime>
#include <mysql++.h>
#include <mysql.h>
#include "LRU.h"
using namespace std;
using namespace mysqlpp;

// secure the credentials
#define dbname "DBMS"
#define server "localhost"
#define user "root"
#define pass "root"

Connection con(true);

int db_connect()
{
    try
    {
        con.connect(dbname, server, user, pass);
        return 1; // success
    }
    catch (Exception &e)
    {
        cerr << e.what() << endl;
        return 0; // failed to connect
    }
}

int validate_name(string name)
{
    // if name is good return 1 else 0
    return 1;
}

int validate_age(int age)
{
    // return 1 or 0
    return 1;
}

int validate_sex(char sex)
{
    // return 1 or 0
    if (sex != 'm' && sex != 'M' && sex != 'f' && sex != 'F')
    {
        return 0;
        return 1;
    }

    int main()
    {
        // until no connected to database, do not proceed
        while (db_connect() == 0)
        {
            cout << "Retrying in 3 sec.." << endl;
            sleep(3);
        }

        try
        {
            cout << "Connected to database\n";
            string s = "select * from student1 where id=12345";
            Query q = con.query(s);
            StoreQueryResult sq = q.store();
            StoreQueryResult::iterator it;
            it = sq.begin();
            while (it != sq.end())
            {
                Row row = *it;
                cout << row[0] << row[1] << row[2] << row[3] << endl;
                it++;
            }
        }
        catch (Exception &e)
        {
            cout << e.what() << endl;
        }
        /*     input == 1 : make_profile
    input == 2: fetch_profile 
    [TBI] input == 3: modify profile
 */
        int operation;
        while (cin >> operation)
        {
            if (operation == 1)
            { // make new profile
                string name;
                cout << "Enter Name: ";
                cin >> name;
                while (validate_name(name) == 0)
                {
                    cout << "Enter Name: ";
                    cin >> name;
                }
                int age;
                cout << "Enter age: ";
                cin >> age;
                while (validate_age(age) == 0)
                {
                    cout << "Enter age: ";
                    cin >> age;
                }
                char sex;
                cout << "Enter sex (m/M/f/F):";
                cin >> sex;
                while (validate_sex(sex) == 0)
                {
                    cout << "Enter sex (m/M/f/F):";
                    cin >> sex;
                }
                // add entry to database
                string insert_query = "INSERT into student1 values()";

            }
        }
        else if (operation == 2)
        { // fetch profile
        }
        else cout << "Wrong input..\n";
    }
    return 0;
}