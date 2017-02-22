#include<iostream>
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgcodecs.hpp>
#include<vector>
using namespace cv;


int main(int argc,char* argv[]) {
	
	if (argc < 2) {
		return -1;
	}

	Mat img = imread (argv[1], IMREAD_UNCHANGED);

	Mat gray_img;

	cvtColor(img, gray_img, CV_RGB2GRAY);

	Mat bin_img;

	adaptiveThreshold(gray_img, bin_img, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,99, 8);

	bin_img = ~bin_img;

	Mat element = Mat::ones(5, 5, CV_8UC1);

	imshow("element",element);
	//erode(bin_img,bin_img);
	for (int i = 0; i < 4; i++) {
		erode(bin_img,bin_img,element,Point(-1,-1),1);
		imshow("IMAGE", bin_img);
		//waitKey(10000);

	}

	imshow("IMAGE", bin_img);
	
	
	//waitKey(10000);


	//—ÖŠsŒŸo‚·‚é
	std::vector<std::vector<Point>> contours;

	findContours(bin_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++) {
		int count = contours.at(i).size();
		double x = 0, y = 0;
		for (int j = 0; j < count; j++) {
			x += contours.at(i).at(j).x;
			y += contours.at(i).at(j).y;
		}
		x /= count;
		y /= count;
		circle(img,Point(x,y),5,Scalar(0,0,255),2,4);

	}

	std::cout << contours.size() << " seeds" << std::endl;
	imshow("IMAGE",img);

	waitKey(20000);
	return 0;
}