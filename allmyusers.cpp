#include <iostream>
#include<fstream>
//#include<vector>
// composite design pattern......
using namespace std;
static int countofappusersofmycontacts = 0;
class Myusers
{
 public:
    string username,mobile;
   // vector <Myusers> users;
    Myusers(string name,string mobile)
    {
        this->username = name;
        this->mobile=mobile;
    }
    string getUsername()
    {
        return username;
    }
    void display()
    {
        cout << "Username  : " << username << "\nMobilenum : " << mobile << "\n\n";
    }
};
int getnoofcontacts()
{
    fstream f;
    f.open("contacts.txt",ios::in);
    int countcontacts=0;
    while(!f.eof())
     countcontacts++;
    f.close();
     return countcontacts;
}
//static int countmycontacts = getnoofcontacts();
static Myusers** alluserslist = new Myusers*[1000];
string getusernamefromdb(string phonenum)
{
    stringstream ss;
    ss << "select * from users where mobile = '"+phonenum+"';";
    string q = ss.str();
    const char* query = q.c_str();
    int qstate = mysql_query(connection,query);
    MYSQL_ROW  row;
    MYSQL_RES *res;
    res = mysql_store_result(connection);
    string usn;
     while(row = mysql_fetch_row(res))
    {
       usn = row[0];
    }
    return usn;
}
void allmyusers()
{
  fstream f;
  f.open("contacts.txt",ios::in);
  string mobilenumber,nm;
  int i=0;
  while(!f.eof())
  {
      f >> mobilenumber;
     if(mobilenumber!="") 
      nm = getusernamefromdb(mobilenumber);
      if(nm!=currentuser->getUsername())
       alluserslist[i++] = new Myusers(nm,mobilenumber);
  }
  countofappusersofmycontacts = i;
  f.close();
}
