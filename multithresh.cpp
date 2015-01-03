#include <opencv2/opencv.hpp>
#include <iostream>
#include "gui.hpp"

enum Key {
	KEY_ESC = 27
};

using namespace cv;
int main() {
	VideoCapture cam(0);
	Mat image, render;
	ThreshOpts thresh;
	while (cam.isOpened()) {
		cam >> image;
		thresh.render();
		render = thresh.threshold(image);
		imshow("Color", image);
		imshow("Thresholded", render);
		char keypress = waitKey(1);
		if (keypress == KEY_ESC)
			break;
	}
	destroyAllWindows();
}
