#include <opencv2/opencv.hpp>

class LiveSketcher
{
  public:
    LiveSketcher(std::string _window_name,cv::Mat image);
    void setEnableDrawing(bool v);
    void setPoint(cv::Point pt);
    void undo();
    void show();
    bool canDraw();
    void drawLines(cv::Point new_point);
    bool canStartLine();
    void addStep();
    void repairImage();

  private:
    static void on_mouse(int event, int x, int y, int flags, void* userdata);
    int slider_value;
    std::string window_name;
    cv::Point prev_point;
    std::vector<std::pair<cv::Mat,cv::Mat>> steps;
    std::pair<cv::Mat,cv::Mat> current;
    cv::Mat repaired;
    bool enableDrawing;
};
