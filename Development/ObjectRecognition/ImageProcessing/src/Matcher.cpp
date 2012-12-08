#include "ObjectRecognition\Matcher.h"
#include "ObjectRecognition\FileToken.h"

using namespace std;
using namespace cv;

namespace ObjectRecognition
{

Matcher::Matcher(const string& descriptorType, const string& matcherType)
:   descriptorType_(descriptorType),
    matcherType_(matcherType)
{
    descriptorMatcher_ = DescriptorMatcher::create(matcherType_);

    CV_Assert(!descriptorMatcher_.empty());
}


Matcher::~Matcher(void)
{
}

void Matcher::Process(const vector<string>& imageList, const Mat& queryDescriptors)
{
    CV_Assert(!imageList.empty());
    CV_Assert(!queryDescriptors.empty());

    trainDescriptors_.clear();
    matches_.clear();

    FillTrainDescriptors(imageList);

    if(!trainDescriptors_.empty())
    {
        cout << "< Set train descriptors collection in the matcher and match query descriptors to them..." << endl;
        TickMeter tm;

        tm.start();
        descriptorMatcher_->add(trainDescriptors_);
        descriptorMatcher_->train();
        tm.stop();
        double buildTime = tm.getTimeMilli();

        tm.start();
        descriptorMatcher_->match(queryDescriptors, matches_);
        tm.stop();
        double matchTime = tm.getTimeMilli();

        CV_Assert( queryDescriptors.rows == (int)matches_.size() || matches_.empty() );

        cout << "Number of matches: " << matches_.size() << endl;
        cout << "Build time: " << buildTime << " ms; Match time: " << matchTime << " ms" << endl;
        cout << ">" << endl;
    }
}

void Matcher::FillTrainDescriptors(const std::vector<std::string>& imageList)
{
    CV_Assert(trainDescriptors_.empty());

    Mat descriptor;
    for(int i = 0; i < int(imageList.size()); i++)
    {
        FileToken ft(imageList[i]);
        string fullName = ft.GetPath() + ft.GetName() + "_descriptors.xml.gz";
        
        FileStorage fs(fullName, FileStorage::READ, "UTF-8");
        if(!fs.isOpened())
        {
            CV_Error(1, "Descriptor XML does not exist (" + fullName + ")!");
        }

        FileNode node = fs["database"];
        string key = descriptorType_ + "_Descriptors";

        cout << "Loading " + descriptorType_ + " descriptor for: " << fullName << endl;

        if(!node[0][key].isNone())
        {
            node[0][key] >> descriptor;
            if(!descriptor.empty())
            {
                trainDescriptors_.push_back(descriptor);
            }
        }
        else
        {
            CV_Error(1, descriptorType_ + " descriptor does not exist (" + fullName + ")!");
        }

        fs.release();
    }
}

const vector<DMatch>& Matcher::GetMatches(void) const
{
    return matches_;
}

}
