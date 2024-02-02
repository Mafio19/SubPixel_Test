#include <iostream>
#include <unistd.h> // Include for getopt
#include <sys/stat.h>
#include <filesystem>
#include <opencv2/opencv.hpp>

class Chessboard{

public:

    Chessboard(int rows, int cols, cv::Point2d center, double squareSize);
    void drawChessboard(cv::Mat image);
    void traslateChessboard(cv::Mat image, cv::Mat traslImage, cv::Point2d ds);
    void rotateChessboard(cv::Mat image, cv::Mat rotImage, int angle);


private:

int numCols;
int numRows;
cv::Point2d center;
int squareSize;

};