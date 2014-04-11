#include "qh_string.h"

#include <string.h>
#include <stdlib.h>
#include <stdexcept>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
	if(s == NULL) return;
	len_ = strlen(s);
	data_ = new char[len_+1];
	strcpy(data_,s);
    }

    string::string( const char* s, size_t len )
    {
	len_ = len;
	data_ = new char[len_+1];
	*(data_+len_)='\0';
	strncpy(data_,s,len);
    }

    string::string( const string& rhs )
    {
	len_ = rhs.len_;
	data_ = new char[len_+1];
	strcpy(data_,rhs.c_str());
    }

    string& string::operator=( const string& rhs )
    {
        if(this == &rhs) return *this;
	char *d = (char *)realloc(data_,sizeof(char)*(rhs.size()+1));
	data_ = d;
	strcpy(data_,rhs.data());
	len_ = rhs.size();
	return *this;
    }

    string::~string()
    {
	if(len_ != 0){
		delete[] data_;
		data_ = NULL;
	}
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char& string::operator[]( size_t index )
    {
        if(index >= len_){
		throw std::out_of_range("index out of range");
	}
	return data_[index];
    }

}
