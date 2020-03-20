#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat bi;
	Mat labels, stats, centroids;
	Mat frmMat = imread("2.jpg", 0);
	//ǰ����������ɫ
	cv::bitwise_not(frmMat, frmMat);
	//���
	Mat dst;
	threshold(frmMat, dst, 0, 255, CV_THRESH_OTSU);
	//������
	Mat element = getStructuringElement(MORPH_RECT, Size(9,9));
	morphologyEx(dst, bi, MORPH_OPEN, element);
	//��ͨ�����      
	int nccomps = connectedComponentsWithStats(
		bi, //������ͼ��
		labels,//��ԭͼһ����ı��ͼ
		stats,  //nccomps��5�ľ��� ��ʾÿ����ͨ�������Ӿ��κ������pixel��            
		centroids,//nccomps��2�ľ��� ��ʾÿ����ͨ���������          
		8,
		CV_32S);

	for (int i = 0; i < nccomps; i++)
	{
		//������ͨ���ͳ����Ϣ������stasMat��
		cout << "��ͨ��NO. " << i << endl;
		cout << "����= " << stats.at<int>(i, 4) << endl;
		cout << "��= " << stats.at<int>(i, 2) << endl;
		cout << "�� = " << stats.at<int>(i, 3) << endl;
		cout << endl;
	}
	char title[1024];
	sprintf_s(title, "ԭͼ����ͨ��������%d\n", nccomps);
	String num_connect(title);
	imshow(num_connect, bi);

	//����bounding box

	for (int i = 1; i <nccomps; i++)
	{

		char num[99];
		sprintf_s(num, "%d", i);

		Rect boundingbox;
		//bounding box���Ͻ�����
		boundingbox.x = stats.at<int>(i, 0);
		boundingbox.y = stats.at<int>(i, 1);
		//bouding box�Ŀ�ͳ� 
		boundingbox.width = stats.at<int>(i, 2);
		boundingbox.height = stats.at<int>(i, 3);
		//����
		rectangle(bi, boundingbox, CV_RGB(0, 255, 155), 2, 8, 0);
	}
	imshow("result", bi);

	waitKey(0);
	return 0;
}