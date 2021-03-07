#ifndef ASCII_CPP_CAM_H
# define ASCII_CPP_CAM_H
#include <iostream>
#include <vector>
#include <thread>

template<typename T>
struct Frame
{
  //methods
  void resize(int height, int width){height_ = height; width_ = width; val.resize(height*width);};
  T& at(int row, int col){return val.at(row * width_ + col);}

  //data
  std::vector<T> val;
  int height_;
  int width_;
};

class AsciiCppCam
{
 public:
  AsciiCppCam(int color_range):color_range_(color_range), height_(32), width_(100), should_finish_(false){std::cout << "Quantization with " << color_range_ << " bits" << std::endl;};
  void operator ()(){std::cout << "Executing the camera app ... " << std::endl; start_app();};
 private:
  void start_app();
  void recieve_cmd();
  void draw_ascii();

  std::vector<std::thread> threads_;
  const int color_range_;
  size_t height_;
  size_t width_;
  bool should_finish_;

  Frame<char> frame_;
};
#endif
