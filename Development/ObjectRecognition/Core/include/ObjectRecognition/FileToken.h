#pragma once

#include <string>
#include "opencv2/opencv.hpp"

namespace ObjectRecognition
{

extern "C++" class __declspec(dllexport) FileToken
{
public:
    FileToken(const std::string& path);
    ~FileToken(void);

    const std::string& GetName(void) const;
    const std::string& GetPath(void) const;

private:
    std::string fileName_;
    std::string path_;
};

}
