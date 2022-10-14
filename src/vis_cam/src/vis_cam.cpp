#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
    string save_path = argv[1];
    VideoCapture cap(2);
    cout << "out put path is: " << save_path << endl; 
    
    if (cap.isOpened() == false){
	cout << "Can not open the video camera" << endl;
	cin.get();
	return -1;
    }

    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

    cout << "Resolution of the video: " << dWidth << " x " << dHeight << endl;

    string window_name = "My Camera Feed";
    namedWindow(window_name);
    int img_index = 0;

    while(true){
	Mat frame;
	bool bSuccess = cap.read(frame);

	if(bSuccess == false){
	    cout << "Video camera is disconnected" << endl;
	    cin.get();
	    break;
	}

	imshow(window_name, frame);

	int key = waitKey(10);
	//cout << "key value is: " << key << endl;

	if (key == 27){
	    cout << "End video" << endl;
	    break;
	}
	else if (key == 13){
	    string img_path = save_path + '/' + to_string(img_index) + ".jpg";
	    cout << "saving image" << img_path;
	    imwrite(img_path, frame);
	}
	img_index++;
    }

    return 0;
}
