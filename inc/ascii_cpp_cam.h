#ifndef ASCII_CPP_CAM_H
# define ASCII_CPP_CAM_H
#include <iostream>
#include <vector>
#include <thread>

class AsciiCppCam
{
 public:
  AsciiCppCam(int color_range):color_range_(color_range), should_finish_(false){std::cout << "Quantization with " << color_range_ << " bits" << std::endl;};
  void operator ()(){std::cout << "Executing the camera app ... " << std::endl; start_app();};
 private:
  void start_app();
  void recieve_cmd();
  void draw_ascii();

  std::vector<std::thread> threads_;
  const int color_range_;
  bool should_finish_;
};
#endif
