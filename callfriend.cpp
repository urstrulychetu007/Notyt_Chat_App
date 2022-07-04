#include <iostream>

#include <windows.h>


using namespace std;
static  int hour;
static  int mins;
static  int sec;
int checkstatus(string caller,string acceptor)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
    ss << "select * from calls where caller = '"+caller+"' and acceptor='"+acceptor+"' order by id desc limit 1;";
    string q = ss.str();
    const char* query = q.c_str();
    mysql_query(connection,query);
    res=mysql_store_result(connection);
    string s;
    while(row=mysql_fetch_row(res))
    {
        s=row[3];
        if(s=="0:0:0")
         return 1;
        else return 0; 
    }
}
void displayTime(int hours, int minutes, int seconds) {
    
   system("cls");
   cout << chatwith << "\n";
   cout << hours << ":"
        << minutes << ":"
        << seconds << endl;

  cout << "\n\nPress Escape to cut the call...\n\n";   
    
}

int startclock(string caller,string acceptor) {
 hour = 0;
 mins = 0;
 sec = 0;
  displayTime(hour, mins, sec);

  while(!GetAsyncKeyState(VK_ESCAPE) ) {
    Sleep(1000);

    sec++;

    if(sec > 59) {
      mins++;
      sec = 0;
    } 

    if(mins > 59) {
      hour++;
      sec = 0;
      mins = 0;
    }

    displayTime(hour, mins, sec);
    if(!checkstatus(caller,acceptor))
     break;
  }
}