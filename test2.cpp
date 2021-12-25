
// Unit test, right values
#include "stdafx.h"
#include "backend.h"


void TestFunction()
{
    int status = decAndExec();
    //when status isn't zero error occured
    if (status != 0)
    {
        printf("Test failed when testing decAndExec ");
        return;
    }
    // if no error was found
    printf("Test passed when testing decAndExec ");
    return;
}