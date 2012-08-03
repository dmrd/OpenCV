#include <iostream>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;



int main ( int argc, char **argv ) {

    int frameNum = 1;
    Mat edges, blend, original;
    VideoCapture camera(0); //Open default camera
    if (!camera.isOpened()) {
        cerr << "Camera failed to initialize";
        return -1;
    }

    namedWindow("original");
    namedWindow("blended");
    namedWindow("edges");
    while (true) {
        Mat frame;
        camera >> frame; //Get frame
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(71, 71), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        frame.copyTo(blend);
        //addWeighted(original, 0.9, edges, 0.1, 0.0,  blend);
        //add(frame, edges, blend);
        blend.setTo(255, edges);

        imshow("original", frame);
        imshow("edges", edges);
        imshow("blended", blend);
        if(waitKey(30) >= 0) {
            break;
        }
    }
    return 0;
}
