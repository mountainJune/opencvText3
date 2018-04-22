#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2\calib3d\calib3d.hpp>
#include<math.h>
using namespace std;
using namespace cv;

//�������ص�3�ַ���
void firstWay(Mat I,uchar table[])
{
	
	//���ͼ��ĳ��λ�õ�rgbֵ
	int channels = I.channels();
	int nRows = I.rows;
	int nCols = I.cols * channels;
	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}
}
void secondWay(Mat I,uchar table[])
{
	
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
			*it = table[*it];
		break;
	}
	case 3:
	{
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
		{
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
	}
	}
}
void thirdWay(Mat I,uchar table[])
{
	
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;
	}
	case 3:
	{
		Mat_<Vec3b> _I = I;
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
			{
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		I = _I;
	}
	}
}
//ͼ��ҶȻ�
void thirdHuidu(Mat I) {
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{

		/*for (int i = 0; i < I.rows; ++i)
		for (int j = 0; j < I.cols; ++j)
		I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;*/
	}
	case 3:
	{
		Mat_<Vec3b> _I = I;
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
			{//ͼ��ҶȻ�  ���ÿ�����ص��R��G,B����������ƽ��ֵ��
			 //Ȼ�����ƽ��ֵ�����������ص���������
				uchar t = (_I(i, j)[0] + _I(i, j)[1] + _I(i, j)[2]) / 3;
				_I(i, j)[0] = t;
				_I(i, j)[1] = t;
				_I(i, j)[2] = t;
			}
		I = _I;
	}
	}

	
}

void bianhuan1(Mat I)
{
	//���ɱ任
	float k;
	float gama;
	cout << "������k��";
	cin >> k;
	cout << "������gama��";
	cin >> gama;
	uchar table[256];
	for (int i = 0; i < 256; ++i)
	{
		float y= k*pow(i, gama);
		if (y > 255)
			table[i] = 255;
		else if (y < 0)
			table[i] = 0;
		else
			table[i] = (uchar)y;
	}
	
	secondWay(I, table);
}
void bianhuan2(Mat I)
{
	int r1,r2,s1,s2;
	cout << "������(r1,s1)��";
	cin >> r1>>s1;
	cout << "������(r2,s2)��";
	cin >> r2>>s2;
	if (r1 > r2&&s1 > s2)
		cout << "shu ru cuo wu " << endl;
	uchar table[256];//�޸�table������ֵ
	for (int i = 0; i < 256; ++i)
	{
		if (i < r1&&i >= 0)
			table[i] = s1 / r1*i;
		else if (i >= r1&&i < r2)
			table[i] = (s2 - s1) / (r2 - r1)*(i - r1) + s1;
		else if (i >= r2&&i <= 255)
			table[i] = (255 - s2) / (255 - r2)*(i - r2) + s2;
	}
		
	secondWay(I, table);//���ڷ���ͼ��Ԫ�ز��޸�

}

int main() {
	
	// ����ͼ��
	const string filename = "input2.jpg";
	Mat srcImg = imread(filename, CV_LOAD_IMAGE_COLOR);
	if (srcImg.empty())
		return -1;
	// ������ʾ����
	
	//��ʾͼ��
	//imshow("ԭͼ", srcImg);
	//waitKey(0);

	//ͼ��ҶȻ�
	thirdHuidu(srcImg);

	Mat dstImg(srcImg.size(), CV_8UC1);
	srcImg.copyTo(dstImg);//�������⿪���µ�ַ
	imshow("ԭͼ", srcImg);
	bianhuan2(dstImg);//���÷����ԻҶȱ任
	imshow("Result", dstImg);
	waitKey(0);




	

	return 0;

}