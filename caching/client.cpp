/* using LRU cache */
#include<iostream>

#include "profile.h" 
#include "LRU.h" 
using namespace std;

int main(){
    // create 5 dummy profiles 
    profile* raj = new profile(1,"raj",100, 12);
    profile* arthur = new profile(2,"arthur",265, 1024);
    profile* larry = new profile(3,"Larry",70615, 3);
    profile* brin = new profile(4,"brin",109, 78);
    profile* jeff = new profile(5,"jeff",89376, 237);

    // initialise LRU cache with capacity = 3
    LRU lru(3);

    // sample request order: 1 2 3 2 3 2 2 4 3 4 1 5 2 1 3
    lru.put(raj);
    lru.put(arthur);
    lru.put(larry);
    lru.get(1);
    lru.get(2);
    lru.get(3);
    lru.get(4);
    lru.get(5);
    lru.print(lru.get(1));
    lru.print(lru.get(2));
    lru.print(lru.get(3));
    lru.print(lru.get(4));
    lru.print(lru.get(5));

    return 0;
}