#include <iostream>
#include <unistd.h> // Include for getopt
#include <sys/stat.h>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <iomanip>


#include "Chessboard.h"


int main(int argc, char** argv) {

    int imageWidth = 1920;
    int imageHeight = 1080;

    int rows = 1;
    int cols = 1;
    cv::Point2d center(static_cast<double>(imageWidth) / 2, static_cast<double>(imageHeight) / 2);
    double squareSize = 1 * std::min(imageWidth / (cols + 1), imageHeight / (rows + 1));

    bool rotateAllAngles = false;
    int rotationAngle = 45;
    std::string folderPath = "Images";

    cv::Point2d ds(100,200);


    int opt;
    while ((opt = getopt(argc, argv, "o:b:s:la:")) != -1) {
        switch (opt) {
            case 'b': {
                // Parse rows and columns from the argument value
                std::string arg = optarg;
                size_t pos = arg.find('x');
                if (pos != std::string::npos) {
                    rows = std::stoi(arg.substr(0, pos));
                    cols = std::stoi(arg.substr(pos + 1));
                } else {
                    std::cerr << "Invalid format for -b option. Use -b <rows>x<cols>" << std::endl;
                    return 1;
                }
                break;
            }
            case 'l':
                rotateAllAngles = true;
                break;
            case 'a':
                rotationAngle = std::stoi(optarg);
                break;
            case 'o':
                folderPath = optarg;
                break;
            case 's':
                squareSize = std::stoi(optarg);
                break;        
            default:
                std::cerr << "Usage: " << argv[0] << " -o <Folder_Path> -b <rows>x<cols> -s <squarSize> [-l|-a <angle>]" << std::endl;
                return 1;
        }
    }
    
    cv::Mat image (imageHeight, imageWidth, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat outImage (imageHeight, imageWidth, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat traslImage (imageHeight, imageWidth, CV_8UC3, cv::Scalar(0, 0, 0));

    // Create an Chessboard object
    Chessboard myChessboard(rows, cols, center, squareSize );

    std::cout << "Centro del pixel centrale: (" << std::fixed << std::setprecision(2) << center.x << ", " << center.y << ")" << std::endl;

    // Draw one 
    myChessboard.drawChessboard(image);
    cv::circle(image, cv::Point(center.x, center.y), 1, cv::Scalar(255,255,0), cv::FILLED);
    

    myChessboard.rotateChessboard(image, outImage, rotationAngle);

    myChessboard.traslateChessboard(image, traslImage, ds);


    cv::namedWindow("Scacchiera", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_NORMAL);
    cv::namedWindow("Scacchiera traslata", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_NORMAL);
    cv::namedWindow("Scacchiera ruotata", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_NORMAL);

    cv::imshow("Scacchiera", image);
    cv::imshow("Scacchiera traslata", traslImage);
    cv::imshow("Scacchiera ruotata", outImage);

    cv::waitKey(0);
    
    
    return 0;
    

}
