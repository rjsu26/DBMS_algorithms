// run command :
// g++ -o server server.cpp LRU/LRU.o -I ./  -I LRU/. -I /usr/include/mysql++ -I /usr/include/mysql -lmysqlpp -lmysqlclient -w; ./server

/* Acts as black box to the client which can make a new profile which gets saved to the MySQL database. Client's requests for profiles will be first looked into the cache. If not found, it will be searched in the MySQL db, and brought into cache from there and then sent to the user. */

#include <iostream>
#include <unistd.h>
#include <string>
#include <mysql++.h>
#include <mysql.h>

#include "LRU.h"
#include "serversocket.h"
#include "socketexception.h"
#include "profile.h"

using namespace std;
using namespace mysqlpp;

// [TODO]secure the credentials
#define dbname "DBMS"
// #define server "localhost"
#define user "root"
#define pass "root"

Connection con(true);
LRU lru(5); // create an LRU cache with capacity of 5

int db_connect()
{
    try
    {
        con.connect(dbname, "localhost", user, pass);
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
    //[TODO]
    return 1;
}

int validate_age(int age)
{
    // return 1 or 0
    //[TODO]
    return 1;
}

int validate_sex(string sex)
{
    // [TODO]return 1 or 0
    // if (sex != 'm' && sex != 'M' && sex != 'f' && sex != 'F')
    // {
    //     return 0;
    // }
    return 1;
}

int validate_userid(int id)
{
    // [TODO]
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

        // create if not exists table with schema (id, name, age, sex, followers count, following count)
        string create_command = "CREATE TABLE if not exists profiles(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), age INT, sex VARCHAR(10), followers INT default 0, following INT default 0) Engine = Memory;";

        Query q = con.query(create_command);
        StoreQueryResult sq = q.store();
        // StoreQueryResult::iterator it;
        // it = sq.begin();
        // while (it != sq.end())
        // {
        //     Row row = *it;
        //     cout << row[0] << row[1] << row[2] << row[3] << endl;
        //     it++;
        // }
    }
    catch (Exception &e)
    {
        cout << e.what() << endl;
        return 0;
    }

    try
    {

        // create a listener
        ServerSocket server(30000);
        try
        {
            while (true)
            {
                cout << "Starting socket..\n";
                ServerSocket new_sock;
                server.accept(new_sock);
                // [TODO] input == 3: modify profile
                while (true)
                {
                    new_sock << "Enter the operation(1/2): ";
                    int operation;
                    new_sock >> operation;

                    if (operation == 1)
                    { // make new profile
                        string name;
                        new_sock << "Enter Name: ";
                        new_sock >> name;
                        while (validate_name(name) == 0)
                        {
                            new_sock << "Enter Name: ";
                            new_sock >> name;
                        }
                        int age;
                        new_sock << "Enter age: ";
                        new_sock >> age;
                        while (validate_age(age) == 0)
                        {
                            new_sock << "Enter age: ";
                            new_sock >> age;
                        }
                        string sex;
                        new_sock << "Enter sex (m/M/f/F):";
                        new_sock >> sex;
                        while (validate_sex(sex) == 0)
                        {
                            new_sock << "Enter sex (m/M/f/F):";
                            new_sock >> sex;
                        }
                        // add entry to database
                        string insert_query = "INSERT into profiles values(NULL, \"" + name + "\", " + to_string(age) + ", \"" + sex + "\", 0, 0);";
                        Query q = con.query(insert_query);
                        q.execute();
                        // StoreQueryResult sq = q.store();
                        // q = con.query("select * from profiles;");
                        // sq = q.store();
                        // StoreQueryResult::iterator it;
                        // it = sq.begin();
                        // while (it != sq.end())
                        // {
                        //     Row row = *it;
                        //     cout << row[0] << row[1] << row[2] << row[3] << endl;
                        //     it++;
                        // }
                        q = con.query("select max(id) from profiles");
                        StoreQueryResult sq = q.store();
                        int user_id = (*(sq.begin()))[0];
                        new_sock << "New profile for " << name << " created successfully. User_id: " << user_id;
                    }

                    else if (operation == 2)
                    { // fetch profile
                        int userid;
                        new_sock << "Enter user_id to fetch: ";
                        new_sock >> userid;
                        while (validate_userid(userid) == 0)
                        {
                            new_sock << "Enter user_id to fetch: ";
                            new_sock >> userid;
                        }
                        profile fetched = lru.get(userid);

                        // if profile not in cache, search it in database and add it to the cache
                        if (fetched.userid != -1)
                            new_sock << fetched.user_name << " " << fetched.age << " " << fetched.followers_count << " " << fetched.following_count;
                        else
                        {
                            new_sock << "Not Found in cache\n";
                            string search_query = "SELECT * from profiles where id=" + to_string(userid) + ";";
                            // cout<<search_query<<endl;
                            Query q = con.query(search_query);
                            StoreQueryResult sq = q.store();
                            if (sq && sq.num_rows() == 1)
                            {
                                // cout<<sq[0][0]<<sq[0][1]<<sq[0][2]<<endl;

                                // make a struct profile and call put function
                                int id = atoi(sq[0]["id"]);
                                // cout<<id<<endl;
                                string name = string(sq[0]["name"]);
                                int age = atoi(sq[0]["age"]);
                                // cout<<age<<endl;
                                string sex = string(sq[0]["sex"]).substr(0, 1);
                                int followers = atoi(sq[0]["followers"]);
                                // cout<<followers<<endl;
                                int following = atoi(sq[0]["following"]);
                                // cout<<following<<endl;
                                // cout<<id<<name<<age<<followers<<sex<<following<<endl;
                                profile temp = profile(id, name, followers, following, age, sex);
                                lru.put(temp);
                            }
                            else
                                new_sock << "Not found in database";
                        }
                    }

                    else if (operation == 3)
                    {
                        // exit for the client
                        break;
                    }

                    new_sock << "Enter the operation..";
                }
            }
        }
        catch (SocketException &){ }
    }
    catch (SocketException &e)
    {
        cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    return 0;
}