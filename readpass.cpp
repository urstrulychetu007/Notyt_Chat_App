#include <conio.h>
#include <iostream>
using namespace std;

enum IN {

    IN_BACK = 8,
    IN_RET = 13
  
};
std::string takePasswdFromUser(
    char sp = '*')
{

    string passwd = "";
    char ch_ipt;
    while (true) {
  
        ch_ipt = getch();
        if (ch_ipt == IN::IN_RET) {
            cout << endl;
            return passwd;
        }
        else if (ch_ipt == IN::IN_BACK
                 && passwd.length() != 0) {
            passwd.pop_back();
            cout << "\b \b";
  
            continue;
        }
        else if (ch_ipt == IN::IN_BACK
                 && passwd.length() == 0) {
            continue;
        }
  
        passwd.push_back(ch_ipt);
        cout << sp;
    }
}
