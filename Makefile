all: multithresh
%: %.cpp
	$(CXX) -g -Wall -std=c++11 $^ -lopencv_core -lopencv_imgproc -lopencv_highgui -o $@
