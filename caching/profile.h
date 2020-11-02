#include<iostream>
using namespace std;

#ifndef PROFILE_H
#define PROFILE_H
struct profile{
    int userid, age;
    char sex;
    string user_name;
    int followers_count, following_count;
    inline profile(){
        userid = -1;
    }
    inline profile(int userid, string name, int count1, int count2, int age, char sex){
        this->userid=userid;
        this->user_name = name; 
        this->followers_count = count1;
        this->following_count = count2;
        this->age = age; 
        this->sex = sex;
    }
};

#endif 