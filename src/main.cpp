#include "Application.h"
int main()
{
    Application App;
    if (App.Init())
    {
        while (App.Update()) {}
        App.Clean();
    }

}



