/* using LRU cache */
#include <iostream>
#include <string>
#include "clientsocket.h"
#include "socketexception.h"
#include "profile.h"
#include "LRU.h"

using namespace std;

int main()
{
    ClientSocket client_socket("localhost", 30000);
    string data;
    int inp;
    // Enter opeartion
    client_socket >> data;
    cout << data;
    cin >> inp;
    client_socket << inp;
    if (inp == 1)
    { 
        // to make a new profile
        // name
        while (true)
        {
            cout << "Enter Name: ";
            cin >> data;
            client_socket << data;
            client_socket >> inp;
            if (inp == 1)
                break;
        }
        // age
        while (true)
        {
            cout << "Enter age: ";
            cin >> inp;
            client_socket << inp;
            client_socket >> inp;
            if (inp == 1)
                break;
        }
        // sex
        while (true)
        {
            cout<< "Enter sex (m/f):";
            cin >> data;
            client_socket << data;
            client_socket >> inp;
            if (inp == 1)
                break;
        }

        // new profile information
        client_socket>>inp;
        cout<<"New profile created. User id: "<<inp<<endl;
    }
    else if (inp == 2)
    { // to fetch data of new profile
        // enter user id to fetch
        while (true)
        {
            cout << "Enter user_id to fetch: ";
            cin >> inp;
            client_socket << inp;
            client_socket >> inp;
            if (inp == 1)
                break;
        }
        client_socket >> inp; // status
        if (inp == 1)
        {
            client_socket >> inp; cout<<"ID: "<<inp<<endl;
            client_socket >> inp; cout<<"Age: "<<inp<<endl;
            client_socket >> inp; cout<<"Followers Count: "<<inp<<endl;
            client_socket >> inp; cout<<"Following Count: "<<inp<<endl;
            client_socket >> data;  cout<<"Name: "<<data.c_str()<<endl;
            // client_socket >> data;  data += '\0';
            // cout<<"Sex: "<<data.c_str()<<endl;
        }
        else {
            cout<<"No such profile found.."<<endl;
        }
    }

    return 0;
}