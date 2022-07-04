#include<iostream>
#include<fstream>
#include<string>
#include "linkedlist.cpp"


using namespace std;
static string chatwith;
static string callingyou;
using namespace std;
class Actiontabs
{
    public:
    string name,mobile;
    int ischat,isstory,iscall;
    static int noofcontacts;
    Actiontabs(string name,string mobile)
    {
        this->name = name;
        this->mobile = mobile;
        noofcontacts++;
    }
    ~Actiontabs(){}
    virtual void display() = 0;
    static void display(Actiontabs* us[])
    {
        for (int i = 0; i < noofcontacts; i++)
        {
           us[i]->display();
        }

    }
};
int Actiontabs::noofcontacts=0;
class chat:public Actiontabs
{
    string datetime;
    string lsender,lmsg;
    public :
     static int noofchats;
     chat(string name,string sender,string msg,string date):Actiontabs(name,sender),datetime(date),lsender(sender),lmsg(msg)
     {
         iscall = 0;
         ischat = 1;
         isstory = 0;
         noofchats++;
     }
     void display()
     {
        color("Light_Aqua"); cout <<"Username : " << name << "\n";
        color("Light_Red"); cout << "Message : "<<  lmsg  << " by " << lsender ;
        color("Bright_White"); cout << "\nDate and time : " << datetime  <<"\n\n" ;    
     }
     void display(Actiontabs *ac[])
     {
         for(int i = 0;i<Actiontabs::noofcontacts;i++)
         {
             if(ac[i]->ischat)
              ac[i]->display();
         }
     }
};
class calls:public Actiontabs
{
    string caller;
    string time;
    public:
    calls(string name,string acceptor,string caller,string time):Actiontabs(name,acceptor)
    {
        ischat = 0;
        iscall =1;
        isstory = 0;
        this->caller=caller;
        this->time = time;
    }
     void display()
     {
         cout <<"Username : " <<name << "\n" << "Called : "<<  caller  << " for " << time  <<" secs\n\n" ;
     }
     void display(Actiontabs *ac[])
     {
         for(int i = 0;i<Actiontabs::noofcontacts;i++)
         {
             if(ac[i]->iscall)
              ac[i]->display();
         }
     }
};
int chat::noofchats = 0;


Actiontabs **cusers = new Actiontabs*[10];
static int msguserscount = 0;
void getlastmessage(string contacter)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
      int qstate = mysql_query(connection,"set time_zone = '+05:30'");
    ss << "select * from chats where (sender = '"+contacter+"' and reciever = '" + currentuser->getUsername() + "') or (reciever = '"+contacter+"' and sender = '"+currentuser->getUsername()+"')  ORDER by id desc LIMIT 1;";
    string q = ss.str();
    const char* query = q.c_str();
      qstate = mysql_query(connection, query);
    res = mysql_store_result(connection);
    while(row = mysql_fetch_row(res))
    {
        cusers[msguserscount++] = new chat(contacter,row[0],row[2],row[4]);
      //cout << row[2] << "\n";
    }
}
void getlastcall(string contacter)
{
    msguserscount=0;
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
    ss << "select * from calls where (caller = '"+contacter+"' and acceptor = '" + currentuser->getUsername() + "') or (acceptor = '"+contacter+"' and caller = '"+currentuser->getUsername()+"')  ORDER by id desc LIMIT 1;";
    string q = ss.str();
    const char* query = q.c_str();
    int  qstate = mysql_query(connection, query);
    res = mysql_store_result(connection);
    while(row = mysql_fetch_row(res))
    {
        cusers[msguserscount++] = new calls(contacter,row[1],row[0],row[3]);
    }
}
int home(int opscreenchoice)
{
    countofappusersofmycontacts=0;
    Actiontabs::noofcontacts=0;
    chat::noofchats=0;
    allmyusers();
    if(opscreenchoice==1)
    {
        for(int i=0;i<countofappusersofmycontacts;i++)
        getlastmessage(alluserslist[i]->getUsername());
        cout << "Chat screen : \n\n";

        Actiontabs::display(cusers);
    }
    else if(opscreenchoice==2)
    {
        for(int i=0;i<countofappusersofmycontacts;i++)
        getlastcall(alluserslist[i]->getUsername());
        cout << "Call screen : \n\n";

        Actiontabs::display(cusers);
    }
    else  if(opscreenchoice==3)
     {
         cout << "Exiting....\n";
         exit(0);
     }
    else
     cout << "Please enter correct input....\n";

}

int calling()
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
    ss << "select * from calls where acceptor = '"+ currentuser->getUsername()+"' and status = 'calling' order by id desc limit 1;";
    string q = ss.str();
    const char* query = q.c_str();
    mysql_query(connection,query);
    res = mysql_store_result(connection);
    int totalrows = mysql_num_rows(res);
    if(totalrows > 0)
    {
        while(row = mysql_fetch_row(res))
         callingyou = row[0];
        return 1; 
    }
    return 0;
    
}


int acceptcall()
{
     MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
      ss << "select * from calls where acceptor='" + currentuser->getUsername() +"' and caller = '"+callingyou+"'  order by id desc limit 1;";
    
          string query = ss.str();
        const char* q = query.c_str();
       
        int qstate = mysql_query(connection,q );
        res = mysql_store_result(connection);
        string id;
        while(row = mysql_fetch_row(res))
        {
            id =row[2];
        }
       
      
       stringstream ss1;
       ss1 << "update calls set status = 'accepted' where id = "+id+";";
       string query1 = ss1.str();
       const char*  q1 = query1.c_str();
        mysql_query(connection,q1);
}
int rejectcall()
{

}

int dispusers()
{
    label:
    system("CLS");
   if(!calling())
   {
        cout << "Enter \n 1:Display chats  \n 2:Display calls screen\n3.exit \n";
    int opscreenchoice;
    cin >> opscreenchoice;
    system("CLS");
    home(opscreenchoice);
    cout << "-------------------------------------------\n1.Enter to  display all contacts \n2.Select user to Message/Call him\n 3.Go back\n ";
    int op;
    cin >> op;
    if(op==1)
    {
        for(int i=0;i<countofappusersofmycontacts;i++)
         alluserslist[i]->display();
         cout << "Enter username : ";
         cin >> chatwith;
         cout << "\n";
    }
    else if(op==2)
    {
        cout << "Enter user name : ";
        cin >> chatwith;
    }
    else
     goto label;
    if(opscreenchoice==2)
    {
        return 1; 
    }
  
   }
   else
   {
      return 2;
   }
    return 0;
}
