#include <iostream>
#include "splash.cpp"
#include "curruseradapter.cpp"
#include "login.cpp"
#include "register.cpp"
#include "allmyusers.cpp"
#include "messagescreen.cpp"
using namespace std;


int main()
{

  splash();
    int lrflag = 0;
   system("CLS");
     cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t >> Login...\n";
    cout << "\t\t\t\t\t\t\t\t\t    Register...\n";
    char motion = getch();
    lrflag=1;
    while(motion!=13)
    {
        if(lrflag)
        {
            system("CLS");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            lrflag=0;
            cout << "\t\t\t\t\t\t\t\t\t    Login...\n";
            cout << "\t\t\t\t\t\t\t\t\t >> Register...\n";
        }
        else
        {
            system("CLS");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            lrflag=1;
            cout << "\t\t\t\t\t\t\t\t\t >> Login...\n";
            cout << "\t\t\t\t\t\t\t\t\t    Register...\n";
        }
        motion = getch();
    }
    if(!lrflag){
        registeruser();
        
         login();
    }
    else
        login();
    system("CLS");
    if(!calling())
     msgscreen();
    else
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

      msgscreen();
    }


    return 0;
}
