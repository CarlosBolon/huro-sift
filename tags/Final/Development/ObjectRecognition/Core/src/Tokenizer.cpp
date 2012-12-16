#include "ObjectRecognition\Tokenizer.h"

using namespace std;

namespace ObjectRecognition
{


const string Tokenizer::DELIMITERS(" \\.\t\n\r");


Tokenizer::Tokenizer(const string& s) 
:	string_(s), 
	offset_(0), 
	delimiters_(DELIMITERS)
{
}


Tokenizer::Tokenizer(const string& s, const string& delimiters) 
:	string_(s), 
	offset_(0), 
	delimiters_(delimiters)
{
}


bool Tokenizer::NextToken(void) 
{
	return NextToken(delimiters_);
}


const std::string Tokenizer::GetToken(void) const
{
	return token_;
}


bool Tokenizer::NextToken(const string& delimiters) 
{
	size_t i = string_.find_first_not_of(delimiters, offset_);

	if(string::npos == i) 
	{
		offset_ = string_.length();
		return false;
	}

	size_t j = string_.find_first_of(delimiters, i);
	if(string::npos == j) 
	{
		token_ = string_.substr(i);
		offset_ = string_.length();
		return true;
	}

	token_ = string_.substr(i, j - i);
	offset_ = j;

	return true;
}


}
