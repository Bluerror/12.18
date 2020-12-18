#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

float aver(float*a,int n)
{
	float sum = 0;
	float aver = 0;
	for (int i = 0; i < n; i++) {
		sum =sum+ a[i];
	}
	aver = sum / n;
	return aver;
}
float variance(float*a,int n)
{
	float dis = 0;
	float sum = 0;

    float average = aver(a, n);
	for (int i = 0; i < n; i++) {
		dis = (a[i] -average) * (a[i]-average)+dis;
	}
	sum = dis / n;
	return sum;
}

int main()
{
	VideoCapture capVideo(0);
	Mat frame;
	Mat bgMat;
	Mat subMat;
	Mat bny_subMat;
	int cnt = 0;
	while (1) {

		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		int length= frame.rows;
		int height=frame.cols;
		vector<Mat>every;
		
		if (cnt <50) {
			frame.copyTo(bgMat);
            every.push_back(frame);
			cnt++; 
		}

		else {
			for(cnt=0;cnt<50;cnt++)
				for (int i = 0; i < length; i++) {
					for (int j = 0; j < height; j++) {
						int bins = length * height;
						float* every = new float[bins];
						memset(every, 0, sizeof(float) * bins);
						delete[]every;
						aver(every, 50);
						variance(every, 50);
						absdiff(frame, bgMat, subMat);//背景图像与当前相减
						threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);//差分结果二值化
					}
				}
			imshow("b_subMat", bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}

	}

}