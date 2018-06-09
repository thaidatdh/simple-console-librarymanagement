
struct DATE {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

struct USER {
    char username[20];
    char password[20];
    char name[40];
    DATE birthday;
    char ID[10];
    char address[100];
    bool isFemale;
    char email[35];
    //status: 1. activated; 0. blocked
    bool status;
    //is admin? (true = admin, false = not)
    bool isAdmin;
    //is manager (true = manager, false = staff)
    bool isManager;
    USER *next;
    USER *prev;
};
struct READER {
    char address[100];
    char name[40];
    char email[35];
    char readerCode[10];
    char ID[10];
    DATE birthday;
    DATE creationDate;
    DATE expirationDate;
    bool isFemale;
    READER *next;
    READER *prev;
};
struct BOOK {
    char name[100];
    char author[100];
    char publisher[60];
    char category[30];
    char ISBN[10];
    unsigned int publishYear;
    unsigned int price;
    unsigned int number;
    unsigned int available;
    BOOK *next;
    BOOK *prev;
};
struct borrowedBooks {
    char ISBN[10];
    unsigned int price;
};
struct BBILL {
    char billCode[10];
    char readerCode[10];
    char ID[10];
    char name[40];
    DATE borrowDate;
    DATE expectedReturnDate;
    unsigned int numberofBooks;
    borrowedBooks *list;
    BBILL *next;
    BBILL *prev;
};
struct RBILL {
    char billCode[10];
    unsigned int fineMoney;
    unsigned int numberofBooks;
    DATE returnDate;
    borrowedBooks *list;
    RBILL *next;
    RBILL *prev;
};
struct LISTusers {
    USER *head;
    USER *tail;
};
struct LISTreaders {
    READER *head;
    READER *tail;
};
struct LISTbooks {
    BOOK *head;
    BOOK *tail;
};
struct LISTbbills {
    BBILL *head;
    BBILL *tail;
};
struct LISTrbills {
    RBILL *head;
    RBILL *tail;
};
struct BookCategories {
    char name[30];
    unsigned int number;
    BookCategories *next;
};
struct BookStatistics {
    unsigned int total;
    unsigned int borrowedBooks;
    unsigned int numberOfCategories;
    BookCategories *categories;
};
struct ReaderStatistics {
    unsigned int maleReaders;
    unsigned int femaleReaders;
};
struct Statistics {
    BookStatistics books;
    ReaderStatistics readers;
};
int dayBetween(DATE expectDate, DATE returnDate);
void importDate(DATE &d);
DATE getCurrentDate();
bool importGender();
bool leapYear(unsigned int year);
unsigned int maxDay(unsigned int month, unsigned int year);

//
//User Management functions
//

void freadUser(FILE *f, USER *p);
void fwriteUser(FILE *f, USER *p);
void deleteUser(USER *user);
LISTusers *createList();
void deleteListUSER(LISTusers *lu);
USER *createUser(USER *user);
void addUSERtoLast(LISTusers *lu, USER *user);
void readListUsers(LISTusers *lu);
void writeListUsers(LISTusers *lu);
USER *isExistinListUsers(LISTusers *lu, USER *user);

//
//Reader Management functions
//

void freadReader(FILE *f, READER *p);
void fwriteReader(FILE *f, READER *p);
void deleteReader(READER *reader);
LISTreaders *createListReader();
void deleteListREADER(LISTreaders *lr);
READER *createReader(READER *reader);
void addREADERtoLast(LISTreaders *lr, READER *reader);
void readListReaders(LISTreaders *lr);
void writeListReaders(LISTreaders *lr);
READER *isExistinListReaders(LISTreaders *lr, char *readerCode);
void deleteReaderinList(LISTreaders *lr, READER *p);

//
//Book Management functions
//

void freadBook(FILE *f, BOOK *p);
void fwriteBook(FILE *f, BOOK *p);
void deleteBook(BOOK *book);
LISTbooks *createListBook();
void deleteListBOOK(LISTbooks *lb);
BOOK *createBook(BOOK *book);
void addBOOKtoLast(LISTbooks *lb, BOOK *book);
void readListBooks(LISTbooks *lb);
void writeListBooks(LISTbooks *lb);
BOOK *isExistinListBooks(LISTbooks *lb, char *ISBN);
void deleteBookinList(LISTbooks *lb, BOOK *p);

//
//Borrow Bill Management functions
//

void freadBBill(FILE *f, BBILL *p);
void fwriteBBill(FILE *f, BBILL *p);
void deleteBBill(BBILL *bbill);
LISTbbills *createListBBill();
void deleteListBBILL(LISTbbills *lbbill);
BBILL *createBBill(BBILL *bbill);
void addBBILLtoLast(LISTbbills *lbbill, BBILL *bill);
void readListBBills(LISTbbills *lbbill);
void writeListBBills(LISTbbills *lbbill);
BBILL *isExistinListBBills(LISTbbills *lbbill, char *billCode);

//
//Return Bill Management functions
//

void freadRBill(FILE *f, RBILL *p);
void fwriteRBill(FILE *f, RBILL *p);
void deleteRBill(RBILL *rbill);
LISTrbills *createListRBill();
void deleteListRBILL(LISTrbills *lrbill);
RBILL *createRBill(RBILL *rbill);
void addRBILLtoLast(LISTrbills *lrbill, RBILL *bill);
void readListRBills(LISTrbills *lrbill);
void writeListRBills(LISTrbills *lrbill);
RBILL *isExistinListRBills(LISTrbills *lrbill, char *billCode);

//
//Statitics
//

Statistics *createStatistics();
BookCategories *createNewCategory(char *category, unsigned int number);
void pushCategories(BookCategories *&head, BookCategories *category);
void readStatistics(Statistics *st);
void writeStatistics(Statistics *st);
BookCategories *categoryLocation(BookStatistics b, char *category);
void deleteListCategory(BookCategories *&head);
void deleteStatistics(Statistics *st);