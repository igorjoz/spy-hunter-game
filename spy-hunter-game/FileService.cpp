#define _CRT_SECURE_NO_WARNINGS


#include <cstdlib>
#include <string.h>
#include <stdio.h>


#include "FileService.h"
#include "Helper.h"


void FileService::convertNumberAndWriteToBuffer(int number, char* buffer, int* bufferIndex) {
	char* digits = Helper::convertNumberIntoDigitsArray(number);
	int digitsIndex = 0;

	while (digits[digitsIndex] != '\0') {
		buffer[(*bufferIndex)++] = digits[digitsIndex++];
	}
	buffer[(*bufferIndex)++] = '\n';
}


void FileService::saveGameToFile(char* fileName) {
	FILE* file;
	char buffer[FileService::BUFFER_SIZE];
	int bufferIndex = 0;

	// TODO: Save game data to buffer

	/*
	FORMAT

	Window:
	- Uint32 frameStartTime;
	- int frameFinishTime;
	- int frames;
	- int scoreFreezeTime;
	- int powerUpTime;
	- double delta;
	- double worldTime;
	- double fpsTimer;
	- double fps;

	Game:
	- int score;
	- bool isScoreFrozen;
	- bool isPowerUpActive;
	- bool isPowerUpUsedUp;
	- bool isPaused;

	PlayerCar:
	- int shootingRange;
	- bool isShooting;
	- int x;
	- int y;
	- CarSpeed verticalVelocity;
	- CarSpeed horizontalVelocity;
	- MovementDirection verticalMovementDirection;
	- MovementDirection horizontalMovementDirection;

	EnemyCar:
	- int x;
	- int y;
	- bool isDestroyed;
	- CarSpeed verticalVelocity;
	- CarSpeed horizontalVelocity;
	- MovementDirection verticalMovementDirection;
	- MovementDirection horizontalMovementDirection;

	NeutralCar:
	- int x;
	- int y;
	- bool isDestroyed;
	- CarSpeed verticalVelocity;
	- CarSpeed horizontalVelocity;
	- MovementDirection verticalMovementDirection;
	- MovementDirection horizontalMovementDirection;
	*/
	
	file = fopen(fileName, "wb");

	fwrite(buffer, sizeof(char), bufferIndex, file);

	fclose(file);
}

void FileService::loadGameFromFile(char* fileName) {
	FILE* file;
	long size;
	char* buffer;
	size_t result;

	int bufferIndex = 0;
	int currentPlayerId = -1;
	int blackPlayerScore = -1;
	int whitePlayerScore = -1;
	int boardSize = -1;

	file = fopen(fileName, "rb");
	if (file == NULL) {
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);

	buffer = (char*)malloc(sizeof(char) * size);
	if (buffer == NULL) {
		exit(2);
	}
		
	result = fread(buffer, 1, size, file);
	if (result != size) {
		exit(3);
	}
	rewind(file);	

	fclose(file);
	
	free(buffer);
}


int FileService::readAndConvertToNumber(char* buffer, int* bufferIndex) {
	char digit;
	int input = 0;
	
	while ((digit = buffer[*bufferIndex]) != '\n') {
		input = input * 10 + digit - '0';
		(*bufferIndex)++;
	}
	
	return input;
}


int* FileService::saveToResults(int score) {
	FILE* file;
	long size;
	char* buffer;
	size_t result;
	
	int bufferIndex = 0;

	int resultsQuantity = 0;

	file = fopen("results.txt", "rb");

	if (file == NULL) {
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);

	buffer = (char*)malloc(sizeof(char) * size);
	if (buffer == NULL) {
		exit(2);
	}

	result = fread(buffer, 1, size, file);
	if (result != size) {
		exit(3);
	}

	char digit = buffer[bufferIndex++];
	resultsQuantity = digit - '0';
	bufferIndex++;
	
	int* results = new int[resultsQuantity];
	int i = 0;

		
	while (bufferIndex < size) {
		int digitIndex = 0;
		char* digits = new char[100];

		while (buffer[bufferIndex] != '\n') {
			digits[digitIndex] = buffer[bufferIndex];
			digitIndex++;
			bufferIndex++;
		}

		if (buffer[bufferIndex] == '\n') {
			bufferIndex++;
		}

		digits[digitIndex] = '\0';
		
		results[i++] = atoi(digits);
	}

	fclose(file);

	// add the new result to the array
	resultsQuantity++;

	int* newResults = new int[resultsQuantity];
	
	for (int i = 0; i < resultsQuantity - 1; i++) {
		newResults[i] = results[i];
	}
	newResults[resultsQuantity - 1] = score;
	
	// sort the array
	for (int i = 0; i < resultsQuantity; i++) {
		for (int j = 0; j < resultsQuantity - 1; j++) {
			if (newResults[j] < newResults[j + 1]) {
				int temp = newResults[j];
				newResults[j] = newResults[j + 1];
				newResults[j + 1] = temp;
			}
		}
	}

	// leave 5 best scores
	if (resultsQuantity > 5) {
		resultsQuantity = 5;
	}
	
	// write the new array to the file
	file = fopen("results.txt", "wb");
	
	bufferIndex = 0;
	buffer[bufferIndex++] = '0' + resultsQuantity;
	buffer[bufferIndex++] = '\n';

	for (int i = 0; i < resultsQuantity; i++) {
		char* resultString = new char[100];
		_itoa(newResults[i], resultString, 10);
		int resultStringLength = strlen(resultString);

		for (int j = 0; j < resultStringLength; j++) {
			buffer[bufferIndex++] = resultString[j];
		}

		buffer[bufferIndex++] = '\n';
	}
	
	fwrite(buffer, sizeof(char), bufferIndex, file);
	
	fclose(file);

	delete[] results;

	return newResults;
}