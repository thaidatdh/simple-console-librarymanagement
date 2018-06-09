#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "LibraryObject.h"
#include "LibraryInterface.h"
#include "GlobalVariables_Functions.h"
#include "BillManagement.h"
int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        loginCommandLine(argv[1], argv[2]);
    }
    else if (argc > 1)
    {
        printf("Not enough reference. Please enter enough Username and Password.\n");
    }
    else
    {
        mainInterface();
    }
    deleteUser(currentUSER);
    return 0;
}
