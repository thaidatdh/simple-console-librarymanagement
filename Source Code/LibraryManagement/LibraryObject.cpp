#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "GlobalVariables_Functions.h"
#include "LibraryObject.h"
//Compare number of days between expectDate and returnDate
//return value > 0, returnDate after expectDate
//             < 0, returnDate before expectDate
int dayBetween(DATE expectDate, DATE returnDate)
{
    int days = returnDate.day - expectDate.day;
    for (unsigned int month = expectDate.month; month < returnDate.month; month++)
    {
        days = days + maxDay(month, expectDate.year);
    }
    for (unsigned int year = expectDate.year; year < returnDate.year; year++)
    {
        if (leapYear(year) == true)
            days = days + 366;
        else
            days = days + 365;
    }
    return days;
}
//Import gender
bool importGender()
{
    printf("Gender (0. Male / 1. Female): ");
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
//Check if year is a leap year
//      true == leap year
//      false == common year
bool leapYear(unsigned int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) ? true : false;
}
//function that return max day of the month
unsigned int maxDay(unsigned int month, unsigned int year)
{
    unsigned int max_day;
    switch (month)
    {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        max_day = 31;
        break;
    case 4: case 6: case 9: case 11:
        max_day = 30;
        break;
    case 2:
    {
        bool check = leapYear(year);
        if (check == true)
            max_day = 29;
        else
            max_day = 28;
        break;
    }
    }
    return max_day;
}
//Import date (day/month/year)
void importDate(DATE &d)
{
    printf("Nhap nam: ");
    scanf_s("%u", &d.year);
    do
    {
        printf("Nhap thang: ");
        scanf_s("%u", &d.month);
    } while (d.month < 1 || d.month >12);
    do
    {
        printf("Nhap ngay: ");
        scanf_s("%u", &d.day);
    } while (d.day<1 || d.day>maxDay(d.month, d.year));
    cleartemp();
}
//get current date (day/month/year)
DATE getCurrentDate()
{
    DATE currentDate;
    time_t *t = new time_t;
    *t = time(NULL);
    tm *timePointer = new tm;
    localtime_s(timePointer, t);
    currentDate.day = timePointer->tm_mday;
    currentDate.month = timePointer->tm_mon + 1;
    currentDate.year = timePointer->tm_year + 1900;
    delete t;
    delete timePointer;
    return currentDate;
}
//
//User Management functions
//

//read a variable p type USER from file f
void freadUser(FILE *f, USER *p)
{
    fread_s(p, sizeof(USER), sizeof(USER), 1, f);
    p->next = NULL;
    p->prev = NULL;
}
//write a variable p type USER to file f
void fwriteUser(FILE *f, USER *p)
{
    fwrite(p, sizeof(USER), 1, f);
}
//delete an USER from list
void deleteUser(USER *user)
{
    if (user != NULL)
    {
        user->next = NULL;
        user->prev = NULL;
        delete user;
    }
}
//creatte a LISTusers variable
LISTusers *createList()
{
    LISTusers *lu = new LISTusers;
    lu->head = NULL;
    lu->tail = NULL;
    return lu;
}
//release variable LISTusers
void deleteListUSER(LISTusers *lu)
{
    if (lu != NULL)
    if (lu->head != NULL)
    {
        while (lu->tail != NULL)
        {
            USER *p = lu->tail;
            lu->tail = p->prev;
            deleteUser(p);
        }
        lu->head = NULL;
        lu->tail = NULL;
    }
    else
    {
        lu->head = NULL;
        lu->tail = NULL;
    }
    delete lu;
}
//Create a variable USER with values given
USER *createUser(USER *user)
{
    USER *p = NULL;
    p = new USER;
    strcpy_s(p->username,   user->username);
    strcpy_s(p->password,   user->password);
    strcpy_s(p->ID,         user->ID);
    strcpy_s(p->address,    user->address);
    strcpy_s(p->email,      user->email);
    strcpy_s(p->name,       user->name);
    p->birthday.day     =   user->birthday.day;
    p->birthday.month   =   user->birthday.month;
    p->birthday.year    =   user->birthday.year;
    p->isAdmin          =   user->isAdmin;
    p->isFemale         =   user->isFemale;
    p->isManager        =   user->isManager;
    p->status           =   user->status;
    p->next             =   NULL;
    p->prev             =   NULL;
    return p;
}
//Add variable (node) USER to LISTusers
void addUSERtoLast(LISTusers *lu, USER *user)
{
    if (lu->head == NULL)
    {
        lu->head = user;
        lu->tail = user;
    }
    else
    {
        user->prev = lu->tail;
        (lu->tail)->next = user;
        lu->tail = user;
    }
}
//Import LISTusers from file users.dat
void readListUsers(LISTusers *lu)
{
    FILE *f;
    fopen_s(&f, "database\\users.dat", "rb");
    USER *temp = new USER;
    while (!feof(f))
    {
        freadUser(f, temp);
        if (!feof(f))
        {
            USER *user = NULL;
            user = createUser(temp);
            if (user != NULL)
            {
                addUSERtoLast(lu, user);
            }
        }
    }
    deleteUser(temp);
    fclose(f);
}
//export LISTusers to file users.dat
void writeListUsers(LISTusers *lu)
{
    FILE *f = NULL;
    fopen_s(&f, "database\\users.dat", "wb");
    USER *p = lu->head;
    while (p!= NULL)
    {
        fwriteUser(f, p);
        p = p->next;
    }
    fclose(f);
}
//Check if USER exists in LISTusers (by username)
//+ if exists USER in LISTusers, return  pointer location
//+ if not, return NULL
USER *isExistinListUsers(LISTusers *lu, USER *user)
{
    USER *p = lu->head;
    while (p != NULL)
    {
        if (_strcmpi(user->username, p->username)==0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//Reader Management functions

//Import a variable READER from file f
void freadReader(FILE *f, READER *p)
{
    fread_s(p, sizeof(READER), sizeof(READER), 1, f);
    p->next = NULL;
    p->prev = NULL;
}
//export a variable READER to file f
void fwriteReader(FILE *f, READER *p)
{
    fwrite(p, sizeof(READER), 1, f);
}
//Delete a READER
void deleteReader(READER *reader)
{
    if (reader != NULL)
    {
        reader->next = NULL;
        reader->prev = NULL;
        delete reader;
    }
}
//Create LISTreaders
LISTreaders *createListReader()
{
    LISTreaders *lr = new LISTreaders;
    lr->head = NULL;
    lr->tail = NULL;
    return lr;
}
//release LISTreaders
void deleteListREADER(LISTreaders *lr)
{
    if (lr != NULL)
        if (lr->head != NULL)
        {
            while (lr->tail != NULL)
            {
                READER *p = lr->tail;
                lr->tail = p->prev;
                deleteReader(p);
            }
            lr->head = NULL;
            lr->tail = NULL;
        }
        else
        {
            lr->head = NULL;
            lr->tail = NULL;
        }
    delete lr;
}
//create READER with values given
READER *createReader(READER *reader)
{
    READER *p = NULL;
    p = new READER;
    strcpy_s(p->readerCode,       reader->readerCode);
    strcpy_s(p->name,             reader->name);
    strcpy_s(p->ID,               reader->ID);
    strcpy_s(p->address,          reader->address);
    strcpy_s(p->email,            reader->email);
    p->birthday                  = reader->birthday;
    p->isFemale                  = reader->isFemale;
    p->creationDate              = reader->creationDate;
    p->expirationDate            = reader->expirationDate;
    p->next                      = NULL;
    p->prev                      = NULL;
    return p;
}
//add READER to LISTreaders
void addREADERtoLast(LISTreaders *lr, READER *reader)
{
    if (lr->head == NULL)
    {
        lr->head = reader;
        lr->tail = reader;
    }
    else
    {
        reader->prev = lr->tail;
        (lr->tail)->next = reader;
        lr->tail = reader;
    }
}
//Import LISTreaders from file readers.dat
void readListReaders(LISTreaders *lr)
{
    FILE *f;
    fopen_s(&f, "database\\readers.dat", "rb");
    READER *temp = new READER;
    while (!feof(f))
    {
        freadReader(f, temp);
        if (!feof(f))
        {
            READER *reader = NULL;
            reader = createReader(temp);
            if (reader != NULL)
            {
                addREADERtoLast(lr, reader);
            }
        }
    }
    deleteReader(temp);
    fclose(f);
}
//Import LISTreaders to file readers.dat
void writeListReaders(LISTreaders *lr)
{
    FILE *f = NULL;
    fopen_s(&f, "database\\readers.dat", "wb");
    READER *p = lr->head;
    while (p != NULL)
    {
        fwriteReader(f, p);
        p = p->next;
    }
    fclose(f);
}
//Check if READER with readerCode exists in LISTreaders?
//+ if READER exists, return pointer location
//+ if not, return NULL
READER *isExistinListReaders(LISTreaders *lr, char *readerCode)
{
    READER *p = lr->head;
    while (p != NULL)
    {
        if (_strcmpi(readerCode, p->readerCode) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
//delete a READER in LISTreaders
void deleteReaderinList(LISTreaders *lr, READER *p)
{
    if (p == lr->head)
    {
        if (lr->head == lr->tail)
        {
            lr->head = NULL;
            lr->tail = NULL;
        }
        else
        {
            lr->head = p->next;
            (lr->head)->prev = NULL;
        }
    }
    else if (p == lr->tail)
    {
        lr->tail = p->prev;
        (lr->tail)->next = NULL;
    }
    else
    {
        (p->prev)->next = p->next;
        (p->next)->prev = p->prev;
    }
    p->next = NULL;
    p->prev = NULL;
    deleteReader(p);
}
//
//Book Management functions
//

//import a variable BOOK from file f
void freadBook(FILE *f, BOOK *p)
{
    fread_s(p, sizeof(BOOK), sizeof(BOOK), 1, f);
    p->next = NULL;
    p->prev = NULL;
}
//export a variable BOOK to file f
void fwriteBook(FILE *f, BOOK *p)
{
    fwrite(p, sizeof(BOOK), 1, f);
}
//delete a BOOK
void deleteBook(BOOK *book)
{
    if (book != NULL)
    {
        book->next = NULL;
        book->prev = NULL;
        delete book;
    }
}
//create LISTbooks
LISTbooks *createListBook()
{
    LISTbooks *lb = new LISTbooks;
    lb->head = NULL;
    lb->tail = NULL;
    return lb;
}
//release LISTbooks
void deleteListBOOK(LISTbooks *lb)
{
    if (lb != NULL)
        if (lb->head != NULL)
        {
            while (lb->tail != NULL)
            {
                BOOK *p = lb->tail;
                lb->tail = p->prev;
                deleteBook(p);
            }
            lb->head = NULL;
            lb->tail = NULL;
        }
        else
        {
            lb->head = NULL;
            lb->tail = NULL;
        }
    delete lb;
}
//create BOOK with given values
BOOK *createBook(BOOK *book)
{
    BOOK *p = NULL;
    p = new BOOK;
    strcpy_s(p->ISBN, book->ISBN);
    strcpy_s(p->name, book->name);
    strcpy_s(p->author, book->author);
    strcpy_s(p->publisher, book->publisher);
    strcpy_s(p->category, book->category);
    p->publishYear = book->publishYear;
    p->price = book->price;
    p->number = book->number;
    p->available = book->available;
    p->next = NULL;
    p->prev = NULL;
    return p;
}
//add BOOK to LISTbooks
void addBOOKtoLast(LISTbooks *lb, BOOK *book)
{
    if (lb->head == NULL)
    {
        lb->head = book;
        lb->tail = book;
    }
    else
    {
        book->prev = lb->tail;
        (lb->tail)->next = book;
        lb->tail = book;
    }
}
//import LISTbooks from file books.dat
void readListBooks(LISTbooks *lb)
{
    FILE *f;
    fopen_s(&f, "database\\books.dat", "rb");
    BOOK *temp = new BOOK;
    while (!feof(f))
    {
        freadBook(f, temp);
        if (!feof(f))
        {
            BOOK *book = NULL;
            book = createBook(temp);
            if (book != NULL)
            {
                addBOOKtoLast(lb, book);
            }
        }
    }
    deleteBook(temp);
    fclose(f);
}
//export LISTbooks to file books.dat
void writeListBooks(LISTbooks *lb)
{
    FILE *f = NULL;
    fopen_s(&f, "database\\books.dat", "wb");
    BOOK *p = lb->head;
    while (p != NULL)
    {
        fwriteBook(f, p);
        p = p->next;
    }
    fclose(f);
}
//check if ISBN exists in LISTbooks
//+ if BOOK exists, return pointer
//+ if not, return NULL
BOOK *isExistinListBooks(LISTbooks *lb, char *ISBN)
{
    BOOK *p = lb->head;
    while (p != NULL)
    {
        if (_strcmpi(ISBN, p->ISBN) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
//delete a BOOK from LISTbooks
void deleteBookinList(LISTbooks *lb, BOOK *p)
{
    if (p == lb->head)
    {
        if (lb->head == lb->tail)
        {
            lb->head = NULL;
            lb->tail = NULL;
        }
        else
        {
            lb->head = p->next;
            (lb->head)->prev = NULL;
        }
    }
    else if (p == lb->tail)
    {
        lb->tail = p->prev;
        (lb->tail)->next = NULL;
    }
    else
    {
        (p->prev)->next = p->next;
        (p->next)->prev = p->prev;
    }
    p->next = NULL;
    p->prev = NULL;
    deleteBook(p);
}

//
//Borrow Bill Management functions
//

//import a variable BBILL from file f
void freadBBill(FILE *f, BBILL *p)
{
    fread_s(p->billCode, sizeof(char) * 10, sizeof(char) * 10, 1, f);
    fread_s(p->readerCode, sizeof(char) * 10, sizeof(char) * 10, 1, f);
    fread_s(p->ID, sizeof(char) * 10, sizeof(char) * 10, 1, f);
    fread_s(p->name, sizeof(char) * 40, sizeof(char) * 40, 1, f);
    fread_s(&(p->borrowDate), sizeof(DATE), sizeof(DATE), 1, f);
    fread_s(&(p->expectedReturnDate), sizeof(DATE), sizeof(DATE), 1, f);
    p->numberofBooks = 0;
    fread_s(&(p->numberofBooks), sizeof(unsigned int), sizeof(unsigned int), 1, f);
    if (p->numberofBooks > 0)
    {
        (p->list) = new borrowedBooks[p->numberofBooks];
        for (unsigned int i = 0; i < p->numberofBooks; i++)
        {
            fread_s((p->list) + i, sizeof(borrowedBooks), sizeof(borrowedBooks), 1, f);
        }
    }
    else
        (p->list) = new borrowedBooks[1];
    p->next = NULL;
    p->prev = NULL;
}
//export a variable BBILL to file f
void fwriteBBill(FILE *f, BBILL *p)
{
    fwrite(p->billCode, sizeof(char), 10, f);
    fwrite(p->readerCode, sizeof(char), 10, f);
    fwrite(p->ID, sizeof(char), 10, f);
    fwrite(p->name, sizeof(char), 40, f);
    fwrite(&(p->borrowDate), sizeof(DATE), 1, f);
    fwrite(&(p->expectedReturnDate), sizeof(DATE), 1, f);
    fwrite(&(p->numberofBooks), sizeof(unsigned int), 1, f);
    for (unsigned int i = 0; i < p->numberofBooks; i++)
    {
        fwrite((p->list) + i, sizeof(borrowedBooks), 1, f);
    }
}
//delete BBILL
void deleteBBill(BBILL *bbill)
{
    if (bbill != NULL)
    {
        delete[](bbill->list);
        bbill->next = NULL;
        bbill->prev = NULL;
        delete bbill;
    }
}
//create LISTbbills
LISTbbills *createListBBill()
{
    LISTbbills *lbbill = new LISTbbills;
    lbbill->head = NULL;
    lbbill->tail = NULL;
    return lbbill;
}
//release LISTbbills
void deleteListBBILL(LISTbbills *lbbill)
{
    if (lbbill != NULL)
        if (lbbill->head != NULL)
        {
            while (lbbill->tail != NULL)
            {
                BBILL *p = lbbill->tail;
                lbbill->tail = p->prev;
                deleteBBill(p);
            }
            lbbill->head = NULL;
            lbbill->tail = NULL;
        }
        else
        {
            lbbill->head = NULL;
            lbbill->tail = NULL;
        }
    delete lbbill;
}
//create BBILL with given variable
BBILL *createBBill(BBILL *bbill)
{
    BBILL *p = NULL;
    p = new BBILL;
    strcpy_s(p->billCode, bbill->billCode);
    strcpy_s(p->readerCode, bbill->readerCode);
    strcpy_s(p->ID, bbill->ID);
    strcpy_s(p->name, bbill->name);
    p->borrowDate = bbill->borrowDate;
    p->expectedReturnDate = bbill->expectedReturnDate;
    p->numberofBooks = bbill->numberofBooks;
    (p->list) = new borrowedBooks[p->numberofBooks];
    for (unsigned int i = 0; i < p->numberofBooks; i++)
    {
        strcpy_s(((p->list) + i)->ISBN, ((bbill->list) + i)->ISBN);
        ((p->list) + i)->price = ((bbill->list) + i)->price;
    }
    p->next = NULL;
    p->prev = NULL;
    return p;
}
//add BBILL to the last of LISTbbills
void addBBILLtoLast(LISTbbills *lbbill, BBILL *bbill)
{
    if (lbbill->head == NULL)
    {
        lbbill->head = bbill;
        lbbill->tail = bbill;
    }
    else
    {
        bbill->prev = lbbill->tail;
        (lbbill->tail)->next = bbill;
        lbbill->tail = bbill;
    }
}
//import LISTbbills from file bbills.dat
void readListBBills(LISTbbills *lbbill)
{
    FILE *f;
    fopen_s(&f, "database\\bbills.dat", "rb");
    BBILL *temp = new BBILL;
    while (!feof(f))
    {
        freadBBill(f, temp);
        if (!feof(f))
        {
            BBILL *bbill = NULL;
            bbill = createBBill(temp);
            if (bbill != NULL)
            {
                addBBILLtoLast(lbbill, bbill);
                delete[](temp->list);
            }
        }
    }
    deleteBBill(temp);
    fclose(f);
    //delete f;
}
//export LISTbbills to file bbills.dat
void writeListBBills(LISTbbills *lbbill)
{
    FILE *f = NULL;
    fopen_s(&f, "database\\bbills.dat", "wb");
    BBILL *p = lbbill->head;
    while (p != NULL)
    {
        fwriteBBill(f, p);
        p = p->next;
    }
    fclose(f);
}
//check if BBILL with billcode exists in LISTbbills
//+ if BBILL exists, return pointer
//+ if not, return NULL
BBILL *isExistinListBBills(LISTbbills *lbbill, char *billCode)
{
    BBILL *p = lbbill->tail;
    while (p != NULL)
    {
        if (_strcmpi(billCode, p->billCode) == 0)
        {
            return p;
        }
        p = p->prev;
    }
    return NULL;
}

//
//Return Bill Management functions
//

//import a variable RBILL from file f
void freadRBill(FILE *f, RBILL *p)
{
    fread_s(p->billCode, sizeof(char) * 10, sizeof(char) * 10, 1, f);
    fread_s(&(p->returnDate), sizeof(DATE), sizeof(DATE), 1, f);
    p->fineMoney = 0;
    fread_s(&(p->fineMoney), sizeof(unsigned int), sizeof(unsigned int), 1, f);
    p->numberofBooks = 0;
    fread_s(&(p->numberofBooks), sizeof(unsigned int), sizeof(unsigned int), 1, f);
    if (p->numberofBooks > 0)
    {
        (p->list) = new borrowedBooks[p->numberofBooks];
        for (unsigned int i = 0; i < p->numberofBooks; i++)
        {
            fread_s((p->list) + i, sizeof(borrowedBooks), sizeof(borrowedBooks), 1, f);
        }
    }
    else
        (p->list) = new borrowedBooks[1];
    p->next = NULL;
    p->prev = NULL;
}
//export a variable RBILL to file f
void fwriteRBill(FILE *f, RBILL *p)
{
    fwrite(p->billCode, sizeof(char), 10, f);
    fwrite(&(p->returnDate), sizeof(DATE), 1, f);
    fwrite(&(p->fineMoney), sizeof(unsigned int), 1, f);
    fwrite(&(p->numberofBooks), sizeof(unsigned int), 1, f);
    for (unsigned int i = 0; i < p->numberofBooks; i++)
    {
        fwrite((p->list) + i, sizeof(borrowedBooks), 1, f);
    }
}
//delete a RBILL
void deleteRBill(RBILL *rbill)
{
    if (rbill != NULL)
    {
        delete[](rbill->list);
        rbill->next = NULL;
        rbill->prev = NULL;
        delete rbill;
    }
}
//create LISTrbills
LISTrbills *createListRBill()
{
    LISTrbills *lrbill = new LISTrbills;
    lrbill->head = NULL;
    lrbill->tail = NULL;
    return lrbill;
}
//release LISTrbills
void deleteListRBILL(LISTrbills *lrbill)
{
    if (lrbill != NULL)
        if (lrbill->head != NULL)
        {
            while (lrbill->tail != NULL)
            {
                RBILL *p = lrbill->tail;
                lrbill->tail = p->prev;
                deleteRBill(p);
            }
            lrbill->head = NULL;
            lrbill->tail = NULL;
        }
        else
        {
            lrbill->head = NULL;
            lrbill->tail = NULL;
        }
    delete lrbill;
}
//create RBILL with given values
RBILL *createRBill(RBILL *rbill)
{
    RBILL *p = NULL;
    p = new RBILL;
    strcpy_s(p->billCode, rbill->billCode);
    p->returnDate = rbill->returnDate;
    p->fineMoney = rbill->fineMoney;
    p->numberofBooks = rbill->numberofBooks;
    (p->list) = new borrowedBooks[p->numberofBooks];
    for (unsigned int i = 0; i < p->numberofBooks; i++)
    {
        strcpy_s(((p->list) + i)->ISBN, ((rbill->list) + i)->ISBN);
        ((p->list) + i)->price = ((rbill->list) + i)->price;
    }
    p->next = NULL;
    p->prev = NULL;
    return p;
}
//add RBILL to LISTrbills
void addRBILLtoLast(LISTrbills *lrbill, RBILL *rbill)
{
    if (lrbill->head == NULL)
    {
        lrbill->head = rbill;
        lrbill->tail = rbill;
    }
    else
    {
        rbill->prev = lrbill->tail;
        (lrbill->tail)->next = rbill;
        lrbill->tail = rbill;
    }
}
//import LISTrbills from file rbills.dat
void readListRBills(LISTrbills *lrbill)
{
    FILE *f;
    fopen_s(&f, "database\\rbills.dat", "rb");
    RBILL *temp = new RBILL;
    while (!feof(f))
    {
        freadRBill(f, temp);
        if (!feof(f))
        {
            RBILL *rbill = NULL;
            rbill = createRBill(temp);
            if (rbill != NULL)
            {
                addRBILLtoLast(lrbill, rbill);
                delete[](temp->list);
            }
        }
    }
    deleteRBill(temp);
    fclose(f);
    //delete f;
}
//export LISTrbills to file rbills.dat
void writeListRBills(LISTrbills *lrbill)
{
    FILE *f = NULL;
    fopen_s(&f, "database\\rbills.dat", "wb");
    RBILL *p = lrbill->head;
    while (p != NULL)
    {
        fwriteRBill(f, p);
        p = p->next;
    }
    fclose(f);
}
//check if RBILL with billcode exists in LISTrbills
//+ if RBILL exists, return pointer
//+ if not, return NULL
RBILL *isExistinListRBills(LISTrbills *lrbill, char *billCode)
{
    RBILL *p = lrbill->tail;
    while (p != NULL)
    {
        if (_strcmpi(billCode, p->billCode) == 0)
        {
            return p;
        }
        p = p->prev;
    }
    return NULL;
}

//
//Statistics
//

//create Statistics
Statistics *createStatistics()
{
    Statistics *st = new Statistics;
    st->books.borrowedBooks = 0;
    st->books.numberOfCategories = 0;
    st->books.total = 0;
    st->readers.femaleReaders = 0;
    st->readers.maleReaders = 0;
    return st;
}
//create BookCategories with given values
BookCategories *createNewCategory(char *category, unsigned int number)
{
    BookCategories *p = new BookCategories;
    strcpy_s(p->name, category);
    p->number = number;
    p->next = NULL;
    return p;
}
//add a BookCategories (category) to list BookCategories (head)
void pushCategories(BookCategories *&head, BookCategories *category)
{
    if (head == NULL)
        head = category;
    else
    {
        category->next = head;
        head = category;
    }
}
//import Statistics to file statistics.dat
void readStatistics(Statistics *st)
{
    FILE *f = NULL;
    fopen_s(&f, "database\\statistics.dat", "rb");
    if (f != NULL)
    {
        fread_s(&(st->books.total), sizeof(unsigned int), sizeof(unsigned int), 1, f);
        fread_s(&(st->books.borrowedBooks), sizeof(unsigned int), sizeof(unsigned int), 1, f);
        fread_s(&(st->books.numberOfCategories), sizeof(unsigned int), sizeof(unsigned int), 1, f);
        st->books.categories = NULL;
        for (unsigned int i = 0; i < st->books.numberOfCategories; i++)
        {
            BookCategories *p = new BookCategories;
            fread_s(p, sizeof(BookCategories), sizeof(BookCategories), 1, f);
            p->next = NULL;
            pushCategories(st->books.categories, p);
        }
        fread_s(&(st->readers.maleReaders), sizeof(unsigned int), sizeof(unsigned int), 1, f);
        fread_s(&(st->readers.femaleReaders), sizeof(unsigned int), sizeof(unsigned int), 1, f);
        fclose(f);
    }
    else
        printf("Can't open file!\n");
}
//export Statitics to file statistics.dat
void writeStatistics(Statistics *st)
{
    FILE *f = NULL;
    fopen_s(&f, "database\\statistics.dat", "wb");
    if (f != NULL)
    {
        fwrite(&(st->books.total), sizeof(unsigned int), 1, f);
        fwrite(&(st->books.borrowedBooks), sizeof(unsigned int), 1, f);
        fwrite(&(st->books.numberOfCategories), sizeof(unsigned int), 1, f);
        BookCategories *p = st->books.categories;
        for (unsigned int i = 0; i < st->books.numberOfCategories; i++)
        {
            fwrite(p, sizeof(BookCategories), 1, f);
            p = p->next;
        }
        fwrite(&(st->readers.maleReaders), sizeof(unsigned int), 1, f);
        fwrite(&(st->readers.femaleReaders), sizeof(unsigned int), 1, f);
        fclose(f);
    }
    else
        printf("Can't open file!\n");
}
//release BookCategories
void deleteListCategory(BookCategories *&head)
{
    BookCategories *p = head;
    while (p != NULL)
    {
        BookCategories *temp = p;
        p = p->next;
        delete temp;
    }
}
//check if category exists in BookCategories
//+ if BookCategories (category) exists, return pointer
//+ if not, return NULL
BookCategories *categoryLocation(BookStatistics b,char *category)
{
    BookCategories *p = b.categories;
    for (unsigned int i = 0; i < b.numberOfCategories; i++)
    {
        if (_strcmpi(p->name, category) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}
//release Statistics
void deleteStatistics(Statistics *st)
{
    deleteListCategory(st->books.categories);
    delete st;
}