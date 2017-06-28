#ifndef PASSWORDDATABASE_H
#define PASSWORDDATABASE_H

#include "encryptor.h"
#include <QMultiMap>
#include <QString>
#include <QFile>

class PasswordDataBase
{
protected :

    QMultiMap<QString, QString> element_multi_map;
    QFile data_file;
    Encryptor encr;
    QMultiMap<QString, QString>::iterator iter;

    void readToMap();
    void writeFromMap();

    void showMap();
    void showMenu();

    void addElement();
    void showElement();
    void editElement();
    void removeElement();

    void generatePassword();

    void encryptDataFile();
    void decryptDataFile();

    int getInt();

public :

    void start();
    void finish();

    PasswordDataBase();
    ~PasswordDataBase();
};

#endif // PASSWORDDATABASE_H
