# Where Are My Vines ?

:warning: This is a work in progress. :warning:

WArM-V is a simple and near real-time image processing pipeline to absorb the data and create a digital twin of one vine row.

## Roadmap

- [x] Get started with [Open CV](https://opencv.org) and the [stitching sample](https://docs.opencv.org/4.x/d8/d19/tutorial_stitcher.html)
- [ ] Design a pipeline to absorb the data and create a digital twin of the vine row.
- [ ] Build a [stitching pipeline](https://docs.opencv.org/4.x/d1/d46/group__stitching.html) (i.e. registration & compositing) for vineyard images.
- [ ] Extract a relationship between posts and vines for the entire dataset.
- [ ] Compute the 1D location in meter of every post and vine along the row with respect to the first asset.

## Design

**TODO**

## Getting Started

### Prerequisites

To build this project, you will need

- a C++ compiler
- [CMake](https://cmake.org) build system.
- [OpenCV](https://opencv.org)

#### Install on macOS

> [Homebrew](https://brew.sh) package manager is used to easily install & manage software on macOS.

```bash
sudo xcode-select --install
brew install cmake
brew install opencv
brew link opencv
```

If needed, one could always [build from source](https://docs.opencv.org/4.x/d0/db2/tutorial_macos_install.html) instead.

For other platforms, please head to [Open CV's documentation](https://docs.opencv.org/4.x/df/d65/tutorial_table_of_content_introduction.html).

### Build

- Create `src/DisplayImage.cpp` and `CMakeList.txt` from [OpenCV tutorial](https://docs.opencv.org/4.x/db/df5/tutorial_linux_gcc_cmake.html) with your favorite IDE.

- Build the project

  ```bash
  cd <path/to/warm-v>
  rm -rf build
  mkdir build
  cd build
  cmake ..
  make
  cd -
  ```

### Run

- Create directory structure for dataset & stitching result

  ```bash
  cd <path/to/warm-v>
  mkdir -p data/inputs
  mkdir -p data/outputs

- Get some images to stitch from [OpenCV dataset](https://github.com/opencv/opencv_extra/tree/4.x/testdata/stitching) and put them in `inputs` directory.

- Run one stitching pipeline

  ```bash
  ./script/stitching_detailed.bash
  ```

- Have a look at the stitched image `stitching_result.jpeg`.

## Going Further

- [Open CV's stitching pipeline](https://docs.opencv.org/4.x/d1/d46/group__stitching.html)
- [Open CV's `Stitcher` tutorial](https://docs.opencv.org/4.x/d8/d19/tutorial_stitcher.html)
