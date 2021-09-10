#include <iostream>
#include <fstream>

int main() {
    constexpr int ImageWidth = 256;
    constexpr int ImageHeight = 196;

    constexpr int MaxColorValue = 255;

    constexpr char const * const FileName = "images/01-1-FirstImage.ppm";
    std::ofstream ImageFile(FileName);

    ImageFile << "P3\n"; // Colors are in ASCII
    ImageFile << ImageWidth << " " << ImageHeight << "\n"; // Columns and Rows
    ImageFile << MaxColorValue << "\n";

    // Write R G B colors of a pixel row by row left to right
    for (int32_t i = 0; i < ImageHeight; ++i) {
        for (int32_t j = 0; j < ImageWidth; ++j) {

            int32_t r = static_cast<int32_t>(static_cast<float>(i + 1) / static_cast<float>(ImageHeight) * MaxColorValue);
            int32_t g = MaxColorValue / 2;
            int32_t b = static_cast<int32_t>(static_cast<float>(j + 1) / static_cast<float>(ImageWidth) * MaxColorValue);

            ImageFile << r << " " << g << " " << b << " ";
        }

        ImageFile << "\n";
    }
}