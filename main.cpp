#include <iostream>
#include "passworddatabase.h"

using namespace std;

int main(int argc, char *argv[])
{

    PasswordDataBase pdb;

    pdb.start();    //проблема переворачивания значений
    pdb.finish();

    return 0;
}
