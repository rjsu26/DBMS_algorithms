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
        while (true)
        {
            try
            {
                cout << "\n\n\t\tStarting socket..\n";
                ServerSocket new_sock;
                server.accept(new_sock);
                cout<<"Accepted a new client.."<<endl;
                // [TODO] input == 3: modify profile
                while (true)
                {
                    new_sock << "Enter the operation(1/2): ";
                    int operation;
                    new_sock >> operation;
                    cout<<"operation: "<<operation<<endl;
                    if (operation == 1)
                    { // make new profile
                        string name;
                        new_sock >> name;
                        while (validate_name(name) == 0)
                        {
                            new_sock<<0; // failure for previous input
                            new_sock >> name;
                        }
                        new_sock<<1; // input recieved successfully

                        int age;
                        new_sock >> age;
                        while (validate_age(age) == 0)
                        {
                            new_sock<<0; // failure for previous input
                            new_sock >> age;
                        }
                        new_sock<<1; // input recieved successfully

                        string sex;
                        new_sock >> sex;
                        while (validate_sex(sex) == 0)
                        {
                            new_sock<<0; // failure for previous input
                            new_sock >> sex;
                        }
                        new_sock<<1; // input recieved successfully

                        // add entry to database
                        string insert_query = "INSERT into profiles values(NULL, \"" + name + "\", " + to_string(age) + ", \"" + sex + "\", 0, 0);";
                        Query q = con.query(insert_query);
                        q.execute();
                        // q.store();
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
                        cout << "New profile created successfully. User_id: " << user_id<<endl;;
                        new_sock<<user_id;
                    }

                    else if (operation == 2)
                    { // fetch profile
                        int userid;
                        new_sock >> userid;
                        while (validate_userid(userid) == 0)
                        {
                            new_sock << 0; // failure
                            new_sock >> userid;
                        }
                        new_sock<<1;
                        profile fetched = lru.get(userid);

                        // if profile not in cache, search it in database and add it to the cache
                        if (fetched.userid != -1){
                            cout << "Found in cache\n";
                            // send 1 for status and then all the data
                            new_sock<<1;
                            // new_sock << fetched.user_name << " " << fetched.age << " " << fetched.followers_count << " " << fetched.following_count;
                        }
                        else
                        {
                            cout << "Not Found in cache\n";
                            string search_query = "SELECT * from profiles where id=" + to_string(userid) + ";";
                            // cout<<search_query<<endl;
                            Query q = con.query(search_query);
                            StoreQueryResult sq = q.store();
                            if (sq && sq.num_rows() == 1)
                            {
                                cout<<"Found in database\n";
                                new_sock<<1;
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
                                // profile temp = profile(id, name, followers, following, age, sex);
                                fetched = profile(id, name, followers, following, age, sex);
                                lru.put(fetched);
                            }
                            else{
                                cout << "Not found in database\n";
                                new_sock<<0;
                                throw -1; // invalid request
                            }
                        }
                        // cout<<fetched.userid<<endl;
                        // cout<<fetched.user_name<<endl;
                        // cout<<fetched.age<<endl;
                        // cout<<fetched.sex<<endl;
                        // cout<<fetched.followers_count<<endl;
                        // cout<<fetched.following_count<<endl;
                        new_sock<<fetched.userid;
                        new_sock<<fetched.age;
                        new_sock<<fetched.followers_count;
                        new_sock<<fetched.following_count;
                        new_sock<<fetched.user_name;
                        // new_sock<<fetched.sex;
                    }

                    else if (operation == 3)
                    {
                        // exit for the client
                        break;
                    }

                    // new_sock << "Enter the operation.123.";
                    break;
                }
            }
            catch (...){
                cout<<"Closing the client.."<<endl;
             }
        }
    }
    catch (SocketException &e)
    {
        cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    return 0;
}