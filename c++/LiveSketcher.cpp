#include "LiveSketcher.h"

void LiveSketcher::on_mouse(int event, int x, int y, int flags, void* userdata)
{
  LiveSketcher * sketcher=(LiveSketcher *) userdata;
  cv::Point pt(x, y);
  if (event == cv::EVENT_LBUTTONDOWN && sketcher->canDraw())
  {
    if (!sketcher->canStartLine())
    {
      std::cout<<"Saving"<<std::endl;
      sketcher->addStep();
    }
    sketcher->setPoint(pt);
  }
  else if (event == cv::EVENT_LBUTTONUP)
      sketcher->setPoint(cv::Point(-1,-1));



  if (sketcher->canStartLine() && (flags & cv::EVENT_FLAG_LBUTTON))
  {
    sketcher->drawLines(pt);
    sketcher->show();
  }
}
LiveSketcher::LiveSketcher(std::string _window_name,cv::Mat image)
{
  window_name=_window_name;
  current=std::make_pair(image.clone(),cv::Mat(image.size(), CV_8UC1));
  prev_point=cv::Point(-1,-1);
  enableDrawing=false;
  slider_value=2;
  show();
  cv::setMouseCallback(window_name,&LiveSketcher::on_mouse,this);
  cv::createTrackbar("Line width",window_name,&slider_value,20,NULL);

}
void LiveSketcher::undo()
{

  if(!steps.empty())
  {
    std::cout << "Undoing" << '\n';
    current=steps.back();
    steps.pop_back();
    show();
  }
}
void LiveSketcher::setEnableDrawing(bool v)
{
  enableDrawing=v;
}
void LiveSketcher::setPoint(cv::Point pt)
{
  prev_point=pt;
}
bool LiveSketcher::canDraw()
{
  return enableDrawing;
}

bool LiveSketcher::canStartLine()
{
  return prev_point.x>=0;
}

void LiveSketcher::drawLines(cv::Point new_point)
{
  cv::line(current.first, prev_point, new_point, cv::Scalar(255,255,255), slider_value);
  cv::line(current.second, prev_point, new_point, cv::Scalar(255,255,255), slider_value);

  prev_point = new_point;
  show();
}
void LiveSketcher::show()
{
  cv::imshow(window_name,current.first);
}
void LiveSketcher::addStep()
{
  steps.push_back(std::make_pair(current.first.clone(),current.second.clone()));
}

void LiveSketcher::repairImage()
{
  cv::inpaint(current.first,current.second,repaired,3, cv::INPAINT_TELEA);
  cv::imshow("Repaired",repaired);
}
