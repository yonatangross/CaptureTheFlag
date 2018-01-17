#include "FileUtils.h"



void getFilesList(std::string filePath, std::string extension,std::vector <std:: string> & returnFileName)
{
	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	std::string  fullPath = filePath + extension;
	hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE) {
		returnFileName.push_back(filePath + fileInfo.cFileName);
		while (FindNextFile(hFind, &fileInfo) != 0) {
			returnFileName.push_back(filePath + fileInfo.cFileName);
		}
	}
}


bool exists_test0(const std::string& name) {
	


	return (_access(name.c_str(), 0) == 0);
	/*	? true : false;
	return f.good();*/
}

string findNextRandom(string path)
{
	int init = 0; 
	string name; 
	vector<string> s;
	getFilesList(path   , "random_*.gboard", s);
	std::sort(s.begin(), s.end());
	for each ( string str in s)
	{
		
			name = path + "random_" + to_string(init) + ".gboard";
			if (str != name)
				return "random_" + to_string(init);
			init++;
		
		
	}
	return name = "random_" + to_string(init);
	
}



