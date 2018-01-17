#pragma once



#include <Windows.h>
#include <conio.h>

#include <algorithm>
#include <string>
#include <vector>
#include <io.h>
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;

// bool exists_test0(const std::string& name);
void getFilesList(std::string filePath, std::string extension, std::vector <std::string> & returnFileName);
string findNextRandom(string path);

