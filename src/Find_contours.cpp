#include "Find_contours.h"
std::vector<cv::Point> help_findhandcounters(cv::Mat &frame)

 {

 cv::Mat frameHSV;	// hsv�ռ�
 cv::Mat mask(frame.rows, frame.cols, CV_8UC1);	// 2ֵ��Ĥ
 cv::Mat dst(frame);	// ���ͼ��

						// 	cv::Mat frameSplit[4];

 std::vector< std::vector<cv::Point> > contours;	// ����
 std::vector< std::vector<cv::Point> > filterContours;	// ɸѡ�������
 std::vector< cv::Vec4i > hierarchy;	// �����Ľṹ��Ϣ
 std::vector< cv::Point > hull;	// ͹����ĵ㼯


 medianBlur(frame, frame, 5);
 GaussianBlur(frame, frameHSV, cv::Size(5, 5), 2, 2);
 // 		imshow("blur2", frameHSV);
 //		pyrMeanShiftFiltering(frame, frameHSV, 10, 10);
 //	 	imshow(WIN_BLUR, frameHSV);
 // ת����HSV��ɫ�ռ䣬�����״���
 cvtColor(frame, frameHSV, CV_BGR2HSV);

 // 		split(frameHSV, frameSplit);
 // 		imshow(WIN_H, frameSplit[0]);
 // 		imshow(WIN_S, frameSplit[1]);
 // 		imshow(WIN_V, frameSplit[2]);

 cv::Mat dstTemp1(frame.rows, frame.cols, CV_8UC1);
 cv::Mat dstTemp2(frame.rows, frame.cols, CV_8UC1);
 // ��HSV�ռ�����������õ�2ֵͼ�����Ĳ���Ϊ�ֵ���״
 inRange(frameHSV, cv::Scalar(0, 30, 30), cv::Scalar(40, 170, 256), dstTemp1);
 inRange(frameHSV, cv::Scalar(156, 30, 30), cv::Scalar(180, 170, 256), dstTemp2);
 /*
 inRange(frameHSV, cv::Scalar(0,30,30), cv::Scalar(40,170,256), dstTemp1);
 inRange(frameHSV, cv::Scalar(156,30,30), cv::Scalar(180,170,256), dstTemp2);
 */
 bitwise_or(dstTemp1, dstTemp2, mask);


 // ��̬ѧ������ȥ����������ʹ�ֵı߽��������
 cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
 erode(mask, mask, element);
 morphologyEx(mask, mask, cv::MORPH_OPEN, element);
 dilate(mask, mask, element);
 morphologyEx(mask, mask, cv::MORPH_CLOSE, element);

 frame.copyTo(dst, mask);

 contours.clear();
 hierarchy.clear();
 filterContours.clear();
 // �õ��ֵ�����
 findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
 // ȥ��α����
 int contour_max = -1, countour_SIZE = 0;
 for (size_t i = 0; i < contours.size(); i++)
 {
	 // 			approxPolyDP(cv::Mat(contours[i]), cv::Mat(approxContours[i]), arcLength(cv::Mat(contours[i]), true)*0.02, true);
	 if (fabs(contourArea(cv::Mat(contours[i]))) > 200)	//�ж��ֽ����������ֵ
	 {
		 if (fabs(contourArea(cv::Mat(contours[i]))) > countour_SIZE) {
			 countour_SIZE = contourArea(cv::Mat(contours[i]));
			 contour_max = i;
		 }
		 //cout << fabs(contourArea(cv::Mat(contours[i])))<<endl;
		 filterContours.push_back(contours[i]);
		 //	convexHull(cv::Mat(contours[i]), hull, true);

	 }
 }
 // ������
 drawContours(dst, contours, contour_max, cv::Scalar(0, 0, 255), 3/*, 8, hierarchy*/);
 frame = dst.clone();
 return filterContours[0];
 // �õ�������͹����
}