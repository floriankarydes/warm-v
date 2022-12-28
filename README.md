<h1 align="center">
  <img width="25%" style="margin: 1em" src="./doc/images/project_logo.svg" alt="Project logo">
  <p>Where Are My Vines ?</p>
</h1>

<p align="center">⚠️ This is a work in progress. ⚠️</p>

WArM-V is an image processing pipeline to absorb photos collected in vineyards to create a digital twin of **one** vine row. The data is processed in near real-time on the edge to reduce the amount of data to upload to the cloud, where the entire vineyard model is updated and analyzed.

## Roadmap

- [x] Design a high-level pipeline to absorb the data and create a digital twin of the vine row.
- [x] Get started with [Open CV](https://opencv.org) and the [stitching sample](https://docs.opencv.org/4.x/d8/d19/tutorial_stitcher.html)
- [ ] Build a first [stitching pipeline](https://docs.opencv.org/4.x/d1/d46/group__stitching.html) (i.e. image registration & compositing) for vineyard images.
- [ ] Develop the designed processing pipeline.

## Design

### High-level Overview

Below is a workflow diagram describing WArM-V image processing pipeline to achieve online estimation of post & trunks positions. An additional pipeline to generate a human-readable preview of the pipeline result is also presented.

<p align="center">
  <img width="90%" src="./doc/images/design_overview.svg" alt="High-level workflow">
</p>

#### Cameras Isolation

The pipeline in the diagram above is duplicated for each camera. In particular, each camera pipeline is completely independent and can easily run in parallel. If enough computing resources are available, this enables for better runtime performances.

Of course, we could gain precision on position estimates by sharing [state estimation](#state-estimation) across pipelines. But complete isolation between pipelines reduce design complexity and increase the overall robustness of the system (one camera or pipeline failure do not impact the other camera work).

#### Pipeline Multithreading

The pipeline itself can be parallelized. As depicted on the diagram, the state estimation, the image alignment and the object detection can mostly run in parallel.

Actually, it can start processing a new image before having fully processed the previous one. In particular, there is only three synchronization constraint (i.e. wait for last image related step to be completed) :

- Image alignment step must wait for previous image to be available in the database (this should always be true anyway)
- State estimator must wait for last step estimate to be refined with computer vision data.
- Duplicate merger must wait for previous image duplicate to be removed.

### Image Alignment

Image alignment, also known as image registration, is the process of aligning two or more images of the same scene taken at different times, from different viewpoints, or using different sensors. Image alignment is often used to combine multiple images into a single composite image, or to compare images to identify changes or differences.

In this project, image alignment is used to estimate the relative position of the object detected is different images. There are several techniques for aligning images. Based on the nature of the images and the goals of the alignment process, feature-based alignment seems like a good option. This method involves identifying features in the images, such as corners or edges, and using these features to determine the transformation needed to align the images. This transformation is called homography.

In particular, for each new image captured by the camera, the pipeline estimates the homography with respect to the previous image with the following steps :

1. **Resize images** : reduce the two images size to reduce the computation cost of the following steps.
2. **Find features** : detect features in the two images using [SURF](https://medium.com/data-breach/introduction-to-surf-speeded-up-robust-features-c7396d6e7c4e) (Speeded up robust features) algorithm.
3. **Match features** : finds two best matches for each feature and leaves the best one only if the
ratio between descriptor distances is greater than a confidence threshold.
4. **Guess homography** : make a first guess of the homography from previous image to new image based on the camera state estimate (i.e. GPS readings, kinematics integration and previous camera parameters).
5. **Estimate homography** : starting from the guess, use pairwise matches in images to estimate the homography & camera parameters (camera parameters are used to pass from camera states to homography).

### State Estimation

[State estimation](https://en.wikipedia.org/wiki/State_observer) can help increase the quality of the image alignment by providing a first guess on the homography to initialize the algorithm.

State estimation is the process of estimating the current state of a system, based on a set of measurements or observations. It is a common problem in many fields, including control systems, robotics, and signal processing. In this project, the states of interest here would be the relative position & orientation of the camera with respect to its initial state (i.e. state at the first capture). On each new capture, the state estimator fuses the new GPS measurement with the expected state of the model to provide a new state estimate. This allows to account for change in velocity of the tractor & filter out GPS errors.

Expected state is obtained by updating a state model over time. A simplistic state model for the tractor can be design as follows

- Camera moves on a straight axis parallel to the vine row vertical plane and included in the camera horizontal plane.
- Virtual kinetic friction force is applied so that linear velocity cannot go above 1 m/s.

Note that mounting a (very cheap) MEMS-based IMU (Microelectromechanical Systems based Inertial Measurement Unit) could help us estimate the full 6DoF state of the tractor. This would greatly improve the quality of the estimate and alleviate the need for the above assumptions. This would also support multi-rows positioning.

## Getting Started

> The design above has not been implemented. The following are just artifacts of my first experiments with Open CV.

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

- Move to the project directory

  ```bash
  cd <path/to/warm-v>
  ```

- If needed, create a `build` directory. You can optionally remove old build artifacts.

  ```bash
  rm -rf build
  mkdir -p build
  ```

- Build the project

  ```bash
  cd build
  cmake ..
  make
  cd -
  ```

### Run

- Move to the project directory

  ```bash
  cd <path/to/warm-v>
  ```

- Create directory structure for dataset & stitching result

  ```bash
  mkdir -p data/inputs
  mkdir -p data/outputs

- Get some images to stitch from [OpenCV dataset](https://github.com/opencv/opencv_extra/tree/4.x/testdata/stitching) and put them in `inputs` directory.

  ```bash
  cd data/inputs
  wget https://github.com/opencv/opencv_extra/raw/4.x/testdata/stitching/boat1.jpg
  wget https://github.com/opencv/opencv_extra/raw/4.x/testdata/stitching/boat2.jpg
  wget https://github.com/opencv/opencv_extra/raw/4.x/testdata/stitching/boat3.jpg
  wget https://github.com/opencv/opencv_extra/raw/4.x/testdata/stitching/boat4.jpg
  wget https://github.com/opencv/opencv_extra/raw/4.x/testdata/stitching/boat5.jpg
  wget https://github.com/opencv/opencv_extra/raw/4.x/testdata/stitching/boat6.jpg
  cd -
  ```

- Run the stitching pipeline

  ```bash
  ./script/stitching_detailed.bash
  ```

- Have a look at the stitched image `data/outputs/stitching_result.jpeg`.

### Going Further

- [Open CV's stitching pipeline](https://docs.opencv.org/4.x/d1/d46/group__stitching.html)
- [Open CV's `Stitcher` tutorial](https://docs.opencv.org/4.x/d8/d19/tutorial_stitcher.html)
