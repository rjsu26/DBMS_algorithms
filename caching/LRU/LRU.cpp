/* Aim: To implement LRU : Least Recently Used cache-eviction policy */

// Run command: g++ -c LRU.cpp -I ../
using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <iterator>

#include "LRU.h"
#include "../profile.h"

LRU::LRU(int capacity)
{
    this->capacity = capacity; // maximum number of profiles that can be cached
    cout<<"Constructor called"<<endl;
}

/* Find input user_id in the cache. Return NULL if not found, else return a pointer to the profile in the memory */
profile LRU ::get(int user_id)
{
    cout<<"get() called"<<endl;
    // if user_id exists, return pointer to profile, else return NULL
    if (mp.count(user_id) == 0)
        return profile();

    // user_id exists. Bring it to front of the list as it has become most recently requested profile.
    // cout<<"moving "<<**(mp[user_id])->userid<<" "<<*mp[user_id]->user_name<<" to 1st"<<endl;
    profile temp = *mp[user_id];
    order.erase(mp[user_id]);
    order.push_front(temp);
    mp[user_id] = order.begin();
    return order.front();
}

/* Given a pointer to a profile, put it into the cache */
void LRU::put(profile user_profile)
{
    cout<<"put() called"<<endl;
    int user_id = user_profile.userid;
    if (mp.size() == capacity && mp.count(user_id) == 0)
    { // size reached to maximum and requested entry not present already => remove least recently used profile
        mp.erase(order.back().userid);
        order.pop_back();
    }
    // if user_id present already, then we want to remove it from old location before adding it again to the front of the list
    if (mp.count(user_id) != 0)
        order.erase(mp[user_id]);

    order.push_front(user_profile);
    mp[user_id] = order.begin();
    profile temp = *mp[user_id];

    // cout<<"Pushed "<<temp->userid<<" "<<temp->user_name<<endl;
    // delete temp;
    return;
}

void LRU::print(profile user_profile)
{
    if (user_profile.userid == -1)
    {
        cout << -1 << endl;
        return;
    }
    cout << user_profile.userid << " " << user_profile.user_name << endl;
}

/* int main()
{
    profile raj = profile(1, "raj", 100, 12);
    profile arthur = profile(2, "arthur", 265, 1024);
    profile larry = profile(3, "Larry", 70615, 3);
    profile brin = profile(4, "brin", 109, 78);
    profile jeff = profile(5, "jeff", 89376, 237);

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

}
 */