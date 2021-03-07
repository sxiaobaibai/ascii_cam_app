# ascii_cam_app

This is a camera application using terminal to show the frame(Ascii camera).
It is recommended to use in a splitted terminal window.

## demo
<img src="https://github.com/sxiaobaibai/ascii_cam_app/blob/master/assets/demo.gif?raw=true" width="600px">

## Start
- build the project
```
$ mkdir build
$ cmake ..
$ make
```

- start the camera
$ ./ascii_cpp_cam

- quit the camera
press 'q'

## Todo
- docker
- automatic image size adjustment
- other medias
- network connections

## dependency
- OpenCV(>= 2)
- CMake(>=3.8)
- g++ (>=c++11)
  - pthread
  - vector
  - ncurses
- Mac OS(I am developing this using Mac)
