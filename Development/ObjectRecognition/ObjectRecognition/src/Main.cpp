#include <iostream>
#include "opencv2/opencv.hpp"

#include "ObjectRecognition\LocalSettings.h"
#include "ObjectRecognition\Algorithm.h"

using namespace std;
using namespace cv;
using namespace ObjectRecognition;

int main(int argc, char *argv[])
{
	if(argc >= 2)
		LocalSettingsPtr->SetProcessXmlFileName(argv[1]);
	
	int result = 0;
	ObjectRecognition::Algorithm algorithm;

    /* The function can be used to dynamically turn on and off optimized code (code that uses SSE2, AVX, and other
	   instructions on the platforms that support it). It sets a global flag that is further checked by OpenCV functions. */
	if(useOptimized() == false)
		setUseOptimized(true);

	/* The function sets the number of threads used by OpenCV in parallel OpenMP regions. */
	if(getNumThreads() < 100)
		setNumThreads(100);

	try
	{
		algorithm.Process();
	}
	catch(Exception& e)
	{
		cout << "Exception caught: " << e.what() << endl;
		result = -1;
	}

    system("pause");

	return result;
}
