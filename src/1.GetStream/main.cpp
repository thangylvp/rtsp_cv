#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

int main(){
    cv::VideoCapture cap("rtsp://admin:zaq1XSW2@192.168.1.64:554/ch1/main/av_stream", cv::CAP_FFMPEG);
    if (!cap.isOpened())
    {   
        std::cout << "Input error\n";
        return -1;
    }

    cv::Mat frame;

    while(1) {
        cap >> frame;
        cv::imshow("frame", frame);
        if (cv::waitKey(5) == 'q') {
            break;
        }
    }
    cap.release();
}
