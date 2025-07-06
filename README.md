# QtImageEditor
A Qt-based desktop application for image editing, featuring various filters, histogram analysis, and a convenient before-and-after comparison view. This project was developed as part of my Electrical Engineering and Information Technology studies, providing practical experience in software development with Qt and image processing.

## Features

- **Load and save images:** Supports common formats like PNG, JPG, and BMP.
- **Apply filters:** Enhance or modify images with a selection of filters including:
    - Brightness (with adjustable intensity)
    - Sepia
    - Gaussian Blur (with adjustable radius)
    - Negative
- **Before/after comparison:** Easily visualize the effects of applied changes.
- **RGB histograms:** Analyze image color distribution through interactive histograms.
- **Unit-tested core components:** Ensures reliability and robustness of key functionalities.

## Architecture Overview

- Clean separation between GUI and logic
- Singleton pattern used for image storage
- Modular filter classes using polymorphism
- Dedicated `ImageProcessor` for applying filters
- Full unit test coverage for core modules

## Technologies Used

- **C++17**
- **Qt 6**
- **QImage** for image handling
- **QCustomPlot** for histogram
- **QTest** for unit testing
- **qmake**

## Running Tests and Build Instructions

### Building and Running Tests with Qt Creator (Recommended)

1. Open the file `test_PhotoViewerPro.pro` in **Qt Creator**.
2. Select an appropriate build kit (e.g., MinGW, MSVC).
3. Click **Build** to compile the test project.
4. Click **Run** to execute the tests.

## Build Instructions

Using Qt Creator:

1. Clone this repo
2. Open the file `PhotoViewerPro.pro` in **Qt Creator**
3. Build and run

## License

This Project is licensed under the MIT License - see LICENSE.md for details.