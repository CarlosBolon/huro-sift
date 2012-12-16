#include <vector>

#include "ObjectRecognition\FileToken.h"
#include "ObjectRecognition\Tokenizer.h"
#include "ObjectRecognition\LocalSettings.h"

using namespace std;

namespace ObjectRecognition
{

    FileToken::FileToken(const string& path)
    :   fileName_(""),
        path_("")
    {
        vector<string> pathParts;
        Tokenizer t(path, "\\.");

        while(t.NextToken())
            pathParts.push_back(t.GetToken());

        if(pathParts.size() < 3)
            CV_Error(1, "Wrong filename (" + path + ")!");

        path_ = LocalSettingsPtr->GetDataBaseDirectory() + pathParts[pathParts.size() - 3] + "/";
        fileName_ = pathParts[pathParts.size() - 2];
    }


    FileToken::~FileToken(void)
    {
    }

    const string& FileToken::GetName(void) const
    {
        return fileName_;
    }

    const string& FileToken::GetPath(void) const
    {
        return path_;
    }

}
