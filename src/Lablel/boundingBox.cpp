#include <opencv2/opencv.hpp>
// selectROI is part of tracking API
#include <opencv2/tracking.hpp>
#include<iostream>  
#include<fstream>    
#include<string>  
#include<direct.h>
using namespace std;
using namespace cv;
void д��TXT(string ����, string ����, bool �Ƿ񸲸�) {
	ofstream д��(����, �Ƿ񸲸� ? ios::trunc : ios::app);

	if (д��.is_open()) {//����ɹ��Ļ�       
		д�� << ���� << endl;
		д��.close();
	}
}
int main(int argc, char **arv)
{
	fstream ���ļ�;
	string Ŀ¼ = "C:\\Users\\zhumingde\\Desktop\\�ɼ�\\thumb";
	���ļ�.open(Ŀ¼+"\\1.txt");
	_mkdir((Ŀ¼+"\\Crop").c_str());
	// Read image
	while (waitKey(30) != 27&& !���ļ�.eof()) {

			string ����Ķ���;
			���ļ� >> ����Ķ���;
			if (����Ķ���.empty())break;
			д��TXT(Ŀ¼+"\\Rect.txt", ����Ķ���, 0);

		Mat im = imread(Ŀ¼ + "\\"+����Ķ���);

		// Select ROI
		bool showCrosshair = false;
		bool fromCenter = false;
		Rect2d r = selectROI("Image", im, fromCenter, showCrosshair);
		cout << r.x << " " << r.y << " " << r.width << " " << r.height << endl;
		// Crop image
		Mat imCrop = im(r);
		string temp = to_string(int(r.x)) + " " + to_string(int(r.y)) + " " + to_string(int(r.width)) + " " + to_string(int(r.height));
		д��TXT(Ŀ¼ + "\\Rect.txt", temp, 0);
		// Display Cropped Image
		imshow("Image_crop", imCrop);
		imwrite(Ŀ¼ + "\\crop\\" + ����Ķ���, imCrop);
		//waitKey(0);
	}
	���ļ�.close();//�ر��Ǹ���ϰ��  

	return 0;
}

