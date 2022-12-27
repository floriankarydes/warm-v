# Where Are My Vines ?

WArM-V is a simple and near real-time image processing pipeline to absorb the data and create a digital twin of one vine row.

## Roadmap

- [x] Create Git project.
- [x] Run OpenCV's [`Hello World` tutorial](https://docs.opencv.org/4.x/db/df5/tutorial_linux_gcc_cmake.html)
- [ ] Run OpenCV's [stitching sample](https://docs.opencv.org/4.x/d8/d19/tutorial_stitcher.html)
- [ ] Build a [stitching pipeline](https://docs.opencv.org/4.x/d1/d46/group__stitching.html) (i.e. registration & compositing).
- [ ] Extract a relationship between posts and vines for the entire dataset.
- [ ] Compute the 1D location in meter of every post and vine along the row with respect to the first asset.

## Knowledge & Tutorials

### Open CV

OpenCV (Open Source Computer Vision) is a free and open-source library of computer vision and machine learning algorithms designed to help developers build computer vision applications. It was originally developed by Intel and is now maintained by a community of developers. OpenCV provides a wide range of tools and functions for image and video processing, including basic image manipulation, feature detection and extraction, object detection and tracking, and machine learning algorithms. It also includes a number of pre-trained models that can be used for tasks such as face detection, object recognition, and image classification. OpenCV is written in C++ and is available for Windows, Linux, and MacOS. It can be used with various programming languages, including Python, C++, and Java.

#### Install on macOS

To build C++ project, a C++ compiler need to be installed. Clang is the default compiler for macOS

```bash
sudo xcode-select --install
```

A proper build system like CMake will also come in handy. CMake is available through [Homebrew](https://brew.sh) package manager

```bash
brew install cmake
```

Open CV's latest release is available on macOS (both Intel & Apple Silicon) through [Homebrew](https://brew.sh) as well

```bash
brew install opencv
brew link opencv
```

If needed, one could always [build from source](https://docs.opencv.org/4.x/d0/db2/tutorial_macos_install.html) instead.

For other platforms, please head to [Open CV's documentation](https://docs.opencv.org/4.x/df/d65/tutorial_table_of_content_introduction.html).

#### Build a first project

- Create `src/DisplayImage.cpp` and `CMakeList.txt` from [OpenCV tutorial](https://docs.opencv.org/4.x/db/df5/tutorial_linux_gcc_cmake.html) with your favorite IDE.

- Build the project with CMake

  ```bash
  cd <path/to/warm-v>
  rm -rf build
  mkdir build
  cd build
  cmake ..
  make
  cd -
  ```

- Test the executable

  ```bash
  ./DisplayImage <path/to/image.jpeg>
  ```

### Image Stitching

- [Open CV's stitching pipeline](https://docs.opencv.org/4.x/d1/d46/group__stitching.html)
- [Open CV's `Stitcher` tutorial](https://docs.opencv.org/4.x/d8/d19/tutorial_stitcher.html)
