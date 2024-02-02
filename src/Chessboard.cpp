#include <iostream>
#include <unistd.h> // Include for getopt
#include <sys/stat.h>
#include <filesystem>
#include <opencv2/opencv.hpp>


#include "Chessboard.h"

Chessboard::Chessboard(int rows, int cols, cv::Point2d center, double squareSize) 
    : numCols(cols), numRows(rows), center(center), squareSize(squareSize) {
    // Implementazione del costruttore
}

void Chessboard::drawChessboard(cv::Mat image) {

    double width = (numCols + 1) * squareSize;
    double height = (numRows + 1) * squareSize;

    //image = cv::Mat::zeros(image.cols, image.rows, CV_8UC3);

    double startX = (image.cols - width) / 2;
    double startY = (image.rows - height) / 2;

    for (int i = 0; i < numRows + 1; ++i) {
        for (int j = 0; j < numCols + 1; ++j) {
            int x = startX + j * squareSize;
            int y = startY + i * squareSize;
            cv::Scalar color = ((i + j) % 2 == 0) ? cv::Scalar(255, 255, 255) : cv::Scalar(0, 0, 0);
            cv::rectangle(image, cv::Point(x, y), cv::Point(x + squareSize, y + squareSize), color, cv::FILLED);
        }
    }

    cv::rectangle(image, cv::Point(startX, startY), cv::Point(startX + width, startX + height), cv::Scalar(255, 0, 0), 2.0);
    
}

void Chessboard::traslateChessboard(cv::Mat image, cv::Mat traslImage, cv::Point2d ds) {
    cv::Mat translationMatrix = (cv::Mat_<double>(2, 3) << 1, 0, ds.x, 0, 1, ds.y);
    cv::warpAffine(image, traslImage, translationMatrix, image.size());

}

void Chessboard::rotateChessboard(cv::Mat image, cv::Mat rotImage, int alpha) {
    cv::Mat rotMatrix = cv::getRotationMatrix2D(center, alpha, 1.0);
    cv::warpAffine(image, rotImage, rotMatrix, image.size());
    //cv::warpAffine(image, rotImage, rotMatrix, image.size(), cv::INTER_LINEAR);
}

