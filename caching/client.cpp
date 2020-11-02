/* using LRU cache */
#include<iostream>

#include "profile.h" 
#include "LRU.h" 
using namespace std;

int main(){
    // create 5 dummy profiles 
    profile raj = profile(1, "raj", 100, 12);
    profile arthur = profile(2, "arthur", 265, 1024);
    profile larry = profile(3, "Larry", 70615, 3);
    profile brin = profile(4, "brin", 109, 78);
    profile jeff = profile(5, "jeff", 89376, 237);

    // initialise LRU cache with capacity = 3
    LRU lru(3);

    // sample request order: 1 2 3 2 3 2 2 4 3 4 1 5 2 1 3
   lru.put(raj);
    lru.put(arthur);
    lru.put(larry);
    lru.put(arthur);
    lru.put(larry);
    lru.put(arthur);
    lru.put(arthur);
    lru.put(brin);
    lru.put(larry);
    lru.put(brin);
    lru.put(raj);
    {
        lru.print(lru.get(1));
        lru.print(lru.get(2));
        lru.print(lru.get(3));
        lru.print(lru.get(4));
        lru.print(lru.get(5));
    }

    return 0;
}