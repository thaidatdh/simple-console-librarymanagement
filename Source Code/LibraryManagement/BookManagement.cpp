#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "GlobalVariables_Functions.h"
#include "LibraryObject.h"
#include "LibraryInterface.h"
#include "BookManagement.h"
//export book's info on screen
void exportBook(BOOK *p)
{
    printf("%s |",  p->ISBN);
    printf(" %s\t|", p->name);
    printf(" %s\t|", p->author);
    printf(" %s\t|", p->publisher);
    printf(" %s\t|", p->category);
    printf(" %u/%u\n", p->available, p->number);
}

//export all books in library
void exportBookList(LISTbooks *lb)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->List books<--\n", currentUSER->username);
    printf("\nISBN   | Book's name\t| Author\t| Publisher | Category |Number\n");
    BOOK *p = lb->head;
    while (p != NULL)
    {
        exportBook(p);
        p = p->next;
    }
    printf("\nPress any key to continue.\n");
    _getch();
}
//search book by ISBN
void searchBookISBN(LISTbooks *lb)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Search book by ISBN<--\n", currentUSER->username);
    char *ISBN = new char[10];
    printf("Enter ISBN: ");
    gets_s(ISBN, 10);
    importStringNotIncludeSpace(ISBN, 10, "ISBN");
    BOOK *book = NULL;
    book = isExistinListBooks(lb, ISBN);
    if (book != NULL)
    {
        printf("\nBook's code | Book's name\t| Author\t| Publisher | Category |Number\n");
        exportBook(book);
    }
    else
    {
        printf("%s doesn't exists.", ISBN);
    }
    delete[]ISBN;
    printf("\nPress any key to continue.\n");
    _getch();
}
//search book by name
void searchBookName(LISTbooks *lb)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Search book by name<--\n", currentUSER->username);
    char *name = new char[100];
    printf("Enter book's name: ");
    gets_s(name, 100);
    printf("\nBook's code | Book's name\t| Author\t| Publisher | Category |Number\n");
    bool exist = false;
    BOOK *book = lb->head;
    while (book != NULL)
    {
        if ((_strcmpi(name, book->name) == 0) || (strstri(book->name,name)!=NULL))
        {
            exportBook(book);
            exist = true;
        }
        book = book->next;
    }
    if (exist == false)
    {
        printf("Book's name \"%s\" doesn't exists.", name);
    }
    delete[]name;
    printf("\nPress any key to continue.\n");
    _getch();
}
//
//Improve functions vesion 1.0 (16/04/2018)
//

//Update book's info
void updateBookInfomationV1(LISTbooks *lb, Statistics *st)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Update book's infomation<--\n", currentUSER->username);
    char *ISBN = new char[10];
    printf("*Enter ISBN: ");
    gets_s(ISBN, 10);
    importStringNotIncludeSpace(ISBN, 10, "ISBN");
    BOOK *current_book = NULL;
    current_book = isExistinListBooks(lb, ISBN);
    if (current_book != NULL)
    {
        printf("\nBook's code | Book's name\t| Author\t| Publisher | Category |Number\n");
        exportBook(current_book);
        printf("\n");
        //
        int action = 0;
        bool changed = false;
        //
        printf("<> Do you want to edit \"book's name\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*Book's name: ");
            gets_s(current_book->name, 100);
            changed = true;
        }
        printf("\n");
        //
        printf("<> Do you want to edit \"author\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*Author's name: \n");
            gets_s(current_book->author, 100);
            changed = true;
        }
        printf("\n");
        //
        printf("<> Do you want to edit \"publisher\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*Publisher: ");
            gets_s(current_book->publisher, 60);
            changed = true;
        }
        printf("\n");
        //
        //
        printf("<> Do you want to edit \"number of books\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        int old_number = current_book->number;
        if (action != 0)
        {
            printf("*Number of book: ");
            scanf_s("%u", &(current_book->number));
            cleartemp();
            current_book->available = current_book->available + (current_book->number - old_number);
            st->books.total = st->books.total + (current_book->number - old_number);
            changed = true;
        }
        printf("\n");
        //
        printf("<> Do you want to edit \"category\"? (1. Yes / 0. No): ");
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            char *oldcategory = new char[30];
            strcpy_s(oldcategory,30, current_book->category);
            printf("*Category: ");
            gets_s(current_book->category, 30);
            //
            if (_strcmpi(oldcategory, current_book->category) != 0)
            {
                BookCategories *oldLocation = categoryLocation(st->books, oldcategory);
                BookCategories *newLocation = categoryLocation(st->books, current_book->category);
                if (oldLocation != NULL)
                {
                    if (newLocation == NULL)
                    {
                        oldLocation->number -= old_number;
                        pushCategories(st->books.categories, createNewCategory(current_book->category,current_book->number));
                        st->books.numberOfCategories += 1;
                    }
                    else
                    {
                        oldLocation->number -= old_number;
                        newLocation->number += current_book->number;
                    }
                }
            }
            //
            changed = true;
        }
        printf("\n");
        //
        printf("<Publishing year: %d> Do you want to edit \"publishing year\"? (1. Yes / 0. No): ", current_book->publishYear);
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*Publishing year: ");
            scanf_s("%u", &(current_book->publishYear));
            cleartemp();
            changed = true;
        }
        printf("\n");
        //
        printf("<Price: %d> Do you want to edit \"price\"? (1. Yes / 0. No): ",current_book->price);
        scanf_s("%d", &action);
        cleartemp();
        if (action != 0)
        {
            printf("*Price: ");
            scanf_s("%u", &(current_book->price));
            cleartemp();
            changed = true;
        }
        printf("\n");
        //
        //
        if (changed == true)
            printf("Book's infomation has been changed. Press any key to continue\n");
        else
            printf("No infomation changed. Press any key to continue.\n");
    }
    else
        printf("Fail to edit or %s doesn't exists or !\n", ISBN);
    delete[]ISBN;
    _getch();
}
//Add new book
void addBooktoDatabaseV1(LISTbooks *lb, Statistics *st)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Add new book<--\n", currentUSER->username);
    BOOK *book = NULL;
    book = new BOOK;
    if (book != NULL)
    {
        printf("*ISBN: ");
        gets_s(book->ISBN);
        importStringNotIncludeSpace(book->ISBN, 10, "ISBN");
        BOOK *temp = NULL;
        temp = isExistinListBooks(lb, book->ISBN);
        if (temp == NULL)
        {
            printf("*Book's name: ");
            gets_s(book->name, 100);
            printf("*Author: ");
            gets_s(book->author, 100);
            printf("*Publisher: ");
            gets_s(book->publisher, 60);
            printf("*Category: ");
            gets_s(book->category, 30);
            printf("*Publishing year: ");
            scanf_s("%u", &(book->publishYear));
            printf("*Price: ");
            scanf_s("%u", &(book->price));
            printf("*Number: ");
            scanf_s("%u", &(book->number));
            //
            BookCategories *Location = categoryLocation(st->books, book->category);
            if (Location == NULL)
            {
                pushCategories(st->books.categories, createNewCategory(book->category,book->number));
                st->books.numberOfCategories += 1;
            }
            else
            {
                Location->number += book->number;
            }
            //
            book->available = book->number;
            st->books.total += book->number;
            cleartemp();
            book->prev = NULL;
            book->next = NULL;
            addBOOKtoLast(lb, book);
            printf("%s (%s) has been created. Press any key to continue.\n", book->name, book->ISBN);
        }
        else
        {
            printf("%s already exists. Press any key to continue.\n", book->ISBN);
            deleteBook(book);
        }
    }
    else
        printf("ERROR!");
    _getch();
}
//Delete book
void deleteBookFromDatabaseV1(LISTbooks *lb, Statistics *st)
{
    system("cls");
    printf("--Library Management--\nCurrent user: %s\n-->Delete book<--\n", currentUSER->username);
    char *ISBN = new char[10];
    printf("Nhap ma sach cua sach can tim: ");
    gets_s(ISBN, 10);
    importStringNotIncludeSpace(ISBN, 10, "ISBN");
    BOOK *p = NULL;
    p = isExistinListBooks(lb, ISBN);
    if (p != NULL)
    {
        printf("\nBook's code | Book's name\t| Author\t| Publisher | Category |Number\n");
        exportBook(p);
        printf("\n=> Do you sure you want to delete this book? (1. Yes/ 0. No): ");
        int action = 0;
        scanf_s("%d", &action);
        cleartemp();
        if (action == 0)
        {
            printf("%s (%s) has not been deleted. ", p->name, p->ISBN);
            p = NULL;
            deleteBook(p);
        }
        else
        {
            printf("Deleted %s (%s). ", p->name, p->ISBN);
            BookCategories *Location = categoryLocation(st->books, p->category);
            if (Location != NULL)
            {
                Location->number -= p->number;
            }
            deleteBookinList(lb, p);
            st->books.total -= 1;
        }
    }
    else
    {
        printf("%s doesn't exists. ", ISBN);
        deleteBook(p);
    }
    delete[]ISBN;
    printf("Press any key to continue.\n");
    _getch();
}