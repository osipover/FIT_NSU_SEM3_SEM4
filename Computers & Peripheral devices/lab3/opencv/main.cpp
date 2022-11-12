#include <iostream> // for standard I/O
#include <string> // for strings
#include <iomanip> // for controlling float print precision
#include <sstream> // string to number conversion
#include <opencv2/core.hpp> // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp> // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp> // OpenCV window I/O
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <time.h>
#include <chrono>
using namespace std;
using namespace cv;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

void getClearImg(Mat img, VideoCapture &cap, int numFrames) {
	time_t start, end;

	time(&start);
	while (true) {
		cap.read(img);
		imshow("Image", img);
		char c = waitKey(1);
		if (c == 'z') break;
		++numFrames;
	}
	time(&end);
	double seconds = difftime(end, start);
	double fps = numFrames / seconds;
	cout << "FPS: " << fps << endl;
}

void getConvertedImg(Mat img, VideoCapture &cap, int numFrames) {
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	assert(!faceCascade.empty());

	double timeInput = 0;
	double timeProc = 0;
	double timeOutput = 0;

	auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	while (true) {
		auto startInput = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		cap.read(img);
		auto endInput = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

		auto startProc = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		vector<Rect> faces;
		faceCascade.detectMultiScale(img, faces, 1.1, 2);
		for (int i = 0; i < faces.size(); ++i) {
			GaussianBlur(img(faces[i]), img(faces[i]), Size(55, 55), 5); 
		}
		auto endProc = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

		auto startOutput = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		imshow("Image", img);
		auto endOutput = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

		++numFrames;
		timeInput += (endInput - startInput);
		timeProc += (endProc - startProc);
		timeOutput += (endOutput - startOutput);		
		
		char c = waitKey(1);
		if (c == 'z') break;
	}
	auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	double seconds = (end - start)/1000.0;
	double fps = numFrames / seconds;
	cout << "Total time: " << (int)seconds << " sec" << endl;
	cout << "FPS: " << fps << endl;
	cout << "Time for input: " << ((timeInput/1000.0)/seconds)*100 << " %" << endl;
	cout << "Time for processing: " << ((timeProc / 1000.0) / seconds) * 100 << " %" <<endl;
	cout << "Time for output: " << ((timeOutput / 1000.0) / seconds) * 100 << " %" << endl;
}


int main(int argc, char* argv[]) {
	VideoCapture cap(0);
	Mat img;

	int numFrames = 0;
	getClearImg(img, cap, numFrames);
	getConvertedImg(img, cap, numFrames);

	return 0;
}
