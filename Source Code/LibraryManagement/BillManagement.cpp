#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "GlobalVariables_Functions.h"
#include "LibraryObject.h"
#include "LibraryInterface.h"
#include "BookManagement.h"
#include "BillManagement.h"
//creating date function from borrowDate, new day is 7 days a borrowDate
DATE getExpectedReturnDate(DATE borrowDate)
{
    DATE expectDate = borrowDate;
    if (expectDate.day + 7 > maxDay(borrowDate.month, borrowDate.year))
    {
        expectDate.day = expectDate.day + 7 - maxDay(borrowDate.month, borrowDate.year);
        if (expectDate.month + 1 > 12)
        {
            expectDate.month = 1;
            expectDate.year += 1;
        }
        else
            expectDate.month += 1;
    }
    else
        expectDate.day += 7;
    return expectDate;
}
//Check input "book" is exist in list?
bool isExistinListBorrowBooks(borrowedBooks *&list, unsigned int number, borrowedBooks book)
{
    for (unsigned int j = 0; j < number; j++)
    {
        if (_strcmpi(book.ISBN, list[j].ISBN) == 0)
            return true;
    }
    return false;
}
//function that allow to import books to the borrow book list
void importBorrowBooks(borrowedBooks *&list, unsigned int number, LISTbooks *lb)
{
    for (unsigned int i = 0; i < number; i++)
    {
        printf("Enter ISBN: ");
        gets_s(list[i].ISBN, 10);
        importStringNotIncludeSpace(list[i].ISBN, 10, "ISBN");
        bool isExistinList = isExistinListBorrowBooks(list, i, list[i]);
        BOOK *isExistBook = isExistinListBooks(lb, list[i].ISBN);
        while (isExistinList == true || isExistBook == NULL || isExistBook->available == 0)
        {
            if (isExistinList == true)
                printf("*%s is exist in borrow list.\n", list[i].ISBN);
            if (isExistBook == NULL)
                printf("*%s is not exist in library.\n", list[i].ISBN);
            if (isExistBook != NULL)
                if (isExistBook->available == 0)
                    printf("*All the books %s have been borrowed.\n", list[i].ISBN);
            printf("=> Enter ISBN again: ");
            gets_s(list[i].ISBN, 10);
            importStringNotIncludeSpace(list[i].ISBN, 10, "ISBN");
            isExistinList = isExistinListBorrowBooks(list, i, list[i]);
            isExistBook = isExistinListBooks(lb, list[i].ISBN);
        }
        list[i].price = isExistBook->price;
        isExistBook->available -= 1;
    }
}
//export returning bill
void exportBorrowBills(BBILL *p)
{
    printf("Borrow Bill information:\n");
    printf("*Bill code: %s\n*Reader code: %s\n", p->billCode, p->readerCode);
    printf("*Borrow date: %u/%u/%u\n", p->borrowDate.day, p->borrowDate.month, p->borrowDate.year);
    printf("*Expect return date: %u/%u/%u\n", p->expectedReturnDate.day, p->expectedReturnDate.month, p->expectedReturnDate.year);
    printf("*Borrowed book list:\n");
    for (unsigned int i = 0; i < p->numberofBooks; i++)
        printf("\t*%s\n", p->list[i].ISBN);
}
//get the number of books in library (not use in V2)
unsigned int getNumberofBooksinLibrary(LISTbooks *lb)
{
    int count = 0;
    BOOK *p = lb->head;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

//function allow import books you want to return
void importReturnBooks(borrowedBooks *&list, unsigned int number, borrowedBooks *&borrowlist, unsigned int borrowNumber, LISTbooks *lb)
{
    for (unsigned int i = 0; i < number; i++)
    {
        printf("Enter ISBN: ");
        gets_s(list[i].ISBN, 10);
        importStringNotIncludeSpace(list[i].ISBN, 10, "ISBN");
        bool isExistinListBorrow = isExistinListBorrowBooks(borrowlist, borrowNumber, list[i]);
        bool isExistinList = isExistinListBorrowBooks(list, i, list[i]);
        while (isExistinList == true || isExistinListBorrow == false)
        {
            if (isExistinList == true)
                printf("*%s already exists in returning list.\n", list[i].ISBN);
            if (isExistinListBorrow == false)
                printf("*%s is not exist in borrowing list.\n", list[i].ISBN);
            printf("=> Please enter ISBN again: ");
            gets_s(list[i].ISBN, 10);
            importStringNotIncludeSpace(list[i].ISBN, 10, "ISBN");
            isExistinListBorrow = isExistinListBorrowBooks(borrowlist, borrowNumber, list[i]);
            isExistinList = isExistinListBorrowBooks(list, i, list[i]);
        }
        list[i].price = borrowlist[i].price;
        BOOK *isExistBook = isExistinListBooks(lb, list[i].ISBN);
        if (isExistBook != NULL)
        {
            if (isExistBook->number <= isExistBook->available)
                isExistBook->available = isExistBook->number;
            else
                isExistBook->available += 1;
        }
        isExistBook = NULL;
        delete isExistBook;
    }
}
//check if the book is lost
//(book not return when create bill  ==  lost)
bool isLost(borrowedBooks book, RBILL *rbill)
{
    for (unsigned int i = 0; i < rbill->numberofBooks; i++)
    {
        if (_strcmpi(book.ISBN, rbill->list[i].ISBN) == 0)
            return false;
    }
    return true;
}
//calculate money that reader fined because they lost books
unsigned int fineLostBooks(RBILL *p, BBILL *bbill)
{
    unsigned int fine = 0;
    for (unsigned int i = 0; i < bbill->numberofBooks; i++)
    {
        if (isLost(bbill->list[i], p) == true)
        {
                fine = fine + 2*bbill->list[i].price;
        }
    }
    return fine;
}
//export returning bill
void exportReturnBill(RBILL *rbill)
{
    printf("Returning bill infomation:\n");
    printf("*Bill code: %s\nFined money: %u\n", rbill->billCode, rbill->fineMoney);
    printf("*List returned books:\n");
    for (unsigned int i = 0; i < rbill->numberofBooks; i++)
        printf("\t%s\n", rbill->list[i].ISBN);
}

//Improve function version 2.0 (18/04/2018)

//create borrowing bill (edited)
void createBorrowBillV2()
{
    //upload list reader data to RAM
    system("cls");
    printf("Loading...\n");
    LISTreaders *lr = createListReader();
    readListReaders(lr);
    //check reader
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Create borrowing bill<--\n", currentUSER->username);
    char *readerCode = new char[10];
    printf("Enter reader code: ");
    gets_s(readerCode, 10);
    importStringNotIncludeSpace(readerCode, 10, "Reader code");
    READER *rd = isExistinListReaders(lr, readerCode);
    int daysExpired = 0;
    if (rd!=NULL) 
        daysExpired = dayBetween(getCurrentDate(), rd->expirationDate);
    while (rd == NULL || daysExpired <= 0)
    {
        if (rd == NULL)
            printf("Reader code doesn't exists, please enter again: ");
        else if (daysExpired <= 0)
            printf("Reader expired, please enter again: ");
        gets_s(readerCode, 10);
        rd = isExistinListReaders(lr, readerCode);
        if (rd != NULL)
            daysExpired = dayBetween(getCurrentDate(), rd->expirationDate);
    }
    //upload other data from file to RAM
    LISTbooks *lb = createListBook();
    readListBooks(lb);
    LISTbbills *lbbill = createListBBill();
    readListBBills(lbbill);
    Statistics *st = new Statistics;
    readStatistics(st);
    //create bill
    BBILL *p = NULL;
    p = new BBILL;
    if (p != NULL)
    {
        printf("Enter bill code: ");
        gets_s(p->billCode, 10);
        importStringNotIncludeSpace(p->billCode, 10, "Bill code");
        BBILL *temp = NULL;
        temp = isExistinListBBills(lbbill, p->billCode);
        if (temp == NULL)
        {
            strcpy_s(p->readerCode, 10, readerCode);
            strcpy_s(p->ID, 10, rd->ID);
            strcpy_s(p->name, 40, rd->name);
            p->borrowDate = getCurrentDate();
            p->expectedReturnDate = getExpectedReturnDate(p->borrowDate);
            printf("Enter number of book you want to borrow: ");
            p->numberofBooks = 0;
            scanf_s("%u", &(p->numberofBooks));
            cleartemp();
            while (p->numberofBooks <= 0 || p->numberofBooks > st->books.total)
            {
                printf("Please enter again: ");
                scanf_s("%u", &(p->numberofBooks));
                cleartemp();
            }
            p->list = new borrowedBooks[p->numberofBooks];
            importBorrowBooks(p->list, p->numberofBooks, lb);
            //
            st->books.borrowedBooks += p->numberofBooks;
            //
            p->next = NULL;
            p->prev = NULL;
            addBBILLtoLast(lbbill, p);
            system("cls");
            printf("--Library Management--\nCurrent user: %s\n-->Create borrowing bill<--\n", currentUSER->username);
            exportBorrowBills(p);
            printf("=>Bill is created. Press any key to continue.\n");
        }
        else
        {
            printf("Bill %s exists. Press any key to continue.\n", p->billCode);
            p->list = new borrowedBooks[1];
            deleteBBill(p);
        }
    }
    else printf("ERROR!\n");
    //export data to file
    //(because changed value)
    writeListBBills(lbbill);
    writeListBooks(lb);
    writeStatistics(st);
    //release memory
    rd = NULL;
    delete rd;
    deleteListREADER(lr);
    deleteListBBILL(lbbill);
    deleteListBOOK(lb);
    deleteStatistics(st);
    _getch();
    //return to commandInterface
    commandInterface();
}
//create returning bill (edited)
void createReturnBillV2()
{
    //upload data from file to RAM
    system("cls");
    printf("Loading...\n");
    LISTbooks *lb = createListBook();
    readListBooks(lb);
    LISTbbills *lbbill = createListBBill();
    readListBBills(lbbill);
    LISTrbills *lrbill = createListRBill();
    readListRBills(lrbill);
    Statistics *st = new Statistics;
    readStatistics(st);
    //create bill
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Create returning bill<--\n", currentUSER->username);
    RBILL *p = NULL;
    p = new RBILL;
    if (p != NULL)
    {
        printf("Enter bill code: ");
        gets_s(p->billCode, 10);
        importStringNotIncludeSpace(p->billCode, 10, "Bill code");
        BBILL *temp_bbill = NULL;
        temp_bbill = isExistinListBBills(lbbill, p->billCode);
        RBILL *temp_rbill = NULL;
        temp_rbill = isExistinListRBills(lrbill, p->billCode);
        if (temp_bbill != NULL && temp_rbill == NULL)
        {
            p->returnDate = getCurrentDate();
            int *days = new int;
            *days = dayBetween(temp_bbill->expectedReturnDate, p->returnDate);
            if (*days > 0)
                p->fineMoney = (unsigned int)(*days) * 5000;
            else
                p->fineMoney = 0;
            delete days;
            printf("Enter number of books you want to return: ");
            p->numberofBooks = 0;
            scanf_s("%u", &(p->numberofBooks));
            cleartemp();
            while (p->numberofBooks <= 0 || p->numberofBooks > temp_bbill->numberofBooks)
            {
                printf("Please enter again: ");
                scanf_s("%u", &(p->numberofBooks));
                cleartemp();
            }
            p->list = new borrowedBooks[p->numberofBooks];
            importReturnBooks(p->list, p->numberofBooks, temp_bbill->list, temp_bbill->numberofBooks, lb);
            p->next = NULL;
            p->prev = NULL;
            p->fineMoney = p->fineMoney + fineLostBooks(p, temp_bbill);
            addRBILLtoLast(lrbill, p);
            st->books.borrowedBooks -= p->numberofBooks;
            system("cls");
            printf("--Library Management--\nCurrent user: %s\n-->Create returning bill<--\n", currentUSER->username);
            exportReturnBill(p);
            printf("=>Bill is created. Press any key to continue.\n");
        }
        else
        {
            printf("Returned bill %s exists or doesn't exist in borrowed list.\n", p->billCode);
            printf("Press any key to continue.\n");
            p->list = new borrowedBooks[1];
            deleteRBill(p);
        }
    }
    else printf("ERROR!\n");
    //export data to file
    //(because changed value)
    writeListRBills(lrbill);
    writeListBooks(lb);
    writeStatistics(st);
    //release memory
    deleteListRBILL(lrbill);
    deleteListBOOK(lb);
    deleteListBBILL(lbbill);
    deleteStatistics(st);
    _getch();
    commandInterface();
}