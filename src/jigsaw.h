#pragma once  
#include<opencv2/opencv.hpp>  
#include<algorithm>  

//�����ֳ����  
void montage(cv::Mat &output, cv::Mat &input, cv::Rect rect,
	cv::Scalar color = cv::Scalar(0)) //���ƴͼ��Χ����ouput��ô�Զ���color��ɫ���  
{
	if (rect.x + rect.width > output.cols || rect.y + rect.height > output.rows) {
		//ƴͼ�������ˣ���color���  
		int cols = std::max(rect.x + rect.width, output.cols);
		int rows = std::max(rect.y + rect.height, output.rows);
		cv::Mat Bigger(rows, cols, output.type());
		Bigger = color;
		montage(Bigger, output, cv::Rect(0, 0, output.cols, output.rows), color);
		output = Bigger.clone();
	}

	if (rect.width != input.cols || rect.height != input.rows) {
		cv::Mat temp;
		resize(input, temp, cv::Size(rect.width, rect.height));
		temp.copyTo(output(rect));
	}
	else input.copyTo(output(rect));
}

void montage(cv::Mat &output, cv::Mat &input, int x, int y, int width, int height, cv::Scalar color = cv::Scalar(0)) {
	montage(output, input, cv::Rect(x, y, width, height));
}
//���ֳ���ȵ����  
void montage(cv::Mat &output, cv::Mat &input, cv::Point location, double zoom_size = 1.0, cv::Scalar color = cv::Scalar(0)) {
	cv::Rect rect(location.x, location.y, input.cols*zoom_size, input.rows*zoom_size);
	montage(output, input, rect, color);
}
void montage(cv::Mat &output, cv::Mat &input, int x, int y, double zoom_size = 1.0, cv::Scalar color = cv::Scalar(0)) {
	cv::Rect rect(x, y, input.cols*zoom_size, input.rows*zoom_size);
	montage(output, input, rect, color);
}