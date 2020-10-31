/* Aim: To implement LRU : Least Recently Used cache-eviction policy */

using namespace std;
#include<iostream>
#include<vector>
#include<unordered_map>
#include<list>
#include<iterator>

#include "LRU.h"
#include "profile.h"


LRU::LRU(int capacity){
    this->capacity = capacity; // maximum number of profiles that can be cached
}

/* Find input user_id in the cache. Return NULL if not found, else return a pointer to the profile in the memory */
profile* LRU :: get(int user_id){
    // if user_id exists, return pointer to profile, else return NULL
    if(mp.count(user_id)==0)
        return NULL ;
    
    // user_id exists. Bring it to front of the list as it has become most recently requested profile.
    profile* temp = *mp[user_id];
    cout<<"moving "<<temp->userid<<" "<<temp->user_name<<" to 1st"<<endl;
    order.erase(mp[user_id]);
    order.push_front(temp);
    mp[user_id]= order.begin();
    delete temp;
    return order.front();
}

/* Given a pointer to a profile, put it into the cache */
void LRU:: put(profile* user_profile ){
    int user_id = user_profile->userid;
    if(mp.size()==capacity && mp.count(user_id)==0){ // size reached to maximum and requested entry not present already => remove least recently used profile
        mp.erase(order.back()->userid);
        order.pop_back();
    }
    // if user_id present already, then we want to remove it from old location before adding it again to the front of the list
    if(mp.count(user_id)!=0)
        order.erase(mp[user_id]);
    
    order.push_front(user_profile);
    mp[user_id] = order.begin();
    profile* temp = *mp[user_id];

    cout<<"Pushed "<<temp->userid<<endl;
    delete temp;
    return;
}

void LRU::print(profile* user_profile){
    if(user_profile==NULL){
        cout<<-1<<endl;
        return;
    }
    cout<<user_profile->userid<<" "<<user_profile->user_name<<endl;
}
