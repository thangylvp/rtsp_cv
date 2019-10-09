#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <opencv2/opencv.hpp>
using namespace std;

#define NUM_THREADS 4

struct thread_data {
    int  thread_id;
    string *message;
};

void *PrintHello(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    // cout << "Thread ID : " << my_data->thread_id  << " Message : " << my_data->message << endl;
    // cv::VideoCapture cap(my_data->message, cv::CAP_FFMPEG);
    // if (!cap.isOpened())
    // {   
    //     std::cout << "Input error\n";
    //     pthread_exit(NULL);
    // }
    
    cout << "Thread ID : " << my_data->thread_id  << " Message : " << *(my_data->message) << endl;
    cv::VideoCapture cap(*(my_data->message));
    if (!cap.isOpened())
    {   
        std::cout << "Input error\n";
        pthread_exit(NULL);
    }

    cv::Mat frame;
    int cnt = 0;
    string name;
    while(1) {
        cap >> frame;
        name = std::to_string(my_data->thread_id) + "___" + std::to_string(cnt) + ".jpg";
        cnt++;
        cv::imwrite(name, frame);
        
    }
    cap.release();

    pthread_exit(NULL);
}

int main () {
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc;
    int i;

    for( i = 0; i < NUM_THREADS; i++ ) {
        cout <<"main() : creating thread, " << i << endl;
        td[i].thread_id = i;
        string tmp = "rtsp://admin:123@Abc.@10.10.0." + std::to_string(i + 164) + ":554/Streaming/Channels/101/";
        td[i].message = new string(tmp);
        rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);
        
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
        
    }

    for( i = 0; i < NUM_THREADS; i++ ) {
        pthread_join(threads[i], NULL);
    }
    pthread_exit(NULL);
}

/*
    cv::VideoCapture cap("rtsp://admin:123@Abc.@10.10.0.166:554/Streaming/Channels/101/", cv::CAP_FFMPEG);
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
    */

