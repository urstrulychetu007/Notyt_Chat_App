#include<iostream>
#include<time.h>
#include<windows.h>
#include<map>

using namespace std;
static long long int id;
map<string,int> cmap = {
                        { "Black"       , 0  },
                        { "Blue"        , 1  },
                        { "Green"       , 2  },
                        { "Aqua"        , 3  },
                        { "Red"         , 4  },
                        { "Purple"      , 5  },
                        { "Yellow"      , 6  },
                        { "White"       , 7  },
                        { "Gray"        , 8  },
                        { "Light_Blue"  , 9  },
                        { "Light_Green" , 10 },
                        { "Light_Aqua"  , 11 },
                        { "Light_Red"   , 12 },
                        { "Light_Purple", 13 },
                        { "Light_Yellow", 14 },
                        { "Bright_White", 15 } };

HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );


void color( string s )
{
   SetConsoleTextAttribute( h, cmap[s] );        // need to add some checking ... job for another day
}


int genuid()
{

    srand (time(NULL));
    id = (rand() % 999999999999 + 1);
}

