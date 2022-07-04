#include <iostream>
#include "readpass.cpp"
#include <mysql.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

const char* host="db4free.net";
const char* muser="hello123dbcpp";
const char* mpass="1234567890";
const char* database="chatappforcpp";
static currUser* currentuser;
static MYSQL* connection;
MYSQL* connectdb()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,muser,mpass,database,3306,NULL,0);
    return conn;
}

void retievedata(MYSQL* conn,string usn,string pass)
{
        MYSQL_ROW row;
        MYSQL_RES* res;
        int qstate = mysql_query(conn,"SELECT *  from users;");
        res = mysql_store_result(conn);
        int i=0;
        try
        {
            while(row=mysql_fetch_row(res))
             {
                if(usn==row[0] && pass==row[3])
                {
                    cout << "Logged in Successfully.....!!";
                    currentuser = new currUser(usn,row[2]);
                    return;
                }

             }
            i=1;
            throw i;
        }
        catch(int j)
        {
            cout << "Invalid credentials....Try again...\n";
        }
        
        
        Sleep(1000);
        exit(0);
}

class Credentials //Singleton design pattern....
{
    string usn,pass;
    static Credentials* instance;
     Credentials()
     {
         usn = "\n";
         pass = "\n";
     }
    public:
     static Credentials* getinstance()
     {
         if(!instance)
          instance = new Credentials;
         return instance; 
     }
     void setUsn(string usn)
     {
         this->usn = usn;
     }
     void setPass(string pass)
     {
         this->pass=pass;
     }
     string getUsn()
     {
         return this->usn;
     }
     string getPass()
     {
         return this->pass;
     }
     void check()
     {
        connection  = connectdb();
        retievedata(connection,usn,pass);
     }
};

Credentials *Credentials::instance=0;

int login()
{
    string username,password;
    system("CLS");
    cout << "\t\t\t\t\tSIGN IN TO HAVE FUN.....\n\n\n";
    cout << "Enter Username : ";
    cin >> username;
    cout << "Enter Password : ";
    password = takePasswdFromUser();
    Credentials *cred = cred->getinstance();
    cred->setUsn(username);
    cred->setPass(password);
    cred->check();

}
