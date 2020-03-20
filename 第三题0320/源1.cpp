#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat bi;
	Mat labels, stats, centroids;
	Mat frmMat = imread("2.jpg", 0);
	//前景背景换颜色
	cv::bitwise_not(frmMat, frmMat);
	//大津法
	Mat dst;
	threshold(frmMat, dst, 0, 255, CV_THRESH_OTSU);
	//闭运算
	Mat element = getStructuringElement(MORPH_RECT, Size(9,9));
	morphologyEx(dst, bi, MORPH_OPEN, element);
	//连通域计算      
	int nccomps = connectedComponentsWithStats(
		bi, //处理后的图像
		labels,//和原图一样大的标记图
		stats,  //nccomps×5的矩阵 表示每个连通区域的外接矩形和面积（pixel）            
		centroids,//nccomps×2的矩阵 表示每个连通区域的质心          
		8,
		CV_32S);

	for (int i = 0; i < nccomps; i++)
	{
		//各个连通域的统计信息保存在stasMat中
		cout << "连通域NO. " << i << endl;
		cout << "像素= " << stats.at<int>(i, 4) << endl;
		cout << "宽= " << stats.at<int>(i, 2) << endl;
		cout << "高 = " << stats.at<int>(i, 3) << endl;
		cout << endl;
	}
	char title[1024];
	sprintf_s(title, "原图中连通区域数：%d\n", nccomps);
	String num_connect(title);
	imshow(num_connect, bi);

	//画出bounding box

	for (int i = 1; i <nccomps; i++)
	{

		char num[99];
		sprintf_s(num, "%d", i);

		Rect boundingbox;
		//bounding box左上角坐标
		boundingbox.x = stats.at<int>(i, 0);
		boundingbox.y = stats.at<int>(i, 1);
		//bouding box的宽和长 
		boundingbox.width = stats.at<int>(i, 2);
		boundingbox.height = stats.at<int>(i, 3);
		//绘制
		rectangle(bi, boundingbox, CV_RGB(0, 255, 155), 2, 8, 0);
	}
	imshow("result", bi);

	waitKey(0);
	return 0;
}