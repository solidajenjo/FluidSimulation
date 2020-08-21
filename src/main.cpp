#include "Application.h"

int main()
{
    Application App;
    App.Init();

    while (App.Update()) {}

    App.Clean();
}



