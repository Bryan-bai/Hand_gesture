

#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>
#include <iostream>
#include <fstream>
#include "dlib\image_io.h"
#include<opencv2/opencv.hpp>


using namespace std;
using namespace dlib;

// ----------------------------------------------------------------------------------------
static cv::Rect dlibRectangleToOpenCV(dlib::rectangle r)
{
	return cv::Rect(cv::Point2i(r.left(), r.top()), cv::Point2i(r.right() + 1, r.bottom() + 1));
}
static dlib::rectangle openCVRectToDlib(cv::Rect r)
{
	return dlib::rectangle((long)r.tl().x, (long)r.tl().y, (long)r.br().x - 1, (long)r.br().y - 1);
}
int main(int argc, char** argv)
{

	try
	{
		//һ��preprocessing
		//1. ����ѵ���������Լ�
		const std::string faces_directory = "C:\\Users\\zhumingde\\Desktop\\�ɼ�\\thumb\\";
		const std::string test_directory = "C:\\Users\\zhumingde\\Desktop\\�ɼ�\\palm\\";
		dlib::array<array2d<unsigned char> > images_train, images_test;
		std::vector<std::vector<rectangle> > face_boxes_train, face_boxes_test;

		load_image_dataset(images_train, face_boxes_train, faces_directory + "train.xml");
		load_image_dataset(images_test, face_boxes_test, test_directory + "train.xml");
		/*
		double ���� = 2;
		for (auto&reclist : face_boxes_train)
		{
			for (auto&rec : reclist)
			{
				cv::Rect temp = dlibRectangleToOpenCV(rec);
				temp.width *= ����;
				temp.height *= ����;
				rec = openCVRectToDlib(temp);
			}
		}*/

		//2.ͼƬ�ϲ���
		upsample_image_dataset<pyramid_down<8> >(images_train, face_boxes_train);
		upsample_image_dataset<pyramid_down<8> >(images_test, face_boxes_test);

		//3.ѵ��ͼƬ������������ѵ����
		//add_image_left_right_flips(images_train, face_boxes_train);

		//����training
		//1.����scanner���ͣ�����ɨ��ͼƬ����ȡ������HOG��
		typedef scan_fhog_pyramid<pyramid_down<8> > image_scanner_type;
		image_scanner_type scanner;

		//2. ����scannerɨ�贰�ڴ�С
		scanner.set_detection_window_size(40,64);
		
		//scanner.set_cell_size(5);
		//3.����trainer���ͣ�SVM��������ѵ�������                
		structural_object_detection_trainer<image_scanner_type> trainer(scanner);
		// Set this to the number of processing cores on your machine.
		trainer.set_num_threads(4);
		// ����SVM�Ĳ���C��CԽ���ʾ���õ�ȥ���ѵ��������ȻҲ�п�����ɹ���ϡ�ͨ�����Բ�ͬC�ڲ��Լ��ϵ�Ч���õ����ֵ
		trainer.set_c(20);
		trainer.be_verbose();
		//����ѵ������������"risk gap"<0.01ʱѵ��������ֵԽС��ʾSVM�Ż�����Խ��ȷ��ѵ��ʱ��Ҳ��Խ�á�
		//ͨ��ȡ0.1-0.01.��verboseģʽ��ÿһ�ֵ�risk gap�����ӡ������
		trainer.set_epsilon(0.01);

		//4.ѵ��������object_detector
		object_detector<image_scanner_type> detector = trainer.train(images_train, face_boxes_train);

		//��������
		// ���precision, recall, average precision.
		cout << "training results: " << test_object_detection_function(detector, images_train, face_boxes_train) << endl;
		cout << "testing results:  " << test_object_detection_function(detector, images_test, face_boxes_test) << endl;

		//��ʾhog
		image_window hogwin(draw_fhog(detector), "Learned fHOG detector");



		//�ġ�ģ�ʹ洢
		serialize(faces_directory+"jieguo.svm") << detector;
		// you can recall it using the deserialize() function.
	//	object_detector<image_scanner_type> detector2;
	//	deserialize("face_detector.svm") >> detector2;
		// ��ʾ���Լ������������
		image_window win;
		for (unsigned long i = 0; i < images_test.size(); ++i)
		{
			// Run the detector and get the face detections.
			std::vector<rectangle> dets = detector(images_test[i]);
			win.clear_overlay();
			win.set_image(images_test[i]);
			win.add_overlay(dets, rgb_pixel(255, 0, 0));
			cout << "Hit enter to process the next image..." << endl;
			cin.get();
		}

	}
	catch (exception& e)
	{
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
		cout << 233;
		system("pause");
	}
}