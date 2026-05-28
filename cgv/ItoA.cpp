#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <set>
#include<fstream>
#include <algorithm>

using namespace cv;
using namespace std;

int main()
{
    Mat A = imread("gray_image.png", IMREAD_GRAYSCALE);
    if (A.empty()) {
        cout << "Image not found\n";
        return -1;
    }
    int tileH = 8, tileW = 10;
    int tilesY = A.rows / tileH;
    int tilesX = A.cols / tileW;

    Mat B(tilesY, tilesX, CV_8UC1);
    set<int> grayLevels;   // Step C
    for (int i = 0; i < tilesY; i++) {
        for (int j = 0; j < tilesX; j++) {
            Rect roi(j * tileW, i * tileH, tileW, tileH);
            Mat tile = A(roi);

            Scalar s = sum(tile);
            int avg = static_cast<int>(s[0] / 80.0 + 0.5);

            B.at<uchar>(i, j) = avg;
            grayLevels.insert(avg);
        }
    }
    vector<int> uniqueGray(grayLevels.begin(), grayLevels.end());
    int Ng = uniqueGray.size();
    vector<char> asciiChars;
    vector<pair<char, double>> charDarkness;

    for (int c = 32; c <= 126; c++) {
        Mat img(50, 50, CV_8UC1, Scalar(255));

        putText(img, string(1, char(c)), Point(5, 40),
                FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0), 2);

        Mat bin;
        threshold(img, bin, 200, 255, THRESH_BINARY_INV);

        int blackPixels = countNonZero(bin);
        double darkness = (double)blackPixels / bin.total();

        charDarkness.push_back({char(c), darkness});
    }

    sort(charDarkness.begin(), charDarkness.end(),
         [](auto &a, auto &b) {
             return a.second < b.second;
         });

    for (auto &p : charDarkness)
        asciiChars.push_back(p.first);

    int Nc = asciiChars.size();  // = 95
    auto grayToChar = [&](int g) {
        int idx = g * (Nc - 1) / 255;
        return asciiChars[idx];
    };

        ofstream out("ascii_output.txt");
    if (!out.is_open()) {
        cerr << "Failed to open output file\n";
        return 1;
    }

    for (int i = 0; i < B.rows; i++) {
        for (int j = 0; j < B.cols; j++) {
            out << grayToChar(B.at<uchar>(i, j));
        }
        out << '\n';
    }

    out.close();
    return 0;
}
