#ifndef FILE_HANDLING_H_
#define FILE_HANDLING_H_

// include C libraries for filesystem access
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// include C++ standard libraries
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <stdint.h>

using namespace std;

void createDirectory(string fullpath)
{

    char directory[fullpath.size() + 1];
    strcpy(directory, fullpath.c_str());

    struct stat st = {0};

    if (stat(directory, &st) == -1)
    {
        mkdir(directory, 0700);
    }
}

string convertFileIDToString(uint _n, uint _decimals)
{
    stringstream result;
    result << std::setfill('0') << std::setw(_decimals) << _n;
    return result.str();
}

int findDecimals(int _n)
{
    int count = 1;
    int result = _n / 10;

    while (result > 0)
    {
        count++;
        result = result / 10;
    }

    return count;
}

#endif