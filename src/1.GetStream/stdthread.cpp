#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include <list>
#include <algorithm>
#include <mutex>

using namespace std;

// a global variable
cv::Mat frameData[4];

// a global instance of std::mutex to protect global variable
std::mutex myMutex[4];

void addToList(std::string camPath, int threadId)
{
	// the access to this function is mutually exclusive
	// std::lock_guard<std::mutex> guard(myMutex[threadId]);

    // cout << "Thread ID : " << threadId  << " Path : " << camPath << endl;
    cv::VideoCapture cap(camPath);
    if (!cap.isOpened())
    {   
        std::cout << "Input error " << camPath << std::endl;
        return;
    } else {
        std::cout << "Success open cam " << threadId << std::endl;
    }
    cv::Mat tmp;
    while(1) {
        
        cap >> tmp;
        myMutex[threadId].lock();
        frameData[threadId] = tmp.clone();
        myMutex[threadId].unlock();
        
    }
    cap.release();
}

void imgShow()
{
    // std::cerr << "yyyyyyyyyyyyyyyyyyyyyyy" << std::endl;
	// the access to this function is mutually exclusive

    std::cout << "zzzzzzzzzzzzzzzzzzzzzzz" << std::endl;
    std::string name;
	for (int i = 0; i < 4; i++) {
        name = "cam" + std::to_string(i);
        cv::namedWindow(name, cv::WINDOW_NORMAL);
    }
	
    cv::Mat frame[4];
    while (1)
    {
        
        for (int i = 0; i < 4; i++) {
            myMutex[i].lock();
            frame[i] = frameData[i].clone();
            myMutex[i].unlock();
        }

        for (int i = 0; i < 4; i++) {
            name = "cam" + std::to_string(i);
            if (frame[i].cols > 0) cv::imshow(name, frame[i]);
        }
        cv::waitKey(30);
    }
}

int main()
{

    std::string camPath[4];
	camPath[0] = "rtsp://admin:123@Abc.@10.10.0.163:554/Streaming/Channels/101/";
    camPath[1] = "rtsp://admin:123@Abc.@10.10.0.164:554/Streaming/Channels/101/";
    camPath[2] = "rtsp://admin:123@Abc.@10.10.0.165:554/Streaming/Channels/101/";
    camPath[3] = "rtsp://admin:123@Abc.@10.10.0.166:554/Streaming/Channels/101/";

	std::thread t[4];
	for (int i = 0; i < 4; i++) {
        t[i] = std::thread(addToList, camPath[i], i);
    }

	
    std::thread show(imgShow);
    for (int i = 0; i < 4; i++) t[i].join();
    show.join();
	return 0;
}