#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include "GlobalVariables_Functions.h"
#include "LibraryObject.h"
#include "LibraryInterface.h"
#include "ReaderManagement.h"

//export reader's info on screen
void exportReader(READER *p)
{
    printf("%s\t|", p->readerCode);
    printf(" %s\t|", p->name);
    if (p->isFemale == true)
        printf(" Female \t\t|");
    else
        printf(" Male \t\t|");
    printf(" %s |", p->ID);
    printf(" %u/%u/%u\t|", p->birthday.day, p->birthday.month, p->birthday.year);
    printf(" %s\t|", p->email);
    printf(" %u/%u/%u\n", p->creationDate.day, p->creationDate.month, p->creationDate.year);
}
//return expiration date (4 year after creation date)
DATE getExpirationDate(DATE creationDate)
{
    DATE expirationDate;
    expirationDate = creationDate;
    expirationDate.year = creationDate.year + 4;
    return expirationDate;
}
//export list of readers on screen
void exportReaderList(LISTreaders *lr)
{
    system("cls");
    printf("--Library Management--\nNguoi dung hien tai: %s\n-->Danh sach doc gia<--\n", currentUSER->username);
    printf("Reader code\t| Full name\t| Gender\t| ID        | Birthday\t| Email\t\t\t| Created\n");
    READER *p = lr->head;
    while (p != NULL)
    {
        exportReader(p);
        p = p->next;
    }
    printf("\nPress any key to continue.\n");
    _getch();
}
//check if reader with ID exists?
//+ if READER exists, return pointer
//+ if not, return NULL
READER *isExistinListReadersID(LISTreaders *lr, char *ID)
{
    READER *p = lr->head;
    while (p != NULL)
    {
        if (_strcmpi(ID, p->ID) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
//search reader by ID
void searchReaderID(LISTreaders *lr)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Search reader by ID<--\n", currentUSER->username);
    char *ID = new char[10];
    printf("Enter ID: ");
    gets_s(ID, 10);
    importStringNotIncludeSpace(ID, 10, "ID");
    READER *reader = NULL;
    reader = isExistinListReadersID(lr, ID);
    if (reader != NULL)
    {
        printf("\nReader code\t| Full name\t| Gender\t| ID        | Birthday\t| Email\t\t\t| Created\n");
        exportReader(reader);
    }
    else
    {
        printf("Reader with ID: %s doesn't exists.", ID);
    }
    delete[]ID;
    printf("\nPress any key to continue.\n");
    _getch();
}

//Search reader by name
void searchReaderName(LISTreaders *lr)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Search reader by name<--\n", currentUSER->username);
    printf("Enter reader's name: ");
    char *name = new char[40];
    gets_s(name,40);
    printf("\nReader code\t| Full name\t| Gender\t| ID        | Birthday\t| Email\t\t\t| Created\n");
    READER *p = lr->head;
    bool exist = false;
    while (p != NULL)
    {
        if (_strcmpi(name, p->name) == 0 || strstri(p->name, name) != NULL)
        {
            exist = true;
            exportReader(p);
        }
        p = p->next;
    }
    if (exist == false)
    {
        printf("Reader with name: \"%s\" doesn't exists.", name);
    }
    delete[]name;
    printf("\nPress any key to continue.\n");
    _getch();
}

//Improve Reader Functions version 1.0 (12/4/2018)

//Update reader's info
void updateReaderInfomationV1(LISTreaders *lr, Statistics *st)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Update reader's infomation<--\n", currentUSER->username);
    char *readerCode = new char[10];
    printf("*Enter reader code: ");
    gets_s(readerCode, 10);
    importStringNotIncludeSpace(readerCode, 10, "Reader code");
    READER *current_reader = NULL;
    current_reader = isExistinListReaders(lr, readerCode);
    if (current_reader != NULL)
    {
        printf("\nReader code\t| Full name\t| Gender\t| ID        | Birthday\t| Email\t\t\t| Created\n");
        exportReader(current_reader);
        printf("\n");
        //
        int action = 0;
        bool changed = false;
        //
        printf("<> Do you want to edit \"reader's name\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*Reader's name: ");
            gets_s(current_reader->name, 40);
            changed = true;
        }
        printf("\n");
        //
        printf("<> Do you want to edit \"birthday\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*Birthday: \n");
            importDate(current_reader->birthday);
            changed = true;
        }
        printf("\n");
        //
        printf("<> Do you want to edit \"ID\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*ID: ");
            gets_s(current_reader->ID, 10);
            changed = true;
        }
        printf("\n");
        //
        printf("<> Do you want to edit \"address\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*Address: ");
            gets_s(current_reader->address, 100);
            changed = true;
        }
        printf("\n");
        //
        printf("<> Do you want to edit \"Email\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*Email: ");
            gets_s(current_reader->email, 35);
            changed = true;
        }
        printf("\n");
        //
        printf("<> Do you want to edit \"gender\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            bool oldValue = current_reader->isFemale;
            current_reader->isFemale = importGender();
            if (current_reader->isFemale != oldValue)
            {
                if (oldValue == false)
                {
                    st->readers.maleReaders -= 1;
                    st->readers.femaleReaders += 1;
                }
                else
                {
                    st->readers.maleReaders += 1;
                    st->readers.femaleReaders -= 1;
                }
            }
            changed = true;
        }
        printf("\n");
        //
        if (changed == true)
        {
            system("cls");
            printf("--Library Management--\nCurrent user: %s\n-->Update reader's infomation<--\n", currentUSER->username);
            exportReader(current_reader);
            printf("=>Reader's infomation has been changed. Press any key to continue.\n");
        }
        else
            printf("Nothing changed. Press any key to continue.\n");
    }
    else
        printf("Reader with reader code: %s doesn't exists or edit failed!\n", readerCode);
    delete[]readerCode;
    _getch();
}
//Add reader
void addReadertoDatabaseV1(LISTreaders *lr, Statistics *st)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Add new reader<--\n", currentUSER->username);
    READER *reader = NULL;
    reader = new READER;
    if (reader != NULL)
    {
        printf("*Reader code: ");
        gets_s(reader->readerCode);
        importStringNotIncludeSpace(reader->readerCode, 10, "Reader code");
        READER *temp = NULL;
        temp = isExistinListReaders(lr, reader->readerCode);
        if (temp == NULL)
        {
            printf("*Reader's name: ");
            gets_s(reader->name, 40);
            printf("*Birthday: \n");
            importDate(reader->birthday);
            printf("*ID: ");
            gets_s(reader->ID, 10);
            importStringNotIncludeSpace(reader->ID, 10, "ID");
            printf("*Address: ");
            gets_s(reader->address, 100);
            printf("*Email: ");
            gets_s(reader->email, 35);
            importStringNotIncludeSpace(reader->email, 35, "Email");
            reader->isFemale = importGender();
            if (reader->isFemale == false)
                st->readers.maleReaders += 1;
            else
                st->readers.femaleReaders += 1;
            reader->creationDate = getCurrentDate();
            reader->expirationDate = getExpirationDate(reader->creationDate);
            reader->prev = NULL;
            reader->next = NULL;
            addREADERtoLast(lr, reader);
            system("cls");
            printf("--Library Management--\nCurrent user: %s\n-->Add new reader<--\n", currentUSER->username);
            exportReader(reader);
            printf("=>Reader %s (%s) has been created. Press any key to continue.\n", reader->name, reader->readerCode);
        }
        else
        {
            printf("Reader with reader code: %s already exists. Press any key to continue.\n", reader->readerCode);
            deleteReader(reader);
        }
    }
    else
        printf("ERROR!");
    _getch();
}
//Delete reader
void deleteReaderFromDatabaseV1(LISTreaders *lr, Statistics *st)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Delete reader<--\n", currentUSER->username);
    char *readerCode = new char[10];
    printf("Enter reader code: ");
    gets_s(readerCode, 10);
    importStringNotIncludeSpace(readerCode, 10, "Email");
    READER *p = NULL;
    p = isExistinListReaders(lr, readerCode);
    if (p != NULL)
    {
        printf("\nReader code\t| Full name\t| Gender\t| ID        | Birthday\t| Email\t\t\t| Created\n");
        exportReader(p);
        printf("\n=> Do you want to delete this reader? (1. Yes/ 0. No): ");
        int action = 0;
        scanf_s("%d", &action);
        cleartemp();
        if (action == 0)
        {
            printf("Reader %s (%s) has not been deleted. ", p->name, p->readerCode);
            p = NULL;
            deleteReader(p);
        }
        else
        {
            if (p->isFemale == false)
                st->readers.maleReaders -= 1;
            else
                st->readers.femaleReaders -= 1;
            deleteReaderinList(lr, p);
            printf("Deleted reader %s (%s). ", p->name, p->readerCode);
        }
    }
    else
    {
        printf("Reader %s doesn't exists. ", readerCode);
        deleteReader(p);
    }
    delete[]readerCode;
    printf("Press any key to continue.\n");
    _getch();
}
//check if reader expired? 4 year after created
bool isExpired(READER *p)
{
    if (dayBetween(p->expirationDate, getCurrentDate()) < 0)
        return true;
    else
        return false;
}
//renew reader card (8/5/2018)
void renewReader(LISTreaders *lr)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Renew reader card<--\n", currentUSER->username);
    char *readerCode = new char[10];
    printf("*Enter reader code: ");
    gets_s(readerCode, 10);
    importStringNotIncludeSpace(readerCode, 10, "reader code");
    READER *current_reader = NULL;
    current_reader = isExistinListReaders(lr, readerCode);
    if (current_reader != NULL)
    {
        printf("\nReader code\t| Full name\t| Gender\t| ID        | Birthday\t| Email\t\t\t| Created\n"); 
        exportReader(current_reader);
        printf("\n");
        //
        if (isExpired(current_reader) == true)
        {
            printf("Do you want to renew reader card? (1. Yes / 0. No): ");
            int yesno = 0;
            scanf_s("%d", &yesno);
            if (yesno == 0)
                printf("Reader has not been renewed.\n");
            else
            {
                current_reader->expirationDate = getExpirationDate(getCurrentDate());
                printf("Reader has been renewed, new expiration daye is %d/%d/%d\n", current_reader->expirationDate.day, current_reader->expirationDate.month, current_reader->expirationDate.year);
            }
        }
        else
            printf("Cannot renew this reader.\n");
    }
    else
        printf("Reader %s doesn't exists or failed!\n", readerCode);
    delete[]readerCode;
    _getch();
}