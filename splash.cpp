#include<iostream>
//#include<windows.h>
using namespace std;
int splash()
{
    system("CLS");
    string s;
    //Sleep(500);
    for(int i = 0;i<19;i++)
    {

        s.clear();
        system("CLS");
        for (int j = i+5; j < 45; j++)
        {
            s+="\n";
        }
        cout<<s << "\t\t\t\t\t\t\t\t";
        cout << "||||\\\\\\      ||||       |||||||||     |||||||||||    ||||     ||||   |||||||||| \n\t\t\t\t\t\t\t\t";
        cout << "|||| \\\\\\     ||||    |||         |||      ||||        ||||   ||||       ||||    \n\t\t\t\t\t\t\t\t";
        cout << "||||  \\\\\\    ||||    |||         |||      ||||           ||||           ||||    \n\t\t\t\t\t\t\t\t";
        cout << "||||   \\\\\\   ||||    |||         |||      ||||           ||||           ||||    \n\t\t\t\t\t\t\t\t";
        cout << "||||    \\\\\\  ||||    |||         |||      ||||           ||||           ||||    \n\t\t\t\t\t\t\t\t";
        cout << "||||     \\\\\\ ||||    |||         |||      ||||           ||||           ||||    \n\t\t\t\t\t\t\t\t";
        cout << "||||      \\\\\\||||       |||||||||         ||||           ||||           ||||    \n";
        //Sleep(100);
    }
    //Sleep(200);
    return 0;
}
