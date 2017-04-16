#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;

//static void help()
//{
//	cout << "\nThis program demonstrates GrabCut segmentation -- select an object in a region\n"
//		"and then grabcut will attempt to segment it out.\n"
//		"Call:\n"
//		"./grabcut <image_name>\n"
//		"\nSelect a rectangular area around the object you want to segment\n" <<
//		"\nHot keys: \n"
//		"\tESC - quit the program\n"
//		"\tr - restore the original image\n"
//		"\tn - next iteration\n"
//		"\n"
//		"\tleft mouse button - set rectangle\n"
//		"\n"
//		"\tCTRL+left mouse button - set GC_BGD pixels\n"
//		"\tSHIFT+left mouse button - set GC_FGD pixels\n"
//		"\n"
//		"\tCTRL+right mouse button - set GC_PR_BGD pixels\n"
//		"\tSHIFT+right mouse button - set GC_PR_FGD pixels\n" << endl;
//}
//
//const Scalar RED = Scalar(0, 0, 255);
//const Scalar PINK = Scalar(230, 130, 255);
//const Scalar BLUE = Scalar(255, 0, 0);
//const Scalar LIGHTBLUE = Scalar(255, 255, 160);
//const Scalar GREEN = Scalar(0, 255, 0);
//
//const int BGD_KEY = EVENT_FLAG_CTRLKEY;
//const int FGD_KEY = EVENT_FLAG_SHIFTKEY;
//
//static void getBinMask(const Mat& comMask, Mat& binMask)
//{
//	if (comMask.empty() || comMask.type() != CV_8UC1)
//		CV_Error(Error::StsBadArg, "comMask is empty or has incorrect type (not CV_8UC1)");
//	if (binMask.empty() || binMask.rows != comMask.rows || binMask.cols != comMask.cols)
//		binMask.create(comMask.size(), CV_8UC1);
//	binMask = comMask & 1;
//}
//
//class GCApplication
//{
//public:
//	enum { NOT_SET = 0, IN_PROCESS = 1, SET = 2 };
//	static const int radius = 2;
//	static const int thickness = -1;
//
//	void reset();
//	void setImageAndWinName(const Mat& _image, const string& _winName);
//	void showImage() const;
//	void mouseClick(int event, int x, int y, int flags, void* param);
//	int nextIter();
//	int getIterCount() const { return iterCount; }
//private:
//	void setRectInMask();
//	void setLblsInMask(int flags, Point p, bool isPr);
//
//	const string* winName;
//	const Mat* image;
//	Mat mask;
//	Mat bgdModel, fgdModel;
//
//	uchar rectState, lblsState, prLblsState;
//	bool isInitialized;
//
//	Rect rect;
//	vector<Point> fgdPxls, bgdPxls, prFgdPxls, prBgdPxls;
//	int iterCount;
//};
//
//void GCApplication::reset()
//{
//	if (!mask.empty())
//		mask.setTo(Scalar::all(GC_BGD));
//	bgdPxls.clear(); fgdPxls.clear();
//	prBgdPxls.clear();  prFgdPxls.clear();
//
//	isInitialized = false;
//	rectState = NOT_SET;
//	lblsState = NOT_SET;
//	prLblsState = NOT_SET;
//	iterCount = 0;
//}
//
//void GCApplication::setImageAndWinName(const Mat& _image, const string& _winName)
//{
//	if (_image.empty() || _winName.empty())
//		return;
//	image = &_image;
//	winName = &_winName;
//	mask.create(image->size(), CV_8UC1);
//	reset();
//}
//
//void GCApplication::showImage() const
//{
//	if (image->empty() || winName->empty())
//		return;
//
//	Mat res;
//	Mat binMask;
//	if (!isInitialized)
//		image->copyTo(res);
//	else
//	{
//		getBinMask(mask, binMask);
//		image->copyTo(res, binMask);
//	}
//
//	vector<Point>::const_iterator it;
//	for (it = bgdPxls.begin(); it != bgdPxls.end(); ++it)
//		circle(res, *it, radius, BLUE, thickness);
//	for (it = fgdPxls.begin(); it != fgdPxls.end(); ++it)
//		circle(res, *it, radius, RED, thickness);
//	for (it = prBgdPxls.begin(); it != prBgdPxls.end(); ++it)
//		circle(res, *it, radius, LIGHTBLUE, thickness);
//	for (it = prFgdPxls.begin(); it != prFgdPxls.end(); ++it)
//		circle(res, *it, radius, PINK, thickness);
//
//	if (rectState == IN_PROCESS || rectState == SET)
//		rectangle(res, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height), GREEN, 2);
//
//	imshow(*winName, res);
//}
//
//void GCApplication::setRectInMask()
//{
//	CV_Assert(!mask.empty());
//	mask.setTo(GC_BGD);
//	rect.x = max(0, rect.x);
//	rect.y = max(0, rect.y);
//	rect.width = min(rect.width, image->cols - rect.x);
//	rect.height = min(rect.height, image->rows - rect.y);
//	(mask(rect)).setTo(Scalar(GC_PR_FGD));
//}
//
//void GCApplication::setLblsInMask(int flags, Point p, bool isPr)
//{
//	vector<Point> *bpxls, *fpxls;
//	uchar bvalue, fvalue;
//	if (!isPr)
//	{
//		bpxls = &bgdPxls;
//		fpxls = &fgdPxls;
//		bvalue = GC_BGD;
//		fvalue = GC_FGD;
//	}
//	else
//	{
//		bpxls = &prBgdPxls;
//		fpxls = &prFgdPxls;
//		bvalue = GC_PR_BGD;
//		fvalue = GC_PR_FGD;
//	}
//	if (flags & BGD_KEY)
//	{
//		bpxls->push_back(p);
//		circle(mask, p, radius, bvalue, thickness);
//	}
//	if (flags & FGD_KEY)
//	{
//		fpxls->push_back(p);
//		circle(mask, p, radius, fvalue, thickness);
//	}
//}
//
//void GCApplication::mouseClick(int event, int x, int y, int flags, void*)
//{
//	// TODO add bad args check
//	switch (event)
//	{
//	case EVENT_LBUTTONDOWN: // set rect or GC_BGD(GC_FGD) labels
//	{
//		bool isb = (flags & BGD_KEY) != 0,
//			isf = (flags & FGD_KEY) != 0;
//		if (rectState == NOT_SET && !isb && !isf)
//		{
//			rectState = IN_PROCESS;
//			rect = Rect(x, y, 1, 1);
//		}
//		if ((isb || isf) && rectState == SET)
//			lblsState = IN_PROCESS;
//	}
//	break;
//	case EVENT_RBUTTONDOWN: // set GC_PR_BGD(GC_PR_FGD) labels
//	{
//		bool isb = (flags & BGD_KEY) != 0,
//			isf = (flags & FGD_KEY) != 0;
//		if ((isb || isf) && rectState == SET)
//			prLblsState = IN_PROCESS;
//	}
//	break;
//	case EVENT_LBUTTONUP:
//		if (rectState == IN_PROCESS)
//		{
//			rect = Rect(Point(rect.x, rect.y), Point(x, y));
//			rectState = SET;
//			setRectInMask();
//			CV_Assert(bgdPxls.empty() && fgdPxls.empty() && prBgdPxls.empty() && prFgdPxls.empty());
//			showImage();
//		}
//		if (lblsState == IN_PROCESS)
//		{
//			setLblsInMask(flags, Point(x, y), false);
//			lblsState = SET;
//			showImage();
//		}
//		break;
//	case EVENT_RBUTTONUP:
//		if (prLblsState == IN_PROCESS)
//		{
//			setLblsInMask(flags, Point(x, y), true);
//			prLblsState = SET;
//			showImage();
//		}
//		break;
//	case EVENT_MOUSEMOVE:
//		if (rectState == IN_PROCESS)
//		{
//			rect = Rect(Point(rect.x, rect.y), Point(x, y));
//			CV_Assert(bgdPxls.empty() && fgdPxls.empty() && prBgdPxls.empty() && prFgdPxls.empty());
//			showImage();
//		}
//		else if (lblsState == IN_PROCESS)
//		{
//			setLblsInMask(flags, Point(x, y), false);
//			showImage();
//		}
//		else if (prLblsState == IN_PROCESS)
//		{
//			setLblsInMask(flags, Point(x, y), true);
//			showImage();
//		}
//		break;
//	}
//}
//
//int GCApplication::nextIter()
//{
//	if (isInitialized)
//		grabCut(*image, mask, rect, bgdModel, fgdModel, 1);
//	else
//	{
//		if (rectState != SET)
//			return iterCount;
//
//		if (lblsState == SET || prLblsState == SET)
//			grabCut(*image, mask, rect, bgdModel, fgdModel, 1, GC_INIT_WITH_MASK);
//		else
//			grabCut(*image, mask, rect, bgdModel, fgdModel, 1, GC_INIT_WITH_RECT);
//
//		isInitialized = true;
//	}
//	iterCount++;
//
//	bgdPxls.clear(); fgdPxls.clear();
//	prBgdPxls.clear(); prFgdPxls.clear();
//
//	return iterCount;
//}
//
//GCApplication gcapp;
//
//static void on_mouse(int event, int x, int y, int flags, void* param)
//{
//	gcapp.mouseClick(event, x, y, flags, param);
//}
//
//
//
//int main(int argc, char** argv)
//{
//	cv::CommandLineParser parser(argc, argv, "{help h||}{@input|1.bmp|}");
//	if (parser.has("help"))
//	{
//		help();
//		return 0;
//	}
//	string filename = parser.get<string>(0);
//	if (filename.empty())
//	{
//		cout << "\nDurn, empty filename" << endl;
//		return 1;
//	}
//	Mat image = imread(filename, 1);
//	if (image.empty())
//	{
//		cout << "\n Durn, couldn't read image filename " << filename << endl;
//		return 1;
//	}
//
//	help();
//
//	const string winName = "image";
//	namedWindow(winName, WINDOW_AUTOSIZE);
//	setMouseCallback(winName, on_mouse, 0);
//
//	gcapp.setImageAndWinName(image, winName);
//	gcapp.showImage();
//
//	for (;;)
//	{
//		char c = (char)waitKey(0);
//		switch (c)
//		{
//		case '\x1b':
//			cout << "Exiting ..." << endl;
//			goto exit_main;
//		case 'r':
//			cout << endl;
//			gcapp.reset();
//			gcapp.showImage();
//			break;
//		case 'n':
//			int iterCount = gcapp.getIterCount();
//			cout << "<" << iterCount << "... ";
//			int newIterCount = gcapp.nextIter();
//			if (newIterCount > iterCount)
//			{
//				gcapp.showImage();
//				cout << iterCount << ">" << endl;
//			}
//			else
//				cout << "rect must be determined>" << endl;
//			break;
//		}
//	}
//
//exit_main:
//	destroyWindow(winName);
//	return 0;
//}

/*int main() {
	Mat src, dst,dst1,dst2,dst3,dst4;
	src = imread("2.bmp", 0);
	//获得合适的dft变换尺寸
	int m = getOptimalDFTSize(src.rows);
	int n = getOptimalDFTSize(src.cols);
	//将添加的元素初始化为0
	Mat padded;
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols,BORDER_CONSTANT,Scalar::all(0));
	//为实部和虚部分配空间,
	Mat planes[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };
	Mat complexI;
	//2代表输入矩阵的个数
	merge(planes,2, complexI);
	dft(complexI, complexI);

	//分离通道，分别是实部和虚部,并且计算幅值
	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat magnitudeImage = planes[0];

	//进行对数尺度缩放
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);

	//剪切和重分布，奇数行去掉，因为是虚部的
	//数&-2，返回最大的偶数
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols&-2, magnitudeImage.rows&-2));
	//重新排列使得远点位于中心
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy)); //top left
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));//top right
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));//bottom left
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));//bottom right
	//交换象限，便于显示
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//归一化，便于显示
	normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX);
	dst = Mat::zeros(magnitudeImage.size(), magnitudeImage.type());
	int x_center = magnitudeImage.cols / 2;
	int y_center = magnitudeImage.rows / 2;

	//LowPass
	for (int x = 0; x < magnitudeImage.rows; x++) {
		for (int y = 0; y < magnitudeImage.cols; y++) {
			if (sqrt((x - x_center)*(x - x_center) + (y - y_center)*(y - y_center)) <50) {
							dst.at<float>(y, x) = 0;
						}
						else
							dst.at<float>(y, x) =complexI.at<float>(y,x)* magnitudeImage.at<float>(y, x);
			}
		}
	idft(dst, dst4, DFT_REAL_OUTPUT);
	normalize(dst4, dst4, 0, 1, CV_MINMAX);
	//Baterwase
	//通过bat公式可得到，
	dst1 = Mat::zeros(magnitudeImage.size(), magnitudeImage.type());
	for (int x = 0; x < magnitudeImage.rows; x++) {
		for (int y = 0; y < magnitudeImage.cols; y++) {
			int a =sqrt((x - x_center)*(x - x_center) + (y - y_center)*(y - y_center)) / 10;
			float b=1/(1+pow(a, 4));
			//cout << b << endl;
				dst1.at<float>(y, x) =b* magnitudeImage.at<float>(y, x);
				//将32F转化为CV_8U,
				float c = 255 * dst1.at<float>(y, x);
				dst1.at<float>(y, x) = c;
				dst1.convertTo(dst3, CV_8U);
				}
		}
	imshow("yuanyu ", magnitudeImage);
	imshow("CV_8U", dst3);
	imshow(" bate", dst4);
	imshow("低通",dst);
	waitKey(0);
	return 0;
}
*/

int main() {

	Mat src,dst;
	src = imread("3.bmp", 0);
	imshow("原图", src);
	//计算图像的直方图
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float* ranges[1] = { hranges };
	MatND hist;
	calcHist(&src, 1, channels, Mat(), hist, 1, histSize, ranges);
	double maxVal = 0;
	double minVal = 0;

	//找到直方图中的最大值和最小值
	minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	int high = hist.rows;
	Mat histImg(high, high, CV_8U, Scalar(255));
	// 设置最大峰值为图像高度的18倍
	int hpt = static_cast<int>(18 * high);

	//for (int h = 0; h<high; h++)
	//{
	//	float binVal = hist.at<float>(h);
	//	int intensity = static_cast<int>(binVal*hpt / maxVal);
	//	line(histImg, Point(h, high), Point(h, high - intensity), Scalar::all(0));
	//}

	//提取胶囊
	//防止在后面寻找谷底时的误差，对直方图平滑处理
	for (int j = 0; j < 3; j++)
		for (int i = 1; i < high - 1; i++)
		{
			hist.at<float>(i) = (hist.at<float>(i - 1) + hist.at<float>(i) +
				hist.at<float>(i + 1)) / 3;
		}
	
	//显示平均后的直方图
	for (int h = 0;h<high;h++)
	{
	float binVal = hist.at<float>(h);
	int intensity = static_cast<int>(binVal*hpt / maxVal);
	line(histImg, Point(h, high), Point(h, high - intensity), Scalar::all(0));
	}
	imshow("showImage", histImg);
	
	//只有当前像素值的像素个数都小于等于两边时，才被认为谷底。这边取3个像素的宽度
	int count = 0, minPoint, maxPoint;
	for (int i = 3; i < high - 3; i++)
	{
		if (hist.at<float>(i) <= hist.at<float>(i - 3) && hist.at<float>(i) <= hist.at<float>(i - 2) &&
			hist.at<float>(i) <= hist.at<float>(i - 1) && hist.at<float>(i) <= hist.at<float>(i + 1) &&
			hist.at<float>(i) <= hist.at<float>(i + 2) && hist.at<float>(i) <= hist.at<float>(i + 3))
		{
			count++;
			if (count == 1)  //第一个谷底
				minPoint = i;
			else if (count ==5)  //第五个谷底
				maxPoint = i;
		}
	}
	//根据波谷值判断胶囊的显示
	for (int i = 0; i<src.rows; i++)
		for (int j = 0; j < src.cols; j++)
		{
			if (src.at<uchar>(i, j) < minPoint || src.at<uchar>(i, j) > maxPoint)
				src.at<uchar>(i, j) = 255;
		}
	//进行闭运算，去除干扰边界
	Mat element = getStructuringElement(0, Size(3, 3), Point(-1, -1));
	dilate(src, dst, element,Point(-1,-1),5);
	erode(dst, dst, element, Point(-1, -1), 5);
	imshow("", dst);
	waitKey(0);
	return 0;
}