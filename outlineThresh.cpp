#include <iostream>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

// Function header
void bound();

int main ( int argc, char **argv ) {

    Mat out, frame_gray, result;
    Mat threshold_output;
    vector<Point> centers;
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours;
    int thresh = 200; //Threshold value
    int max_thresh = 255;
    int key;
    int frameNum = 1;
    VideoCapture camera(0); //Open default camera
    if (!camera.isOpened()) {
        cerr << "Camera failed to initialize";
        return -1;
    }

    namedWindow("source", CV_WINDOW_AUTOSIZE);
    //namedWindow("blobs");
    while (true) {
        Mat frame;
        camera >> frame; //Get frame
        cvtColor(frame, frame_gray, CV_BGR2GRAY);
        blur(frame_gray, frame_gray, Size(3, 3));

        /// Detect edges using Threshold
        threshold( frame_gray, threshold_output, thresh, 255, THRESH_BINARY );

        result = frame_gray;

        findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

        for (int c = 0; c < contours.size(); c++) {
            centers.push_back(Point(0,0));
            for (int p = 0; p < contours[c].size(); p++) {
                centers[c] += contours[c][p];   
            }
            centers[c].x /= contours[c].size();
            centers[c].y /= contours[c].size();;
        }

        drawContours(result, contours, -1, Scalar(0,0, 255), 5);

        for (int c = 0; c < centers.size(); c++) {
            circle(result, centers[c], 5, Scalar(255, 0, 0) , -1);
                }

        imshow("source", frame);
        imshow("threshold", threshold_output);
        imshow("result", result);
        
        key = waitKey(30);
        if(key == 65362 && thresh < 255) {
            thresh++;
        } else if (key == 65364 && thresh > 0) {
            thresh--;
        } else if (key > 0) {
            break;
        }
    }
    return 0;
}
