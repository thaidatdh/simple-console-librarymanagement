#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "GlobalVariables_Functions.h"
#include "LibraryObject.h"
#include "LibraryInterface.h"
#include "UserManagement.h"
//log in function
bool login(char *username, char *password)
{
    FILE *f = NULL;
    fopen_s(&f, "database\\users.dat", "rb");
    if (f != NULL)
    {
        USER *p = new USER;
        while (!feof(f))
        {
            freadUser(f, p);
            if (strcmp(p->password, password) == 0 && strcmp(p->username, username) == 0 && p->status == true)
            {
                currentUSER = p;
                fclose(f);
                return true;
            }
            else
            {
                if (strcmp(p->password, password) == 0 && strcmp(p->username, username) == 0 && p->status == false)
                {
                    printf("Dang nhap that bai. Tai khoan %s da bi khoa.\n",p->username);
                    _getch();
                    break;
                }
            }
        }
        fclose(f);
    }
    else
    {
        printf("Fail to open User file.\n");
        _getch();
    }
    return false;
}
//log out function
void logout()
{
    USER *p = new USER;
    p = currentUSER;
    currentUSER->next = NULL;
    currentUSER->prev = NULL;
    currentUSER = NULL;
    delete p;
}
//change password of current user
void changePassword(LISTusers *lu)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Change password<--\n", currentUSER->username);
    char *old_pass = new char[20];
    char *new_pass = new char[20];
    printf("Old password : ");
    gets_s(old_pass,20);
    printf("New password: ");
    gets_s(new_pass, 20);
    importStringNotIncludeSpace(new_pass, 20, "new password");
    if (strcmp(old_pass, currentUSER->password) == 0)
    {
        strcpy_s(currentUSER->password, new_pass);
        USER *current_user = NULL;
        current_user = isExistinListUsers(lu, currentUSER);
        if (current_user != NULL)
        {
            strcpy_s(current_user->password, currentUSER->password);
            printf("Changed password. Press any key to continue.\n");
        }
        else
            printf("ERROR!\n");
        _getch();
        delete[]old_pass;
        delete[]new_pass;
    }
    else
    {
        printf("Mat khau cu khong dung. Nhan phim bat ki de tro lai.");
        _getch();
    }
}
//import user's status (activated/blocked)
bool importStatus()
{
    printf("Status (1. Activated / 0. Blocked):");
    int input;
    do
    {
        scanf_s("%d", &input);
    } while (input != 0 && input != 1);
    cleartemp();
    if (input == 0)
        return false;
    else
        return true;
}
//import user's permissions(manager/staff)
bool isManager()
{
    printf("Is this user manager (0. No / 1. Yes):");
    int input;
    do
    {
        scanf_s("%d", &input);
    } while (input != 0 && input != 1);
    cleartemp();
    if (input == 0)
        return false;
    else
        return true;
}
//update current user's infomation
void updateUserInfomation(LISTusers *lu)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Update current user's infomation<--\n", currentUSER->username);
    int action = 0;
    bool changed = false;
    printf("\t<Name: %s>\n Do you want to edit \"name\"? (1. Yes / 0. No): ", currentUSER->name);
    scanf_s("%d", &action);
    cleartemp();
    if (action != 0)
    {
        printf("*Full name: ");
        gets_s(currentUSER->name, 40);
        changed = true;
    }
    printf("\n");
    //
    printf("\t<Birthday: %d/%d/%d>\n", currentUSER->birthday.day, currentUSER->birthday.month, currentUSER->birthday.year);
    printf(" Do you want to edit \"birthday\"? (1. Yes / 0. No): ");
    scanf_s("%d", &action);
    cleartemp();
    if (action != 0)
    {
        printf("*Birthday: \n");
        importDate(currentUSER->birthday);
        changed = true;
    }
    printf("\n");
    //
    printf("\t<ID: %s>\n Do you want to edit \"ID\"? (1. Yes / 0. No): ", currentUSER->ID);
    scanf_s("%d", &action);
    cleartemp();
    if (action != 0)
    {
        printf("*ID number: ");
        gets_s(currentUSER->ID, 10);
        changed = true;
    }
    printf("\n");
    //
    printf("\t<Address: %s>\n Do you want to edit \"address\"? (1. Yes / 0. No): ", currentUSER->address);
    scanf_s("%d", &action);
    cleartemp();
    if (action != 0)
    {
        printf("*Address: ");
        gets_s(currentUSER->address, 100);
        changed = true;
    }
    printf("\n");
    //
    printf("\t<Email: %s>\n Do you want to edit \"Email\"? (1. Yes / 0. No): ", currentUSER->email);
    scanf_s("%d", &action);
    cleartemp();
    if (action != 0)
    {
        printf("*Email: ");
        gets_s(currentUSER->email, 35);
        changed = true;
    }
    printf("\n");
    //
    printf("\t<Gender: %s>\n", (currentUSER->isFemale == 1)? "Nu": "Nam" );
    printf(" Do you want to edit \"gender\"? (1. Yes / 0. No): ");
    scanf_s("%d", &action);
    cleartemp();
    if (action != 0)
    {
        currentUSER->isFemale = importGender();
        changed = true;
    }
    if (changed == true)
    {
        USER *current_user = NULL;
        current_user = isExistinListUsers(lu, currentUSER);
        if (current_user != NULL)
        {
            strcpy_s(current_user->name, currentUSER->name);
            strcpy_s(current_user->ID, currentUSER->ID);
            strcpy_s(current_user->address, currentUSER->address);
            strcpy_s(current_user->email, currentUSER->email);
            current_user->birthday = currentUSER->birthday;
            current_user->isFemale = currentUSER->isFemale;
            printf("=> Changed user's infomation. Press any key to continue\n");
        }
        else
            printf("ERROR!");
    }
    else
    {
        printf("=> Nothing changed. Press any key to continue.\n");
    }
    _getch();
}
//Add new user
void addUsertoDatabase(LISTusers *lu)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Add new user<--\n", currentUSER->username);
    USER *user = NULL;
    user = new USER;
    if (user != NULL)
    {
        printf("*Username: ");
        importStringNotIncludeSpace(user->username, 20, "username");
        USER *temp = NULL;
        temp = isExistinListUsers(lu, user);
        if (temp == NULL)
        {
            printf("*Password: ");
            gets_s(user->password, 20);
            printf("*Full name: ");
            gets_s(user->name, 40);
            printf("*Birthday: \n");
            importDate(user->birthday);
            printf("*ID number: ");
            gets_s(user->ID, 10);
            printf("*Address: ");
            gets_s(user->address, 100);
            printf("*Email: ");
            gets_s(user->email, 35);
            user->isFemale = importGender();
            user->status = true;
            user->isAdmin = false;
            user->isManager = false;
            user->prev = NULL;
            user->next = NULL;
            addUSERtoLast(lu, user);
            printf("Created user %s. Press any key to continue.\n", user->username);
        }
        else
        {
            printf("User %s already exists. Press any key to continue.\n", user->username);
            deleteUser(user);
        }
    }
    else
        printf("ERROR!");
    _getch();
}
//import permissions of user p
void importDecentralization(USER *p)
{
    int i;
    printf("*User permissions of %s? (1. Manager / 2. Staff): \n", p->username);
    do
    {
        printf("Enter permissions (1 / 2): ");
        scanf_s("%d", &i);
    } while (i != 1 && i != 2);
    cleartemp();
    if (i == 1)
        p->isManager = true;
    else
        p->isManager = false;
    printf("Changed. Press any key to continue.\n");
}
//decentralize for user
void decentralizeUsers(LISTusers *lu)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Decentralize user<--\n", currentUSER->username);
    USER *p = lu->head;
    printf("Username \t\t|\t Permissions\n");
    char *pisManager = new char[20];
    while (p != NULL)
    {
        if (p->isAdmin == false)
        {
            if (p->isManager == true)
                strcpy_s(pisManager,sizeof(char)*20, "Manager");
            else
                strcpy_s(pisManager, sizeof(char) * 20, "Staff");
            printf("%s \t\t|\t %s\n", p->username, pisManager);
        }
        p = p->next;
    }
    delete[]pisManager;
    printf("* Enter username: ");
    char *iusername = new char[20];
    do
    {
        gets_s(iusername, 20);
        importStringNotIncludeSpace(iusername, 20, "Username");
        if (strcmp(iusername, "admin") == 0)
            printf("ERROR! Cannot decentralize admin account.\n");
    } while (strcmp(iusername, "admin") == 0);
    p = lu->head;
    while (p != NULL && strcmp(p->username, iusername) != 0)
    {
        p = p->next;
    }
    if (p != NULL)
    {
        importDecentralization(p);
    }
    else
    {
        printf("User %s doesn't exists. Press any key to continue.\n",iusername);
    }
    _getch();
    delete[]iusername;
    p = NULL;
    deleteUser(p);
}
//change user's status (activated/blocked)
void changeStatus(LISTusers *lu)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Change user's status<--\n", currentUSER->username);
    USER *p = lu->head;
    printf("Username \t\t|\t Status\n");
    char *pStatus = new char[10];
    while (p != NULL)
    {
        if (p->isAdmin == false)
        {
            if (p->status == true)
                strcpy_s(pStatus, sizeof(char) * 10, "Activated");
            else
                strcpy_s(pStatus, sizeof(char) * 10, "Blocked");
            printf("%s \t\t|\t %s\n", p->username, pStatus);
        }
        p = p->next;
    }
    delete[]pStatus;
    char *iusername = new char[20];
    printf("* Enter username: ");
    do
    {
        gets_s(iusername, 20);
        importStringNotIncludeSpace(iusername, 20, "Username");
        if (strcmp(iusername, "admin") == 0)
            printf("ERROR! Cannot change admin's status.\n");
    } while (strcmp(iusername, "admin") == 0);
    p = lu->head;
    while (p != NULL && strcmp(p->username, iusername) != 0)
    {
        p = p->next;
    }
    if (p != NULL)
    {
        p->status = importStatus();
        printf("Changed. Press any key to continue.\n");
    }
    else
    {
        printf("User %s doesn't exists. Press any key to continue.\n", iusername);
    }
    _getch();
    delete[]iusername;
    p = NULL;
    deleteUser(p);
}