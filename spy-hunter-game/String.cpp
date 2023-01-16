#include "String.h"


String::String() : string{ nullptr } {
	string = new char[1];
	*string = '\0';
}


String::String(const char* string) : string{ nullptr } {
	if (string == nullptr) {
		this->string = new char[1];
		*this->string = '\0';
	}
	else {
		this->string = new char[strlen(string) + 1];
		strcpy(this->string, string);
	}
}


String::String(const String& source) : string{ nullptr } {
	string = new char[strlen(source.string) + 1];
	strcpy(string, source.string);
}


String::String(String&& source) noexcept : string{ source.string } {
	source.string = nullptr;
}


String::~String() {
	delete[] string;
}


String& String::operator=(const String& rhs) {
	if (this != &rhs) {
		delete[] string;
		string = new char[strlen(rhs.string) + 1];
		strcpy(string, rhs.string);
	}
	
	return *this;
}


String& String::operator=(String&& rhs) noexcept {
	if (this != &rhs) {
		delete[] string;
		string = rhs.string;
		rhs.string = nullptr;
	}

	return *this;
}


int String::length() const {
	return strlen(string);
}


const char* String::get() const {
	return string;
}


void String::set(const char* string) {
	if (this->string != nullptr) {
		delete[] this->string;
	}

	if (string == nullptr) {
		this->string = new char[1];
		*this->string = '\0';
	}
	else {
		this->string = new char[strlen(string) + 1];
		strcpy(this->string, string);
	}
}


bool String::isEmpty() const {
	return string[0] == '\0';
}
