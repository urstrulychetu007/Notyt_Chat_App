#include<iostream>
#include "useful.cpp"
#include<mysql.h>
#include<sstream>
using namespace std;


int retrieveandcheck(MYSQL* conn)
{
        MYSQL_ROW row;
        MYSQL_RES* res;
        int qstate = mysql_query(conn,"SELECT *  from users;");
        res = mysql_store_result(conn);
        while(row=mysql_fetch_row(res))
        {
            if(row[1]==to_string(id))return 1;
        }
        return 0;
}


int insertdata(MYSQL* conn,string username,string uid,string name,string password,string mobile)
{
    stringstream ss;
    ss << "insert into users values('"+username+"',"+uid+",'"+name+"','"+password+"','"+mobile+"');";
    string query = ss.str();
    const char* q = query.c_str();
    int qstate = mysql_query(conn,q);
    if(q){
     cout << "\t\t\t\t\t\t\t\t\tRegistered Successfully...!!\n\n\n\n\n\n\n\n\t\t\t";return 1;}
    else{
     cout << "\t\t\t\t\t\t\t\t\tRegistered Unsuccessfully...!!\n\n\n\n\n\n\n\n\t\t\t";return 0;}
}


int registeruser()
{
    system("CLS");
    cout << "\t\t\t\t\t\t\t\t\tWELCOME TO NOTyT\n\n\n\n\n\n\n\n\t\t\t";
    string username,password,name,mobile,uid,confirmpass;
    cout << "Enter Full Name                        :  ";
    getline(cin,name);
    cout << "\t\t\tEnter Username                   :  ";
    cin >> username;
    cout << "\t\t\tEnter Mobile Number              :  ";
    cin >> mobile;
    cout << "\t\t\tEnter Password of 8 digits min   :  ";
    password = takePasswdFromUser();
    cout << "\t\t\tRe-Type Password                 :  ";
    confirmpass = takePasswdFromUser();
    try
    {
        if( password.length() < 7)throw 0;
            if(password == confirmpass &&  password.length() > 7)
        {
            genuid();
            MYSQL* conn = connectdb();
            int flag = retrieveandcheck(conn);
            if(flag)
            id*=1000;
            uid = to_string(id);
            int successstatus =  insertdata(conn,username,uid,name,password,mobile);
        }
      
    }
    catch(int i)
    {
        cout << "Entered password and confirm password correctly or check the length of password...should be > 7\n";
    }
    exit(0);
    system("PAUSE");

    return 0;
}
