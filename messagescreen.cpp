#include<iostream>
#include "users.cpp"
#include "callfriend.cpp"
#include <sstream>
using namespace std;
int tcount = 0;

enum clienttype
{
    M_sender,M_reciever
};

class Messages
{
    public:
     virtual  void getMsgs(MYSQL* conn) = 0;
     virtual void sendmsg(string msg,MYSQL* conn)=0;
     static Messages* create(clienttype type);
};

class Sender:public Messages
{
    public:
     void sendmsg(string msg,MYSQL* conn)
    {
        MYSQL_ROW row;
        MYSQL_RES* res;
        stringstream ss;
        ss << " INSERT into chats (`sender`,`reciever`,`msg`,`dateandtime`) values('"+currentuser->getUsername()+ "','"+chatwith+ "','"+msg+"',now());";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn,q );

    }
    void getMsgs(MYSQL* conn)
    {
        MYSQL_ROW row;
        MYSQL_RES* res;
        int qstate = mysql_query(conn,"set time_zone = '+05:30'");
        qstate = mysql_query(conn, "SELECT * from chats");
        res = mysql_store_result(conn);
        while (row=mysql_fetch_row(res))
        {
            if(row[0] == currentuser->getUsername() and row[1] == chatwith)
            {
                color("Aqua");
                tcount++;
                std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t" << row[2] << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t" << row[4] << "\n\n";
            }
            else if(row[1] == currentuser->getUsername() and row[0] == chatwith)
            {
                color("Light_Yellow");
                tcount++;
                std::cout  <<"\t\t" << row[2] << "\n\t\t" << row[4] << "\n\n";
            }
        }


    }
};

class Reciever:public Messages
{
    public:
     void sendmsg(string msg,MYSQL* conn)
    {
        MYSQL_ROW row;
        MYSQL_RES* res;
        stringstream ss;
        ss << " INSERT into chats (`sender`,`reciever`,`msg`,`dateandtime`) values('"+currentuser->getUsername()+ "','"+chatwith+ "','"+msg+"',now());";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn,q );

    }
    void getMsgs(MYSQL* conn)
    {
        MYSQL_ROW row;
        MYSQL_RES* res;
        int qstate = mysql_query(conn,"set time_zone = '+05:30'");
        qstate = mysql_query(conn, "SELECT * from chats");
        res = mysql_store_result(conn);
        while (row=mysql_fetch_row(res))
        {
            if(row[0] == currentuser->getUsername() and row[1] == chatwith)
            {
                color("Aqua");
                tcount++;
                std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t" << row[2] << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t" << row[4] << "\n\n";
            }
            else if(row[1] == currentuser->getUsername() and row[0] == chatwith)
            {
                color("Light_Yellow");
                tcount++;
                std::cout  <<"\t\t" << row[2] << "\n\t\t" << row[4] << "\n\n";
            }
        }


    }
};

Messages* Messages::create(clienttype type)
{
    if(type==M_sender)
     return new Sender();
    else if(type==M_reciever)
     return new Reciever();
}

class Currentuserclient
{
    public:
        Currentuserclient(clienttype type)
    {
        mMessages = Messages::create(type);
    } 
    ~Currentuserclient()
    {
        if(mMessages)
        {
            delete[] mMessages;
            mMessages = NULL;
        }
    }
    Messages* getMessages()
    {
        return mMessages;
    }
    private:
     Messages* mMessages;
};

int getcount(MYSQL* conn)
{
    int prescount=0;
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
    ss << "Select * from chats where (sender = '"+currentuser->getUsername()+ "' and reciever = '"+chatwith+ "') or (sender = '"+chatwith+"' and reciever = '"+currentuser->getUsername()+ "');";
    string query = ss.str();
    const char* q = query.c_str();
    int qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
       prescount++;
    return prescount;

}



void insertintocalls(int i)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
    if(i)
    {
        ss << "select * from calls where caller='" + currentuser->getUsername() +"' and acceptor = '"+chatwith+"'  order by id desc limit 1;";
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
       ss1 << "update calls set status = 'accepted', timeoftalk = '"+ to_string(hour) + ":" +  to_string(mins) + ":" +  to_string(sec) + "' where id = "+id+";";
       string query1 = ss1.str();
       const char*  q1 = query1.c_str();
        mysql_query(connection,q1);
    }
    else
    {
       ss << "Insert into calls(`caller`,`acceptor`,`timeoftalk`,`status`) values('" + currentuser->getUsername() +"','"+chatwith+"','"+ to_string(hour) +":"+to_string(mins)+":"+ to_string(sec) +"','calling');";
       string query = ss.str();
       const char* q = query.c_str();
       int qstate = mysql_query(connection,q );
    }
}





int getchangedstatus()
{
     MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
    ss <<  "select * from calls where caller = '" + currentuser->getUsername()+"' and acceptor = '"+ chatwith+"' order by id desc limit 1;";
    string q = ss.str();
    const char* query = q.c_str();
    int qstate = mysql_query(connection,query);
    res = mysql_store_result(connection);
    string s;
    while(row=mysql_fetch_row(res))
    {
            s=row[4];
            if(s=="accepted")
              return 1;
    }
    return 0;
}


int msgscreen()
{
    label:
    char optionmc;
    int ans=dispusers();
    if(ans==0)
    {
        while(1){
            label1:
        int detectkey;
    tcount = 0;
    system("CLS");
    std::cout << "\t\t\t\t\t" << chatwith << "\n\n\n";
    Currentuserclient *myclient = new Currentuserclient(M_reciever);
    myclient->getMessages()->getMsgs(connection);
    color("White");
    cout << "PRESS CTRL FOR OPTIONS\n";
  while(1)
  {
      if(!GetAsyncKeyState(VK_CONTROL))
      {
          if(getcount(connection)>tcount)
          {
               system("CLS");
               std::cout << "\t\t\t\t\t" << chatwith << "\n\n\n";
                myclient->getMessages()->getMsgs(connection);
               color("White");
                cout << "PRESS CTRL TO FOR OPTIONS\n";
          }
          Sleep(1000);

      }
      else break;

  }

  cout << "Press M for message or Press c for call or Press b to go back \n ";

  optionmc = getch();
  if(optionmc == 'M' || optionmc == 'm')
  {
       cout << "Type Message : ";
       string msg,msg1;
       getline(cin,msg);
        getline(cin,msg1);
   
    try
    {
            if(msg!="" && msg1=="")
            myclient->getMessages()->sendmsg(msg,connection);
        else if(msg=="" && msg1!="")myclient->getMessages()->sendmsg(msg1,connection);
        else  if (msg=="" && msg1==""){throw 0; cout <<"Exception :  Can't send empty message...\n";}
    }
    catch(int i)
    {
       cout <<"Exception :  Can't send empty message...\n";
    }
    goto label1;
  }
  else if(optionmc=='c' || optionmc =='C')
  {
       int countclock=0;
        hour=0;
        mins=0;
        sec=0;
        insertintocalls(0);
        while(countclock!=30000)
        {
            system("CLS");
          if(getchangedstatus())
              break;
           else
           {
                cout << "Calling " << chatwith << "\n";
                Sleep(1000);
                countclock+=1000;
           }


        }
       if(countclock!=30000)
       {
           system("CLS");
            startclock(currentuser->getUsername(),chatwith);
       }
       insertintocalls(1);

  }
  else if(optionmc == 'B' || optionmc=='b');
   break;


}


    }
    else if(ans==2)
    {
           cout << callingyou << " Calling....";
            cout << "\n\n\n\nPress 1 to accept call \nPress 2 to reject call";
            int opaccept;
            cin >> opaccept;
            if(opaccept==1)
            {
                acceptcall();
                startclock(callingyou,currentuser->getUsername());
            }
            else
            rejectcall();
    }
    else if(ans==1)
    {
        int countclock=0;
        hour=0;
        mins=0;
        sec=0;
        insertintocalls(0);
        while(countclock!=30000)
        {
            system("CLS");
          if(getchangedstatus())
              break;
           else
           {
                cout << "Calling " << chatwith << "\n";
            Sleep(1000);
            countclock+=1000;
           }


        }
       if(countclock!=30000)
       {
           system("CLS");
            startclock(currentuser->getUsername(),chatwith);
       }

        insertintocalls(1);

    }
    system("CLS");
     goto label;
}
