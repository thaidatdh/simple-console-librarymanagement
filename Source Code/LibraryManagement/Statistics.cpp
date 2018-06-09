#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "LibraryObject.h"
#include "GlobalVariables_Functions.h"
#include "LibraryInterface.h"
#include "Statistics.h"

//show number of borrowed books 
void showNumberofBorrowedBook(Statistics *st)
{
    printf("<1>. Number of borrowed books: %u\n", st->books.borrowedBooks);
    printf("Press any key to continue.\n");
    _getch();
}
//show reader and late days
void printLateReader(BBILL *p, int day)
{
    printf("%s\t| %s\t\t|%d\n", p->readerCode, p->name, day);
}
//show list of late returning readers
void showLateReaders(Statistics *st)
{
    //update data to RAM
    printf("Loading...");
    LISTbbills *b = createListBBill();
    readListBBills(b);
    LISTrbills *r = createListRBill();
    readListRBills(r);
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Basic statistics<--\n", currentUSER->username);
    printf("<2>. Late of late readers:\n");
    printf("Reader code\t|\tReader's name\t| Late:\n");
    //Check and show late reader
    BBILL *p = b->tail;
    while (p != NULL)
    {
        int day = dayBetween(p->expectedReturnDate, getCurrentDate());
        if (isExistinListRBills(r, p->billCode) == NULL && day > 0)
        {
            printLateReader(p, day);
        }
        p = p->prev;
    }
    printf("\nPress any key to continue.\n");
    //release 
    deleteListBBILL(b);
    deleteListRBILL(r);
    _getch();
}
//Hien thi so sach co trong thu vien
void showNumberofBooks(Statistics *st)
{
    printf("<3>. So luong sach trong thu vien: %u\n", st->books.total);
    printf("Nhan phim bat ky de tro lai.\n");
    _getch();
}
//Show number of books by category
void showNumberofBooksbyCategory(Statistics *st)
{
    printf("<4>. Number of books by category: \n");
    BookCategories *p = st->books.categories;
    for (unsigned int i = 0; i < st->books.numberOfCategories; i++)
    {
        printf("%s\t|\t%u\n", p->name, p->number);
        p = p->next;
    }
    printf("Press any key to continue.\n");
    _getch();
}
//Show number of readers
void showNumberofReaders(Statistics *st)
{
    printf("<5>. Number of readers: %u\n", st->readers.femaleReaders + st->readers.maleReaders);
    printf("Press any key to continue.\n");
    _getch();
}
//Show number of readers by gender
void showNumberofReadersbyGender(Statistics *st)
{
    printf("<6>. Number of readers by gender:\n");
    printf(" * Male: %u\n * Female: %u\n", st->readers.maleReaders, st->readers.femaleReaders);
    printf("Press any key to continue.\n");
    _getch();
}