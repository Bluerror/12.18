#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int aver_variance(std::vector<cv::Mat>pics, cv::Mat& Average, cv::Mat& Variance) {
	int rows = pics[0].rows;
	int cols = pics[0].cols;


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int sum = 0;
			float var = 0;
			//求均值
			for (int c = 0; c < pics.size(); c++) {
				sum += pics[c].at<uchar>(i, j);
			}
			Average.at<uchar>(i, j) = sum / pics.size();
			//求方差
			for (int n = 0; n < pics.size(); n++) {
				var += pow((pics[n].at<uchar>(i, j) - Average.at<uchar>(i, j)), 2);
			}
			Variance.at<float>(i, j) = var / pics.size();
		}
	}
	return 0;
}
int Threshold(cv::Mat src, cv::Mat& Average, cv::Mat& Variance,  cv::Mat& dst)
{
	int src1;
	int aver;
	int dst1;
	int rows = src.rows;
	int cols = src.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			src1 = src.at<uchar>(i, j);
			aver = Average.at<uchar>(i, j);
			int dif = abs(src1 - aver);
			int th = Variance.at<float>(i, j);
			if (dif > th)
			{
				dst.at<uchar>(i, j) = 255;
			}
			else {
				dst.at<uchar>(i, j) = 0;
			}
		}
	}
	return 0;
}
int main()
{
	VideoCapture capVideo(0);
	Mat frame;
	Mat Average;
	Mat Final;
	Mat Variance;
	std::vector<cv::Mat>ALL;


	int cnt = 0;
	
	while (1) {

		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt < 50) {

			ALL.push_back(frame);
			if (cnt == 0) {
				std::cout << "reading frame " << std::endl;
			}
			
		}
		else if (cnt == 50) {
			Average.create(frame.size(), CV_8UC1);
			Variance.create(frame.size(), CV_32FC1);

			aver_variance(ALL, Average, Variance);
		}

		else {
			Final.create(frame.size(), CV_8UC1);
			Threshold(frame, Average, Variance, Final);
			imshow("frame", frame);
			imshow("Final", Final);
			waitKey(30);
		}
		cnt++;
	}
	return 0;
}

