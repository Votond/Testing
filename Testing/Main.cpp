#include "Includes.h"
#include "SystemManager.cpp"

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");

    SystemManager::getInstance().start();

    return 0;
}