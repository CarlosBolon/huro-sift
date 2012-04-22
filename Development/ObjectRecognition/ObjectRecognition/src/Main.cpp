#include <iostream>
#include "ExceptionDescriptor.h"
#include "ObjRecAlgorithm.h"

using namespace std;

int main(int argc, char** argv)
{
	try
	{
		ObjRecAlgorithm algorithm;
		algorithm.Process();

		system("pause");
	} 
	catch(ExceptionDescriptor &e)
	{
		e.TraceError();
		system("pause");
		exit(-1);
	} 
	catch(...)
	{
		cerr << "Unknown exception!" << endl;
		system("pause");
		exit(-1);
	}

	return 0;
}
