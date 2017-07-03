#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include<QString>
#include<QFile>
#include<iostream>

class Encryptor
{
protected :

    int key;
    QFile file;
    QString file_data;
    QString flag_word;

    void encryptFileData();
    void decryptFileData();

    void tryToOpenFile();
    int readKey();

public :

    class EncryptorException
    {
        std::string msg;

    public :

        explicit EncryptorException(std::string);
        ~EncryptorException();

        void errmsg();
    };

    bool isFileDataEncrypted();

    void setFileName(QString);
    void setFlag(QString);

    void encryptFileProcess();
    void decryptFileProcess();

    void writeKey(int _key);

    Encryptor();
    ~Encryptor();
};

#endif // ENCRYPTOR_H
