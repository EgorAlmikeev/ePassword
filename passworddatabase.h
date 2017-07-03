#ifndef PASSWORDDATABASE_H
#define PASSWORDDATABASE_H

#include <QMultiMap>
#include <QString>
#include <QFile>
#include <time.h>
//#include "encryptor.h"

class PasswordDataBase
{
protected :

    QMultiMap<QString, QString> element_multi_map;
    QFile data_file;
//    Encryptor encr;
    QMultiMap<QString, QString>::iterator iter;
    char *password_simbols = nullptr;

    //password simbols generation functions
    void setPasswordSimbolsDigits();
    void setPasswordSimbolsLetters();
    void setPasswordSimbolsSpecials();
    void setPasswordSimbolsDigitsLetters();
    void setPasswordSimbolsDigitsSpecials();
    void setPasswordSimbolsLettersSpecials();
    void setPasswordSimbolsDigitsLettersSpecials();
    //end of password simbols generation functions

    void readToMap();
    void writeFromMap();

    void showMap();
    void showMenu();

    void addElement();
    void showElement();
    void editElement();
    void removeElement();

    void wipeDataFile();

    std::string generatePassword();

    void encryptDataFile();
    void decryptDataFile();

    int getSwitchChoice(int min, int max);

public :

    void start();
    void finish();

    PasswordDataBase();
    ~PasswordDataBase();
};

#endif // PASSWORDDATABASE_H
