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


int FileService::readAndConvertToNumber(char* buffer, int* bufferIndex) {
	char digits[100];
	int digitsIndex = 0;

	char currentCharacter = buffer[(*bufferIndex)++];

	while (currentCharacter != '\n') {
		digits[digitsIndex++] = currentCharacter;

		currentCharacter = buffer[(*bufferIndex)++];
	}

	int number = Helper::convertDigitsArrayIntoNumber(digits, digitsIndex);

	return number;
}


void FileService::saveGameToFile(char* fileName) {
	FILE* file;
	char buffer[FileService::BUFFER_SIZE];
	int bufferIndex = 0;


	
	// conver board size & write to the file
	/*Board::convertNumberAndWriteToBuffer(this->getCurrentPlayerId(), buffer, &bufferIndex);
	Board::convertNumberAndWriteToBuffer(this->blackPlayer->getScore(), buffer, &bufferIndex);
	Board::convertNumberAndWriteToBuffer(this->whitePlayer->getScore(), buffer, &bufferIndex);
	Board::convertNumberAndWriteToBuffer(this->size, buffer, &bufferIndex);

	for (int rowIndex = 0; rowIndex < this->size; rowIndex++) {
		for (int columnIndex = 0; columnIndex < this->size; columnIndex++) {
			buffer[bufferIndex++] = '0' + this->board[rowIndex][columnIndex];
		}
	}
	buffer[bufferIndex++] = '\n';

	for (int rowIndex = 0; rowIndex < this->size; rowIndex++) {
		for (int columnIndex = 0; columnIndex < this->size; columnIndex++) {
			buffer[bufferIndex++] = '0' + this->previousBoard[rowIndex][columnIndex];
		}
	}
	buffer[bufferIndex++] = '\n';*/



	/*

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

	/*

	currentPlayerId = this->readAndConvertToNumber(buffer, &bufferIndex);
	blackPlayerScore = this->readAndConvertToNumber(buffer, &bufferIndex);
	whitePlayerScore = this->readAndConvertToNumber(buffer, &bufferIndex);
	boardSize = this->readAndConvertToNumber(buffer, &bufferIndex);

	this->blackPlayer->setScore(blackPlayerScore);
	this->whitePlayer->setScore(whitePlayerScore);

	*this = Board(boardSize, true, this->blackPlayer, this->whitePlayer, currentPlayerId);

	for (int rowIndex = 0; rowIndex < this->size; rowIndex++) {
		for (int columnIndex = 0; columnIndex < this->size; columnIndex++) {
			this->board[rowIndex][columnIndex] = buffer[bufferIndex++] - '0';
		}
	}*/

	

	fclose(file);
	
	free(buffer);
}


void FileService::saveToResults(int score) {
	FILE* file;
	long size;
	char* buffer;
	size_t result;
	//char buffer[FileService::BUFFER_SIZE];
	int bufferIndex = 0;

	int resultsQuantity = 0;

	// read the file and append nums to array; first line is number of results in the file and the rest are the results
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
	rewind(file);

	// 1. Use the fgets function to read the first line of the file into a char array.
	// 2. Convert the char array to an int using the atoi() function.
	// 3. Assign the int value to a variable, for example "resultsQuantity".
	// DO NOT USE readAndConvertToNumber function
	resultsQuantity = atoi(buffer);
	//print resultsQuantity
	printf("resultsQuantity: %d\n", resultsQuantity);
	
	// 1. Create a new array of ints with size "resultsQuantity + 1".
	// 2. Copy the values from the old array to the new array.
	// 3. Add the new score to the new array.
	// 4. Sort the new array.
	// 5. Write the new array to the file.
	// 6. Free the old array.
	
	
	
	

	int* results = new int[resultsQuantity];

	// increase bufferIndex to skip the first line
	bufferIndex = 0;
	while (buffer[bufferIndex++] != '\n');

	for (int i = 0; i < resultsQuantity; i++) {
		// read the next line and convert it to int
		results[i] = FileService::readAndConvertToNumber(buffer, &bufferIndex);
		
		
		
		/*results[i] = FileService::readAndConvertToNumber(buffer, &bufferIndex);*/
		// print results[i]
		printf("results[%d]: %d\n", i, results[i]);
	}

	fclose(file);

	//// add the new result to the array
	//resultsQuantity++;
	//int* newResults = new int[resultsQuantity];
	//for (int i = 0; i < resultsQuantity - 1; i++) {
	//	newResults[i] = results[i];
	//}
	//newResults[resultsQuantity - 1] = score;
	//
	//// sort the array
	//
	//for (int i = 0; i < resultsQuantity; i++) {
	//	for (int j = 0; j < resultsQuantity - 1; j++) {
	//		if (newResults[j] < newResults[j + 1]) {
	//			int temp = newResults[j];
	//			newResults[j] = newResults[j + 1];
	//			newResults[j + 1] = temp;
	//		}
	//	}
	//}


	//// write the new array to the file
	//file = fopen("results.txt", "wb");
	//
	//bufferIndex = 0;
	//buffer[bufferIndex++] = '0' + resultsQuantity;
	//buffer[bufferIndex++] = '\n';
	//
	//for (int i = 0; i < resultsQuantity; i++) {
	//	buffer[bufferIndex++] = '0' + newResults[i];
	//	buffer[bufferIndex++] = '\n';
	//}
	//
	//fwrite(buffer, sizeof(char), bufferIndex, file);
	//
	//fclose(file);

	//free(buffer);

	//delete[] results;

	//delete[] newResults;




	//file = fopen("results.txt", "w");
	//
	//// convert score & write to the file
	//FileService::convertNumberAndWriteToBuffer(score, buffer, &bufferIndex);
	//
	//fwrite(buffer, sizeof(char), bufferIndex, file);
	//
	//fclose(file);
}