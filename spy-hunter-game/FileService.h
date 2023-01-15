#pragma once


class FileService
{
public:
	static const int BUFFER_SIZE = 20000;

	static void convertNumberAndWriteToBuffer(int number, char* buffer, int* bufferIndex);
	static int readAndConvertToNumber(char* buffer, int* bufferIndex);
	void saveGameToFile(char* fileName);
	void loadGameFromFile(char* fileName);

	static void saveToResults(int score);
};

