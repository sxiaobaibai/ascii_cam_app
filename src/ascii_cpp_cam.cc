#include <ascii_cpp_cam.h>
#include <opencv2/opencv.hpp>
#include <ncurses.h>
#include <unistd.h>

const char *pixel_val = "   :-=+#%@";
std::string ascii_pixel;

void convert_frame_size_color(cv::Mat &frame, double h_scale, double w_scale)
{
  resize(frame, frame, cv::Size(), w_scale, h_scale);
  cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
}

void set_proper_camera_size(int &height, int  &width, int term_height, int term_width)
{
  double aspect_term = term_width / static_cast<double>(term_height);
  double aspect_camera = width * 2.4 / static_cast<double>(height);// Careful: because the height of displayed character is almost 2.4 times larger than width, we need to double width.

  if (aspect_camera > aspect_term)
  {
    width = term_width;
    height = static_cast<int>(width / aspect_camera);
  }
  else
  {
    height = term_height;
    width = static_cast<int>(aspect_camera * height);
  }
}

void AsciiCppCam::draw_ascii()
{
  int height, width;
  int term_height=39, term_width=168;
  int padding_x, padding_y;
  double height_scale, width_scale;
  getmaxyx(stdscr, term_height, term_width);
  cv::Vec3b *src;
  cv::Mat frame;
  int fd, fd2;
  fd = dup(1);
  fd2 = dup(2);
  close(1);
  close(2);
  cv::VideoCapture cap(1);
  dup2(fd,1);
  dup2(fd2,2);

  if (!cap.isOpened())
  {
    std::cerr << "failed to open video device" << std::endl;
    exit(1);
  }

  cap.read(frame);
  height = frame.rows;
  width = frame.cols;

  set_proper_camera_size(height, width, term_height, term_width);//height, width will be updated by this function. the aspect will be kept and the image will be resized so that the image size will be smaller than the size of the terminal
  height_scale = height / static_cast<double>(frame.rows);
  width_scale = width / static_cast<double>(frame.cols);

  padding_y = (term_height - height) / 2;
  padding_x = (term_width - width) / 2;

  char line[width + 1];
  erase();
  refresh();
  while(cap.read(frame))
  {
    if (should_finish_)
      break;
    convert_frame_size_color(frame, height_scale, width_scale);
    erase();
    for (int i = 0; i < height; i++)
    {
      src = frame.ptr<cv::Vec3b>(i);
      for (int j = 0; j < width; j++)
      {
          line[j] = pixel_val[static_cast<int>(src[0][j]) / 26];
      }
      line[width] = '\0';
      move(i + padding_y, padding_x);
      addstr(line);
    }
    refresh();
  }
  erase();
  refresh();
}

void AsciiCppCam::recieve_cmd()
{
  int ch = 0;

  while (1)
  {
    ch = getch();
    if (ch == 'q')
    {
      should_finish_ = true;
      break ;
    }
  }
}

void AsciiCppCam::start_app()
{
  initscr();
  noecho();
  curs_set(0);
  threads_.push_back(std::thread([&](){draw_ascii();}));
  threads_.push_back(std::thread([&](){recieve_cmd();}));
  for (auto &th: threads_)
    th.join();
  endwin();
}
