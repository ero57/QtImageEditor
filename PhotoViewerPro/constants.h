#ifndef CONSTANTS_H
#define CONSTANTS_H


// --- extra header for constants ---


// --- VALUES ---
constexpr int START_VALUE = 0;
constexpr int MIN_COLOR_VALUE = 0;
constexpr int MAX_COLOR_VALUE = 255;
constexpr int MIN_BRIGHTNESS = -100;
constexpr int MAX_BRIGHTNESS = 100;
constexpr int MAX_BLUR_GRAIN = 10;        // radius of blur matrix
constexpr int MAX_SEPIA_STRENGTH = 100;

// --- LAYOUT AND WINDOWS ---
constexpr int INIT_WINDOW_WIDTH = 1200;
constexpr int INIT_WINDOW_HEIGHT = 800;
constexpr int INIT_HISTOGRAM_WIDTH = 700;
constexpr int INIT_HISTOGRAM_HEIGHT = 800;
constexpr int MAX_HISTOGRAM_X_VALUE = 256;
constexpr int INIT_IMAGE_WIDTH = 400;
constexpr int INIT_IMAGE_HEIGHT = 300;
constexpr int BUTTON_HEIGHT = 40;
constexpr int SPACER_WIDTH = 20;
constexpr int SPACER_HEIGHT = 40;

// --- SEPIA ---
constexpr float SEPIA_FACTOR_RED_FOR_RED_PIXEL = 0.393;
constexpr float SEPIA_FACTOR_GREEN_FOR_RED_PIXEL = 0.769;
constexpr float SEPIA_FACTOR_BLUE_FOR_RED_PIXEL = 0.189;
constexpr float SEPIA_FACTOR_RED_FOR_GREEN_PIXEL = 0.349;
constexpr float SEPIA_FACTOR_GREEN_FOR_GREEN_PIXEL = 0.686;
constexpr float SEPIA_FACTOR_BLUE_FOR_GREEN_PIXEL = 0.168;
constexpr float SEPIA_FACTOR_RED_FOR_BLUE_PIXEL = 0.272;
constexpr float SEPIA_FACTOR_GREEN_FOR_BLUE_PIXEL = 0.534;
constexpr float SEPIA_FACTOR_BLUE_FOR_BLUE_PIXEL = 0.131;


#endif // CONSTANTS_H
