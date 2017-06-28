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

    void EncryptFileData();
    void DecryptFileData();

public :

    class EncryptorException
    {
        std::string msg;

    public :

        explicit EncryptorException(std::string);
        ~EncryptorException();

        void errmsg();
    };

    void setFileName(QString);
    void setFlag(QString);

    void tryToOpenFile();

    void encryptFileProcess();
    void decryptFileProcess();

    void writeKey(int _key);
    int readKey();

    bool isFileDataEncrypted();

    Encryptor();
    ~Encryptor();
};

#endif // ENCRYPTOR_H
