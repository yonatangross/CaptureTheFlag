#pragma once
#include <string>
#include "Tool.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "FileUtils.h"
#include <algorithm>


using namespace std;
class FileHandler
{
	//for all file the class
	string EndWith;
	string path;

	//for input fils 
	bool endOfFile = false;  //check if end of file
	vector<string> Inputfiles; // all files for path and type orber alphabet
	string inputFileName; // current input file name
	ifstream inputFile; // current input file
	
	// for record file 
	ofstream recorderFile;

	public:
		
		//getter/ setter
		void setEndWith(string end) { EndWith = end; }
		void setPath(string pth) { path = pth; }
		bool getendOfFile() { return endOfFile; }
		string  getInputFileName();

		/*input files*/
		//get all inputfiles
		void getInputFiles();
		//return number of files in the vector
		int getNumOfInputFiles();
		//open the next input file in the vector
		void openInputFile();
		//open input file by name
		bool openInputFile(string fileName);
		
		//get next line
		string readLine();
		

		string getNextline();
		//closr input file
		void closeInputFile();

		/*record files*/
		//open file
	void setrecordFile(string FileName);
	//write line
	void writeLine(string line);
	//write char
	void writeChar(char ch);

	//close  file
	void closeRecorderFile();

	
};