
#include <iostream>


#include "Core/BluePhoenix.h"



int main(void)
{
    BluePhoenix engine;

    if (engine.Init() != -1)
    {
        engine.Setup();
        engine.Run();
        engine.End();
    }

    return 0;
}