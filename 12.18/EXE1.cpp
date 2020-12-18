//#include <iostream>
//#include <opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//int main()
//{
//	VideoCapture capVideo(0);
//	Mat frame;
//	Mat bgMat;
//	Mat subMat;
//	Mat bny_subMat;
//	int cnt = 0;
//	while (1) {
//		    
//			capVideo >> frame;
//			cvtColor(frame, frame, COLOR_BGR2GRAY);
//
//			if (cnt ==0) {
//				frame.copyTo(bgMat);
//				cnt++;
//			}
//
//			else {
//			absdiff(frame, bgMat, subMat);
//			threshold(subMat, bny_subMat, 50,255,CV_THRESH_BINARY);
//
//			imshow("b_subMat", bny_subMat);
//			imshow("subMat", subMat);
//			waitKey(30);
//            } 
//
//	}
//
//}