#include<iostream>
using namespace std;
class currUser
{
    string username,name;
    public:
    currUser(){}
     currUser(string username,string name)
     {
         this->username = username;
         this->name = name;
     }
     

     void setUsername(string username)
     {
         this->username=username;
     }
     void setName(string name)
     {
        this->name=name;
     }
     string getUsername()
     {
         return this->username;
     }
     string getName()
     {
         return this->name;
     }
};


