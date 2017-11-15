#pragma once
#include <fstream>

class FileHandler {

private:

	char *fileName;

public:

	FileHandler(char *fileName);

	void openFile();

	void closeFile();
};