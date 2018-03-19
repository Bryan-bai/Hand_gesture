#include "RegionGrow.h"

cv::Mat RegionGrow(cv::Mat src, cv::Point2i pt, int R, int G, int B, bool isornot)
{
	cv::Point2i ptGrowing;                      //��������λ��  
	int nGrowLable = 0;                             //����Ƿ�������  
	std::vector<int> nSrcValue = { 0,0,0 };                             //�������Ҷ�ֵ  
	std::vector<int> nCurValue = { 0,0,0 };                              //��ǰ������Ҷ�ֵ  
	cv::Mat matDst = cv::Mat::zeros(src.size(), CV_8UC1);   //����һ���հ��������Ϊ��ɫ  
													//��������˳������  
	int DIR[8][2] = { { 0,-1 },{ 0,1 },{ 1,0 },{ -1,0 },{ 1,1 },{ -1,1 },{ -1,-1 },{ 1,-1 } };
	//{ { -1,-1 },{ 0,-1 },{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 } };
	std::vector<cv::Point2i> vcGrowPt;                     //������ջ  
	vcGrowPt.push_back(pt);                         //��������ѹ��ջ��  
	matDst.at<uchar>(pt.y, pt.x) = 255;               //���������  
	for (int i = 0; i < 3; ++i)
		nSrcValue[i] = src.at<cv::Vec3b>(pt.y, pt.x)[i];
	while (!vcGrowPt.empty())                       //����ջ��Ϊ��������  
	{
		pt = vcGrowPt.back();                       //ȡ��һ��������  
		vcGrowPt.pop_back();

		//�ֱ�԰˸������ϵĵ��������  
		for (int i = 0; i<4; ++i)
		{
			ptGrowing.x = pt.x + DIR[i][0];
			ptGrowing.y = pt.y + DIR[i][1];
			//����Ƿ��Ǳ�Ե��  
			if (ptGrowing.x < 0 || ptGrowing.y < 0 || ptGrowing.x >(src.cols - 1) || (ptGrowing.y > src.rows - 1))
				continue;

			nGrowLable = matDst.at<uchar>(ptGrowing.y, ptGrowing.x);      //��ǰ��������ĻҶ�ֵ  

			if (nGrowLable == 0)                    //�����ǵ㻹û�б�����  
			{
				for (int i = 0; i<3; ++i)
					nCurValue[i] = src.at<cv::Vec3b>(pt.y, pt.x)[i];

				if (isornot) {
					if ((abs(nSrcValue[0] - nCurValue[0]) < R) &&
						(abs(nSrcValue[1] - nCurValue[1]) < G) &&
						(abs(nSrcValue[2] - nCurValue[2]) < B)
						)                 //����ֵ��Χ��������  
					{
						matDst.at<uchar>(ptGrowing.y, ptGrowing.x) = 255;     //���Ϊ��ɫ  
						vcGrowPt.push_back(ptGrowing);                  //����һ��������ѹ��ջ��  
					}
				}
				else {
					if ((abs(nSrcValue[0] - nCurValue[0]) < R) ||
						(abs(nSrcValue[1] - nCurValue[1]) < G) ||
						(abs(nSrcValue[2] - nCurValue[2]) < B)
						)                 //����ֵ��Χ��������  
					{
						matDst.at<uchar>(ptGrowing.y, ptGrowing.x) = 255;     //���Ϊ��ɫ  
						vcGrowPt.push_back(ptGrowing);                  //����һ��������ѹ��ջ��  
					}
				}

			}
		}
	}
	return matDst.clone();
}
