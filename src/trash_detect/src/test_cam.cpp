#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include "iostream"
#include "string"
#include "iomanip"
#include "sstream"

using namespace std;
using namespace cv;

int main(int, char**){
    VideoCapture camera(2);
    
    if(!camera.isOpened()){
	cerr << "ERROR: Could not open camera" << endl;
	return 1;
    }

    namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

    Mat frame;

    while(1){
	camera >> frame;
	imshow("Webcam", frame);

	char c = (char)waitKey(33);
	if (c==27) break;
	/*
	if(cv::waitKey(30) >= 27)
	    std::cout << "frame output" << std::endl;
	    break;
	*/
    }
    cvDestroyWindow("Webcam");

    return 0;
}
