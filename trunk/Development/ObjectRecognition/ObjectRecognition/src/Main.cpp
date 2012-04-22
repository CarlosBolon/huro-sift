#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

#include "SiftFeature.h"
#include "ExceptionDescriptor.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	VideoCapture cap;
	Mat frame;

	cap.open(0);

	if( !cap.isOpened() )
		throw ExceptionError("Could not initialize capturing.");

	cap >> frame;

	//imshow("frame", frame);

	auto_ptr<SiftFeature> thread1(new SiftFeature(1, frame));
	auto_ptr<SiftFeature> thread2(new SiftFeature(2, frame));

	//thread3 is created on the stack
	//SiftFeature thread3(3, frame);

	thread1->Start();
	thread2->Start();
	//thread3.Start();

	// wait for the threads to finish
	int result1 = reinterpret_cast<int>(thread1->Join());
	int result2 = reinterpret_cast<int>(thread2->Join());
	//int result3 = reinterpret_cast<int>(thread3.Join());

	cout << result1 << ' ' << endl;

	//imshow("first", thread1->frame_);
	//imshow("second", thread2->frame_);
	//imshow("third", thread3.frame_);
	//waitKey(0);
	//std::auto_ptr<Runnable> r(new simpleRunnable(1));
	//std::auto_ptr<Thread> thread0(new Thread(r));
	//thread0->start();

	//// thread1 and thread2 are created on the heap
	//auto_ptr<SiftFeature> thread1(new SiftFeature(1, image));
	//auto_ptr<SiftFeature> thread2(new SiftFeature(2, image));

	//// thread3 is created on the stack
	//SiftFeature thread3(3, image);

	//thread1->Start();
	//thread2->Start();
	//thread3.Start();

	//// wait for the threads to finish
	//int result1 = reinterpret_cast<int>(thread1->Join());
	//int result2 = reinterpret_cast<int>(thread2->Join());
	//int result3 = reinterpret_cast<int>(thread3.Join());

	//cout << result1 << ' ' << result2 << ' ' << result3 << endl;

	return 0;
}
