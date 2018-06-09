DATE getExpirationDate(DATE creationDate);
void exportReader(READER *p);
void exportReaderList(LISTreaders *lr);
void searchReaderID(LISTreaders *lr);
void searchReaderName(LISTreaders *lr);

//
//Improve functions vesion 1.0 (12/04/2018)
//


void updateReaderInfomationV1(LISTreaders *lr, Statistics *st);
void addReadertoDatabaseV1(LISTreaders *lr, Statistics *st);
void deleteReaderFromDatabaseV1(LISTreaders *lr, Statistics *st);
void renewReader(LISTreaders *lr);