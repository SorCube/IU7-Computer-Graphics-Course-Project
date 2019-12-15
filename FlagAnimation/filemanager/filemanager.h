#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <QDir>

using namespace std;

class FileManager
{
public:
    FileManager(string name) : 
		files_path(QDir::current().path().toStdString()),
		file_name(files_path + name) {}
    ~FileManager() {}

    /*void write();
    void reopen(string name);*/
	
private:
	const string files_path;
    string file_name;
};

#endif // FILEMANAGER_H
