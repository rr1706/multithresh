#include <fstream>
using namespace cv;
using namespace std;
enum Operation {
	OP_OR = 0,
	OP_AND
};
class ThreshOpts {
private:
	int hue_min, hue_max, sat_min, sat_max, val_min, val_max;
	int r_min, r_max, g_min, g_max, b_min, b_max;
	int operation;
	std::string dataFile;
public:
	ThreshOpts(std::string dataFile = "multithresh.conf") : dataFile(dataFile) {
		ifstream data(dataFile);
		hue_min = 0;
		hue_max = 255;
		sat_min = 0;
		sat_max = 255;
		val_min = 0;
		val_max = 255;
		r_min = 0;
		r_max = 255;
		g_min = 0;
		g_max = 255;
		b_min = 0;
		b_max = 255;
		operation = OP_AND;
		if (data.is_open()) {
			data >> hue_min;
			data >> hue_max;
			data >> sat_min;
			data >> sat_max;
			data >> val_min;
			data >> val_max;
			data >> r_min;
			data >> r_max;
			data >> g_min;
			data >> g_max;
			data >> b_min;
			data >> b_max;
			data >> operation;
			data.close();
		}
		namedWindow("Options", CV_WINDOW_AUTOSIZE);
	}
	~ThreshOpts() {
		ofstream data(dataFile);
		if (data.is_open()) {
			data << hue_min;
			data << " ";
			data << hue_max;
			data << " ";
			data << sat_min;
			data << " ";
			data << sat_max;
			data << " ";
			data << val_min;
			data << " ";
			data << val_max;
			data << " ";
			data << r_min;
			data << " ";
			data << r_max;
			data << " ";
			data << g_min;
			data << " ";
			data << g_max;
			data << " ";
			data << b_min;
			data << " ";
			data << b_max;
			data << " ";
			data << operation;
			data << "\n";
			data.close();
		}
		destroyWindow("Options");
	}
	void render() {
		createTrackbar("Hue Min", "Options", &hue_min, 255, 0);
		createTrackbar("Hue Max", "Options", &hue_max, 255, 0);
		createTrackbar("Sat Min", "Options", &sat_min, 255, 0);
		createTrackbar("Sat Max", "Options", &sat_max, 255, 0);
		createTrackbar("Val Min", "Options", &val_min, 255, 0);
		createTrackbar("Val Max", "Options", &val_max, 255, 0);
		createTrackbar("R Min", "Options", &r_min, 255, 0);
		createTrackbar("R Max", "Options", &r_max, 255, 0);
		createTrackbar("G Min", "Options", &g_min, 255, 0);
		createTrackbar("G Max", "Options", &g_max, 255, 0);
		createTrackbar("B Min", "Options", &b_min, 255, 0);
		createTrackbar("B Max", "Options", &b_max, 255, 0);
		createTrackbar("Operation", "Options", &operation, 1, 0);
	}
	Mat threshold(Mat input) {
		Mat rgb, hsv, rgbBinary, hsvBinary, output;
		cvtColor(input, rgb, CV_BGR2RGB);
		cvtColor(input, hsv, CV_BGR2HSV);
		inRange(rgb, Scalar(r_min, g_min, b_min), Scalar(r_max, g_max, b_max), rgbBinary);
		inRange(hsv, Scalar(hue_min, sat_min, val_min), Scalar(hue_max, sat_max, val_max), hsvBinary);
		if (operation == OP_OR) {
			output = rgbBinary | hsvBinary;
		} else {
			output = rgbBinary & hsvBinary;
		}
		return output;
	}
	
};
