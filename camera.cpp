#include <opencv2/opencv.hpp>
//#include <Windows.h>
using namespace cv;
using namespace std;
//using std::thread;

VideoCapture  capture(0);
Mat frame; //영상 출력용 MAT 행렬

int width = capture.get(CAP_PROP_FRAME_WIDTH);
int height = capture.get(CAP_PROP_FRAME_HEIGHT);

Rect focus(Point(0, 300), Point(640, 480));

Rect pia1(Point(0, 0), Point(90, 180)); Rect pia2(Point(90, 0), Point(180, 180)); Rect pia3(Point(180, 0), Point(270, 180));
Rect pia4(Point(270, 0), Point(370, 180)); Rect pia5(Point(370, 0), Point(460, 180)); Rect pia6(Point(460, 0), Point(550, 180));
Rect pia7(Point(550, 0), Point(640, 180));
//피아노 7구역 나누기 위한 Rect

Mat old_frame;
Mat gray_frame;
Mat sub_frame;

Mat newF[7];
int countMaxSub[7];
int maxPiano;

// 문자열 출력 함수 - 그림자 효과 
void put_string(Mat& frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);		// 그림자 효과 	
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);// 작성 문자
}


int main()
{
	if (!capture.isOpened())
	{
		cout << "카메라가 연결되지 않았습니다." << endl;
		exit(1);
	}

	capture.read(frame);
	capture.set(3, 640);
	capture.set(4, 480);

	for (;;) {
		capture.read(frame);

		flip(frame, frame, 1);
		Mat focusframe = frame(focus); //영역 지정하기
		put_string(frame, "EXPOS: ", Point(10, 40), capture.get(CAP_PROP_EXPOSURE));
		//focusframe += Scalar(0, 50, 0);
		//rectangle(focusframe, Point(0, 0), Point(640, 480), Scalar(0, 0, 255), 3);
		rectangle(focusframe, pia1, Scalar(0, 0, 255));
		rectangle(focusframe, pia2, Scalar(0, 0, 255));
		rectangle(focusframe, pia3, Scalar(0, 0, 255));
		rectangle(focusframe, pia4, Scalar(0, 0, 255));
		rectangle(focusframe, pia5, Scalar(0, 0, 255));
		rectangle(focusframe, pia6, Scalar(0, 0, 255));
		rectangle(focusframe, pia7, Scalar(0, 0, 255));

		cvtColor(focusframe, gray_frame, COLOR_BGR2GRAY);

		if (old_frame.empty()) {
			old_frame = gray_frame.clone();
			continue;
		}

		subtract(old_frame, gray_frame, sub_frame);
		threshold(sub_frame, sub_frame, 50, 255, THRESH_BINARY);

		newF[0] = sub_frame(pia1);
		newF[1] = sub_frame(pia2);
		newF[2] = sub_frame(pia3);
		newF[3] = sub_frame(pia4);
		newF[4] = sub_frame(pia5);
		newF[5] = sub_frame(pia6);
		newF[6] = sub_frame(pia7);

		countMaxSub[0] = countNonZero(newF[0]);
		countMaxSub[1] = countNonZero(newF[1]);
		countMaxSub[2] = countNonZero(newF[2]);
		countMaxSub[3] = countNonZero(newF[3]);
		countMaxSub[4] = countNonZero(newF[4]);
		countMaxSub[5] = countNonZero(newF[5]);
		countMaxSub[6] = countNonZero(newF[6]);

		imshow("카메라 영상보기", frame);
		//imshow("old_frame", old_frame);
		imshow("차영상", sub_frame);
		//imshow("gray", gray_frame);
		old_frame = gray_frame.clone();

		if (waitKey(30) >= 0) break; //esc break
	}

	return 0;
}