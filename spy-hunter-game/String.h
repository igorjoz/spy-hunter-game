#pragma once


#include<cstring>


class String
{
public:
	String();
	String(const char* string);
	String(const String& source);
	String(String&& source);
	~String();

	String& operator=(const String& rhs);
	String& operator=(String&& rhs);

	int length() const;
	const char* get() const;
	void set(const char* string);
	bool isEmpty() const;

private:
	char* string;
};

