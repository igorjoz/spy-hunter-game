#pragma once


class FileService
{
public:
	static const int BUFFER_SIZE = 20000;

	void convertNumberAndWriteToBuffer(int number, char* buffer, int* bufferIndex);
	void saveGameToFile(char* fileName);
	void loadGameFromFile(char* fileName);
	
	int readAndConvertToNumber(char* buffer, int* bufferIndex);
	int* saveToResults(int score);
};

