#include "FileHandler.h"


void  FileHandler::getInputFiles()
{

	getFilesList(path, "*." + EndWith, Inputfiles);
	std::sort(Inputfiles.begin(), Inputfiles.end());
}

int FileHandler::getNumOfInputFiles()
{
	return Inputfiles.size();
}
void  FileHandler::openInputFile()
{
	inputFileName = Inputfiles.front();
	inputFile.open(inputFileName);
	Inputfiles.erase(Inputfiles.begin());
}

bool  FileHandler::openInputFile(string fileName)
{
	
	inputFile.open(path+fileName+"."+EndWith , ios::in);
	endOfFile = false;
	return inputFile.good();
	
}

string FileHandler::readLine()
{
	string line;

	getline(inputFile, line);
	return line;
}

string FileHandler::getInputFileName()
{
	int stringSize = inputFileName.size() - path.size() - EndWith.size()-1;
	string str2 = inputFileName.substr(path.size(), stringSize);
	return str2;
}

//get the next file - if its the last line close the file and set endoffile has true;
string FileHandler::getNextline()
{
	
	if (inputFile.eof())
	{
		
		inputFile.close();
		endOfFile = true;
		return "";
	}
	//get the next line
	string line;
	getline(inputFile, line);
	return line;
}

void FileHandler::setrecordFile(string FileName)
{

	recorderFile.open(path + FileName+"."+ EndWith);
	if (!recorderFile.is_open())
	{
		cout << "error";
	}
}

void FileHandler::writeLine(string line)
{
	recorderFile << line;
}

void FileHandler::writeChar(char ch)
{
	recorderFile << ch;
}

void FileHandler::closeRecorderFile()
{
	recorderFile.close();

}

void FileHandler::closeInputFile()
{
	inputFile.close();
}