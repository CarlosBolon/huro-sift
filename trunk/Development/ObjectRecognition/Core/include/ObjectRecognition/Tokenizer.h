#pragma once
#pragma warning( disable: 4251 ) // Disable needs to have dll-interface warning.

#include <string>

namespace ObjectRecognition
{

extern "C++" class __declspec(dllexport) Tokenizer 
{
public:
	static const std::string DELIMITERS;

	Tokenizer(const std::string& str);
	Tokenizer(const std::string& str, const std::string& delimiters);

	bool NextToken(void);
	bool NextToken(const std::string& delimiters);
	const std::string GetToken(void) const;
	void Reset(void);

protected:
	size_t offset_;
	const std::string string_;
	std::string token_;
	std::string delimiters_;
};

}
