#include <iostream>
#include "ExceptionDescriptor.h"
#include "HuroAlgorithm.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    int result = 0;

	/* The function can be used to dynamically turn on and off optimized code (code that uses SSE2, AVX, and other
	   instructions on the platforms that support it). It sets a global flag that is further checked by OpenCV functions. */
	if(useOptimized() == false)
		setUseOptimized(true);

	/* The function sets the number of threads used by OpenCV in parallel OpenMP regions. */
	if(getNumThreads() < 100)
		setNumThreads(100);

	try
	{
		HuroAlgorithm algorithm;
		algorithm.Process();
	} 
	catch(ExceptionDescriptor &e)
	{
		e.TraceError();
		result = -1;
	} 
	catch(...)
	{
		cerr << "Unknown exception!" << endl;
		result = -1;
	}

    system("pause");
	
    return result;
}
