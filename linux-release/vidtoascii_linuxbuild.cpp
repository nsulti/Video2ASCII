// Includes
#include <iostream>
#include <cstdlib>
#include "opencv2/opencv.hpp"
#include <string>
#include <vector>
#include <cmath>

// Aliases
typedef std::string str;

// Figures OS (CMD purposes)
str GetOsName() {
    #ifdef _WIN32
        return "Win";
    #elif _WIN64
        return "Win";
    #elif __linux__
        return "Linux";
    #else
        return "none";
    #endif     
}

// Struct/Enumerators. We LOVE ourselves a clean code. To me, one year from now.
struct s_Frame { // Basically the resolution and the frame itself.
    int nXSize;
    int nYSize;                            
    std::vector<char> vFrame;       // Totally a bad idea lol.
    std::vector<cv::Vec3b> cFrame; // colors of a frame, basically
};

enum eFail_state { // Error states.
    BAD_FILE = -4,
    BAD_SYSTEM = -3,
    BAD_ARGV = -2,
    BAD_FILE_NAME = -1,
    ALL_GOOD = 0
};

// Declaration of Functions. Not Independence. Totally hope these names are self-explanatory.
void useWebcam();
void useFile(str FileName);
void frameManip(cv::Mat * InFrame, s_Frame * structFrame, cv::Mat * ColFrame);
void outputFrame(s_Frame * Frame);
void systemClear();

// Variables
float dres = 0.2; // This variable decreases resolution to something acceptable. 
int to_color = 0;

// Main()
int main(int argc, char *argv[]) {

    if (argc < 2) { // No bad argv shall pass.
        std::cerr << "Usage: " << argv[0] << " <video>.\n";
        std::cerr << "Alternatively: " << argv[0] << " webcam; to use web-camera.\n";
        return BAD_ARGV;
    } 
    
    if (argc > 2) { // 3 if-statements are not enough.
        std::cerr << "Error (BAD_ARGV) > No more than 1 argument.\n";
        return BAD_ARGV;
    }

    std::string sOsName = GetOsName();

    std::cout << "How much to decrease resolution? (Default: " << dres << "f, increases it by " << dres << ", meaning it actually decreases)\n>";
    std::cin >> dres;
    std::cout << "\nColor the text? (Default: " << (bool) to_color <<". A number.)\n>";
    std::cin >> to_color;

    if (sOsName == "none") {
        std::cerr << "Error (BAD_SYSTEM) > Couldn't figure out your system.\n";
        return BAD_SYSTEM; // Deciding to not work because of a single damn command.
    }                      // LOL. 
    systemClear();

    std::string sFile_name = argv[1]; // Opening the argv file.
    if (sFile_name == "webcam") {     // Self-explanatory.
        useWebcam();
    } else { 
        useFile(sFile_name);
    }
    std::cout << "OK > Program finished. Cleaning up...\n";
    return ALL_GOOD;
}


// Definiton of functions.
void useFile(str sFile_name) {
    std::cout << "OK > Opening " << sFile_name << " file...\n";
    cv::VideoCapture FileOpen(sFile_name);
    
    if (!FileOpen.isOpened()) {
        std::cerr << "Error (BAD_FILE) > Failed to open " << sFile_name << ".\n";
        exit(BAD_FILE);
    }

    std::cout << "OK > File " << sFile_name << " opened.\n";
    std::cout << "HINT > Press 'Q' to quit.\n";

    s_Frame trFrame;

    cv::Mat frame;
    cv::Mat frame_col;
    

    while (true) {
        FileOpen >> frame;
	frame_col = frame.clone();
        if (frame.empty()) {
            cv::waitKey(0);
            FileOpen.release();
            break;
        }
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        cv::resize(frame, frame, cv::Size(), dres, dres, cv::INTER_LANCZOS4);
	cv::resize(frame_col, frame_col, cv::Size(), dres, dres, cv::INTER_LANCZOS4);
        // Getting video resolution.
        trFrame.nXSize = frame.cols;
        trFrame.nYSize = frame.rows;

        cv::Mat * pFrame = &frame;
        s_Frame * ptrFrame = &trFrame;
	cv::Mat * pColorFrame = &frame_col;

        frameManip(pFrame, ptrFrame, pColorFrame);
        outputFrame(&trFrame);
        trFrame.vFrame.clear();
	trFrame.cFrame.clear();
    }
    std::cout << "OK > Done.\n";
}

void useWebcam() {
    std::cout << "OK > Opening webcam...\n";
    cv::VideoCapture WebOpen(0);

    if (!WebOpen.isOpened()) {
        std::cerr << "Error (BAD_FILE) > Failed to open webcam.\n";
        exit(BAD_FILE);
    }

    std::cout << "OK > Webcam opened.\n";
    std::cout << "HINT > Press 'Q' to quit.\n"; // will be useful

    s_Frame web_trFrame;

    cv::Mat web_frame;
    cv::Mat web_frame_col;

    while (true) {
        WebOpen >> web_frame;
	web_frame_col = web_frame.clone();
        cv::cvtColor(web_frame, web_frame, cv::COLOR_BGR2GRAY);
        cv::resize(web_frame, web_frame, cv::Size(), dres, dres, cv::INTER_NEAREST);
	cv::resize(web_frame_col, web_frame_col, cv::Size(), dres, dres, cv::INTER_NEAREST);
        web_trFrame.nXSize = web_frame.cols;
        web_trFrame.nYSize = web_frame.rows;

        cv::Mat * pweb_Frame = &web_frame;
	cv::Mat * pweb_color_Frame = &web_frame_col;
        s_Frame * pweb_trFrame = &web_trFrame;
	

        frameManip(pweb_Frame, pweb_trFrame, pweb_color_Frame);
        outputFrame(pweb_trFrame);
        if (cv::waitKey(0) == 'q') {
            WebOpen.release();
            break;
        }
        web_trFrame.vFrame.clear();
	web_trFrame.cFrame.clear();
    }
    std::cout << "OK > Done.\n";
}

void outputFrame(s_Frame * Frame) {
    printf("\033[H");
    for (int y = 0; y < Frame->nYSize; y++) {
        for (int x = 0; x < Frame->nXSize; x++) {
	    int curr_pos = y * (Frame->nXSize) + x;
	    int B = (Frame->cFrame)[curr_pos][0];
	    int G = (Frame->cFrame)[curr_pos][1];
	    int R = (Frame->cFrame)[curr_pos][2];
	    if (!to_color) {R = 255, G = 255, B = 255;}
	    printf("\033[38;2;%d;%d;%dm%c", R, G, B, (Frame->vFrame)[curr_pos]); // БЛЯЯЯЯЯЯЯ
        }
        std::cout << "\n";
    }
}

void systemClear() {
    str sOsName = GetOsName();
    if (sOsName == "Linux") {       // We clear the terminal, including different OS.
        system("clear");   // How noble of me!
    } else if (sOsName == "Win") { // addendum a year later: it doesnt work lmao i did 2 different vers
        system("cls");
    }
}

void frameManip(cv::Mat * InFrame, s_Frame * structFrame, cv::Mat * ColFrame) {
    std::string sLuminance = ".,'-~:;=<!?*#$@"; // Luminance (Lightning) as
                                              // to differ colors(?) I guess.
    for (int y = 0; y < structFrame->nYSize; y++) {
        for (int x = 0; x < structFrame->nXSize; x++) { // wtf is this
            int pixel_initial = (*InFrame).at<uchar>(y, x); // to me, a year ago
	    cv::Vec3b color_pixel = (*ColFrame).at<cv::Vec3b>(y, x);
	    (structFrame->cFrame).push_back(color_pixel);
            int pixel_conv_lum = pixel_initial * sLuminance.length() / 256; // optimization? nah, never heard of it
            (structFrame->vFrame).push_back(sLuminance[pixel_conv_lum]);
        }
    }
}
