/* using LRU cache */
#include <iostream>
#include <string>
#include "clientsocket.h"
#include "socketexception.h"
#include "profile.h" 
#include "LRU.h" 

using namespace std;

int main(){
    // create 5 dummy profiles 
    // profile raj = profile(1, "raj", 100, 12);
    // profile arthur = profile(2, "arthur", 265, 1024);
    // profile larry = profile(3, "Larry", 70615, 3);
    // profile brin = profile(4, "brin", 109, 78);
    // profile jeff = profile(5, "jeff", 89376, 237);

    // initialise LRU cache with capacity = 3
    // LRU lru(3);

    // sample request order: 1 2 3 2 3 2 2 4 3 4 1 5 2 1 3
    
    ClientSocket client_socket ( "localhost", 30000 );
    string data;
    int inp;
    client_socket>>data; cout<<data; cin>>inp;
    client_socket << inp;
    client_socket << 1;
    client_socket>>data;
    cout<<data<<endl;
    return 0;
}