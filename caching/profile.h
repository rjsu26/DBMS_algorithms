#include<iostream>
using namespace std;

#ifndef PROFILE_H
#define PROFILE_H
struct profile{
    int userid;
    string user_name;
    int followers_count, following_count;

    inline profile(int userid, string name, int count1, int count2){
        this->userid=userid;
        this->user_name = name; 
        this->followers_count = count1;
        this->following_count = count2;
    }
};

#endif 