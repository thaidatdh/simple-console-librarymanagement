#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <signal.h>
#include "LibraryInterface.h"
#include "LibraryObject.h"
#include "GlobalVariables_Functions.h"
#include "UserManagement.h"
#include "ReaderManagement.h"
#include "BookManagement.h"
#include "BillManagement.h"
#include "Statistics.h"
void statisticsInterface()
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Basic statistics<--\n", currentUSER->username);
    int maxActions = 2;
    printf("1. Borrowed books.\n");
    printf("2. Late returning readers.\n");
    if (currentUSER->isAdmin == true || currentUSER->isManager)
    {
        maxActions = 6;
        printf("3. Books in library.\n");
        printf("4. Books by category.\n");
        printf("5. Number of readers.\n");
        printf("6. Number of readers by gender.\n");
    }
    printf("0. Back.\n\n");
    printf("=> Choose action (0-%d): ", maxActions);
    int action = 0;
    do
    {
        scanf_s("%d", &action);
    } while (action < 0 || action > maxActions);
    cleartemp();
    Statistics *st = createStatistics();
    if (action != 0 && action <= maxActions)
    {
        readStatistics(st);
    }
    printf("\n");
    switch (action)
    {
    case 0:
        delete st;
        commandInterface();
        break;
    case 1:
        showNumberofBorrowedBook(st);
        break;
    case 2:
        showLateReaders(st);
        break;
    default:
        if (maxActions == 6)
        {
            switch (action)
            {
            case 3:
                showNumberofBooks(st);
                break;
            case 4:
                showNumberofBooksbyCategory(st);
                break;
            case 5:
                showNumberofReaders(st);
                break;
            case 6:
                showNumberofReadersbyGender(st);
                break;
            default:
                break;
            }
        }
    }
    if (action != 0 && action <= maxActions)
    {
        writeStatistics(st);
        deleteListCategory(st->books.categories);
        delete st;
    }
    if (action >= 1 && action <= maxActions)
        statisticsInterface();
}
void bookManagementInterface()
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Book management<--\n", currentUSER->username);
    int maxActions = 2;
    printf("1. Search book by ISBN.\n");
    printf("2. Search book by name.\n");
    if (currentUSER->isAdmin == true || currentUSER->isManager)
    {
        maxActions = 6;
        printf("3. View list of books.\n");
        printf("4. Add new book.\n");
        printf("5. Update book's infomation.\n");
        printf("6. Delete book.\n");
    }
    printf("0. Back.\n\n");
    printf("=> Choose action (0-%d): ", maxActions);
    int action = 0;
    do
    {
        scanf_s("%d", &action);
    } while (action < 0 || action > maxActions);
    cleartemp();
    LISTbooks *lb = createListBook();
    Statistics *st = createStatistics();
    if (action != 0 && action <= maxActions)
    {
        readListBooks(lb);
        readStatistics(st);
    }
    switch (action)
    {
    case 0:
        deleteListBOOK(lb);
        delete st;
        commandInterface();
        break;
    case 1:
        searchBookISBN(lb);
        break;
    case 2:
        searchBookName(lb);
        break;
    default:
        if (maxActions == 6)
        {
            switch (action)
            {
            case 3:
                exportBookList(lb);
                break;
            case 4:
                addBooktoDatabaseV1(lb, st);
                break;
            case 5:
                updateBookInfomationV1(lb, st);
                break;
            case 6:
                deleteBookFromDatabaseV1(lb, st);
                break;
            default:
                break;
            }
        }

        break;
    }
    if (action != 0 && action <= maxActions)
    {
        writeListBooks(lb);
        deleteListBOOK(lb);
        writeStatistics(st);
        deleteListCategory(st->books.categories);
        delete st;
    }
    if (action >= 1 && action <= maxActions)
        bookManagementInterface();
}
void readerManagementInterface()
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Reader management<--\n", currentUSER->username);
    int maxActions = 6;
    printf("1. View list of readers.\n");
    printf("2. Update reader's infomation.\n");
    printf("3. Add reader.\n");
    printf("4. Search reader by CMND.\n");
    printf("5. Search reader by name.\n");
    printf("6. Renew reader card.\n");
    if (currentUSER->isAdmin == true || currentUSER->isManager == true)
    {
        maxActions = 7;
        printf("7. Delete reader.\n");
    }
    printf("0. Back.\n\n");
    printf("=> Choose action (0-%d): ", maxActions);
    int action = 0;
    do
    {
        scanf_s("%d", &action);
    } while (action < 0 || action > maxActions);
    cleartemp();
    LISTreaders *lr = createListReader();
    Statistics *st = createStatistics();
    if (action != 0 && action <= maxActions)
    {
        readListReaders(lr);
        readStatistics(st);
    }
    switch (action)
    {
    case 0:
        deleteListREADER(lr);
        delete st;
        commandInterface();
        break;
    case 1:
        exportReaderList(lr);
        break;
    case 2:
        updateReaderInfomationV1(lr, st);
        break;
    case 3:
        addReadertoDatabaseV1(lr, st);
        break;
    case 4:
        searchReaderID(lr);
        break;
    case 5:
        searchReaderName(lr);
        break;
    case 6:
        renewReader(lr);
        break;
    default:
        if (maxActions == 7 && action == 7)
        {
            deleteReaderFromDatabaseV1(lr, st);
        }
        break;
    }
    if (action != 0 && action <= maxActions)
    {
        writeListReaders(lr);
        deleteListREADER(lr);
        writeStatistics(st);
        deleteListCategory(st->books.categories);
        delete st;
    }
    if (action >= 1 && action <= maxActions)
        readerManagementInterface();
}
void userManagementInterface()
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->User management<--\n", currentUSER->username);
    int maxActions = 2;
    printf("1. Change password.\n");
    printf("2. Update user's infomation.\n");
    if (currentUSER->isAdmin == true)
    {
        maxActions = 5;
        printf("3. Add user.\n");
        printf("4. Decentralize user.\n");
        printf("5. Change user's status.\n");
    }
    printf("0. Back.\n\n");
    printf("=> Choose action (0-%d): ", maxActions);
    int action = 0;
    do
    {
        scanf_s("%d", &action);
    } while (action < 0 || action > maxActions);
    cleartemp();
    LISTusers *lu = createList();
    if (action != 0 && action <= maxActions)
    {
        readListUsers(lu);
    }
    switch (action)
    {
    case 0:
        deleteListUSER(lu);
        commandInterface();
        break;
    case 1:
        changePassword(lu);
        break;
    case 2:
        updateUserInfomation(lu);
        break;
    default:
        if (maxActions == 5)
        {
            if (action == 3)
                addUsertoDatabase(lu);
            else if (action == 4)
                decentralizeUsers(lu);
            else if (action == 5)
                changeStatus(lu);
        }
        break;
    }
    if (action != 0 && action <= maxActions)
    {
        writeListUsers(lu);
        deleteListUSER(lu);
    }
    if (action >= 1 && action <= maxActions)
        userManagementInterface();
}
void commandInterface()
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n\n",currentUSER->username);
    int maxActions = 6;
    printf("1. User management.\n");
    printf("2. Reader management.\n");
    printf("3. Book management.\n");
    printf("4. Create borrowing bill.\n");
    printf("5. Create returning bill.\n");
    printf("6. Basic statistic.\n");
    printf("0. Sign out.\n\n");
    printf("=> Choose action (0-%d): ",maxActions);
    int action = 0;
    scanf_s("%d", &action);
    cleartemp();
    switch (action)
    {
    case 1:
        userManagementInterface();
        break;
    case 2:
        readerManagementInterface();
        break;
    case 3:
        bookManagementInterface();
        break;
    case 4:
        createBorrowBillV2();
        break;
    case 5:
        createReturnBillV2();
        break;
    case 0:
        logout();
        mainInterface();
        break;
    default:
        if (action == 6 && maxActions == 6)
        {
            statisticsInterface();
        }
        else
        {
            commandInterface();
        }
        break;
    }
}
void loginInterface()
{
    system("cls");
    printf("--Library Management--\n\n");
    char username[20], password[20];
    printf(" * Username: ");
    gets_s(username);
    importStringNotIncludeSpace(username, 20, "Username");
    printf(" * Password: ");
    gets_s(password);
    importStringNotIncludeSpace(password, 20, "Password");
    if (login(username, password) == false)
    {
        printf("=> Username or Password is incorrect. Press any key to continue.");
        _getch();
        loginInterface();
    }
    else
    {
        if (currentUSER->status == true)
        {
            commandInterface();
        }
        else
        {
            printf("=>Account has been locked. Please contact admin for more details.\n");
        }
    }
}
void loginCommandLine(char *username, char *password)
{
    if (login(username, password) == false)
    {
        printf("=> Username or Password is incorrect. Press any key to continue.");
        _getch();
        mainInterface();
    }
    else
    {
        if (currentUSER->status == true)
        {
            commandInterface();
        }
        else
        {
            printf("=>Account has been locked. Please contact admin for more details.\n");
        }
    }
}
void mainInterface()
{
    system("cls");
    printf("--Library Management--\n\n");
    printf("1. Sign in.\n0. Exit.\n\n");
    printf("=> Choose action (1 / 0): ");
    int action = 0;
    scanf_s("%d", &action);
    cleartemp();
    switch (action)
    {
    case 1:
        loginInterface();
        break;
    case 0:
        {
            printf("=> Do you want to exit? (y,n): ");
            char exitaction; 
            do 
            { 
                scanf_s("%c", &exitaction,sizeof(char)); 
                //cleartemp();
            } while (exitaction != 'y' && exitaction != 'n' && exitaction != 'Y' && exitaction != 'N');
            
            if (exitaction == 'n' || exitaction == 'N')
            {
                mainInterface();
                break;
            }
        }
        break;
    default:
        mainInterface();
        break;
    }
}