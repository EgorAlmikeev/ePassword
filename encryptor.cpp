#include<encryptor.h>
#include<QFile>
#include<iostream>

using namespace std;

Encryptor::EncryptorException::EncryptorException(std::string _msg) : msg(_msg)
{}

Encryptor::EncryptorException::~EncryptorException()
{}

void Encryptor::EncryptorException::errmsg()
{
    std::cerr << "\n#error [ENCRYPTOR] : " << msg << std::endl;
    exit(1);
}


void Encryptor::setFileName(QString _name)
{
    file.setFileName(_name);
}

void Encryptor::setFlag(QString _flag)
{
    flag_word = _flag;
}

bool Encryptor::isFileDataEncrypted()
{    
    if(file_data.toStdString().find(flag_word.toStdString()) == 0)
        return true;
    return false;
}

void Encryptor::tryToOpenFile()
{
    std::clog << "\ntrying to open " << file.fileName().toStdString() << "...";
    if(QFile::exists(file.fileName()))
    {
        if(!file.isOpen())
            if(!file.open(QIODevice::ReadWrite | QIODevice::Unbuffered))
                throw Encryptor::EncryptorException("can not open file...");
            else std::clog << "done";
    }
    else throw Encryptor::EncryptorException("file does not exist...");
}

void Encryptor::encryptFileProcess()
{
    std::clog << "\nchecking for key...";
    if(readKey() == 1)
        return;
    std::clog << "done";

    tryToOpenFile();

    //reading data
    std::clog << "\nreading file data...";
    char data_block[1024];
    string temp_data;

    file_data.clear();

    while(!file.atEnd())
    {
        int block_size = file.read(data_block, sizeof(data_block));
        temp_data = data_block;
        file_data.append(QString::fromStdString(temp_data));
    }

    std::clog << "done";
    //end of reading

    EncryptFileData();

    file.close();
    file.open(QIODevice::ReadWrite | QIODevice::Unbuffered | QIODevice::Truncate);

    QByteArray buff;
    buff.append(file_data);

    file.write(buff);
    file.close();
}

void Encryptor::decryptFileProcess()
{
    std::clog << "\nchecking for key...";
    if(readKey() == 1)
        return;
    std::clog << "done";

    tryToOpenFile();

    //reading data
    std::clog << "\nreading file data...";
    char data_block[1024];
    string temp_data;

    file_data.clear();

    while(!file.atEnd())
    {
        int block_size = file.read(data_block, sizeof(data_block));
        temp_data = data_block;
        file_data.append(QString::fromStdString(temp_data));
    }

    std::clog << "done";
    //end of reading data

    DecryptFileData();

    file.close();
    file.open(QIODevice::ReadWrite | QIODevice::Unbuffered | QIODevice::Truncate);

    QByteArray buff;
    buff.append(file_data);

    file.write(buff);
    file.close();
}

void Encryptor::EncryptFileData()
{
    std::clog << "\nencrypting file...";

    if(isFileDataEncrypted())
    {
        std::clog << "\n#error [ENCRYPTOR] : already encrypted...";
        std::clog << "\nare you sure you wanna encrypt it again?(y/n) : ";
        char choice;
        choice = getchar();
        if(choice != 'y')
            return;
    }

    //magic
    QString temp_data;

    for(int i = 0, ascii_code = 0; i < file_data.length(); ++i)
    {
        ascii_code = file_data.toStdString().at(i);
        ascii_code *= key;
        temp_data += QString::number(ascii_code);
        temp_data += " ";
    }

    file_data.clear();
    file_data = temp_data;
    //magic end

    file_data.prepend(flag_word + " ");
    std::clog << "done";
}

void Encryptor::DecryptFileData()
{
    std::clog << "\ndecrypting file...";

    if(!isFileDataEncrypted())
    {
        std::clog << "\n#error [ENCRYPTOR] : this file is not encrypted with this program,\ncannot decrypt it...";
        return;
    }

    file_data.remove(0, flag_word.size() + 1);

    //magic
    QString temp_data;
    QString temp_code;

    for(int i = 0, ascii_code = 0; i < file_data.length(); ++i, temp_code.clear())
    {
        while(file_data.at(i) != ' ')
            temp_code += file_data.at(i++);
        ascii_code = temp_code.toInt();
        ascii_code /= key;
        temp_data += ascii_code;
    }

    file_data.clear();
    file_data = temp_data;
    //magic end

    std::clog << "done";
}

void Encryptor::writeKey(int _key)
{
    QByteArray buff;
    buff.append(QString::number(_key));

    QFile key_file("./config");
    key_file.open(QIODevice::WriteOnly | QIODevice::Unbuffered);
    key_file.write(buff);
    key_file.close();
}

int Encryptor::readKey()
{
    QFile key_file("./config");
    if(!key_file.exists())
    {
        std::clog << "config file does not exists : run eEncryptor --makeconfig\n";
        return 1;
    }
    key_file.open(QIODevice::ReadOnly | QIODevice::Unbuffered);
    QString temp = key_file.readAll();
    key = temp.toInt();
    key_file.close();
    return 0;
}

Encryptor::Encryptor()
{}

Encryptor::~Encryptor()
{}
