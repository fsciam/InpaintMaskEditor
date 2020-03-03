#include <opencv2/opencv.hpp>
#include <iostream>

#include "LiveSketcher.h"
int main(int argc, char const *argv[]) {
		if(argc != 2)
		{
			std::cout<<"Usage: p <image-path>";
			return -1;
		}
		cv::Mat image=cv::imread(argv[1]);
		if(!image.empty())
		{
			LiveSketcher sketcher("Original",image);

			while(1)
			{
				char c=cv::waitKey(1);
				if(c == 27)
					break;
				if(c == 122)
					sketcher.undo();
				if(c == 108)
					sketcher.canDraw()?sketcher.setEnableDrawing(false):sketcher.setEnableDrawing(true);
				if(c == 114)
					sketcher.repairImage();

			}
		}
		return 0;
	}
