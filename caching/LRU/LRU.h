#include<unordered_map>
#include<list>
#include<iterator>
#include "profile.h"

using namespace std; 

#ifndef LRU_H
#define LRU_H

class LRU{
    unordered_map<int, list<profile>::iterator> mp; // user_id-> profile*
    list<profile>order; // list of user_ids from most recent to least recent
    int capacity;
public:
    LRU(int capacity);

    /* Find input user_id in the cache. Return NULL if not found, else return a pointer to the profile in the memory */
    profile get(int user_id);

    /* Given a pointer to a profile, put it into the cache */
    void put(profile user_profile );

    void print(profile user_profile);
};


#endif 