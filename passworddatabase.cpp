#include "passworddatabase.h"
#include "encryptor.h"

PasswordDataBase::PasswordDataBase()
{
    data_file.setFileName("./saves.txt");

    encr.setFileName(data_file.fileName());
    encr.setFlag("encrypted");

    iter = element_multi_map.begin();
}

PasswordDataBase::~PasswordDataBase()
{}

void PasswordDataBase::start()
{
    system("clear");

    decryptDataFile();
    readToMap();
    showMap();
    showMenu();
}

void PasswordDataBase::finish()
{
    writeFromMap();
    encryptDataFile();
    exit(0);
}

void PasswordDataBase::decryptDataFile()
{
//    if(encr.isFileDataEncrypted())
//        encr.decryptFileProcess();
}

void PasswordDataBase::encryptDataFile()
{
//    if(!encr.isFileDataEncrypted())
//        encr.encryptFileProcess();
}

void PasswordDataBase::readToMap()
{
    if(!data_file.isOpen())
        data_file.open(QIODevice::ReadOnly);

    while(!data_file.atEnd())
    {
        QString temp_key = data_file.readLine();

        element_multi_map.insertMulti(temp_key, data_file.readLine());
        element_multi_map.insertMulti(temp_key, data_file.readLine());
        element_multi_map.insertMulti(temp_key, data_file.readLine());
    }

    data_file.close();
}

void PasswordDataBase::writeFromMap()
{
    if(!data_file.isOpen())
        data_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Unbuffered);

    QByteArray buff;
    QString last_key = NULL;

    for(iter = element_multi_map.begin(); iter != element_multi_map.end(); ++iter, buff.clear())
    {
        if(iter.key() != last_key)
        {
            last_key = iter.key();
            buff.append(last_key);
            data_file.write(buff);
            buff.clear();
        }

        buff.clear();
        buff.append(iter.value());
        data_file.write(buff);
    }
}

void PasswordDataBase::showMap()
{}
void PasswordDataBase::showMenu()
{}

void PasswordDataBase::addElement()
{}
void PasswordDataBase::showElement()
{}
void PasswordDataBase::editElement()
{}
void PasswordDataBase::removeElement()
{}

void PasswordDataBase::generatePassword()
{}

int PasswordDataBase::getInt()
{}
