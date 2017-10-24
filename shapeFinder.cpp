#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>

using namespace cv;
int step = 0;
Mat img; Mat dst;
char window_name1[] = "Unprocessed Image";
char window_name2[] = "Processed Image";

void imagePreprocessing() {
    // Make it bi-color for more precision
}

float deformationIndice(int i, int a, int b, int c)
    {
    const float sba = sqrt (pow (step, 2) + pow (b - a, 2));
    const float sbc = sqrt (pow (step + i - (step * 2 + i), 2) + pow (b - c, 2));
    const float sac = sqrt (pow (i - (step * 2 + i), 2) + pow (a - c, 2));
    const float angle = (pow (sba, 2) + pow (sbc, 2) - pow (sac, 2)) / (2 * sba * sbc);

    return acos(angle) * (180 / 3.14);
    }

int spikesCounter(vector<int>& v)
    {
    int sum = 0;
    for(vector<int>::size_type i = 0; i != v.size(); i++)
        sum += v[i];

    sum /= v.size();
    
    int limit = sum - (sum / 10);
    int spikes = 0;
    bool isUnder = false;

    for(vector<int>::size_type i = 0; i != v.size(); i++)
        {
        if (v[i] < limit && !isUnder) 
            {
            spikes++;
            isUnder = true;
            }

        if (v[i] > limit && isUnder)
            isUnder = false;
        }

    return spikes;
}

void imageAnalyse() {
    vector<int> scan;
    step =  10 * img.cols / 100;

    for (int i = 0; i < img.rows; ++i)
        {
        Vec3b* pixel = img.ptr<Vec3b>(i);
        int fw = 0;
        int bw = img.cols - 1;

        while (fw < img.cols && pixel[fw][2] == 255)
            fw++;

        while (bw >= 0 && pixel[bw][2] == 255)
            bw--;

        if (bw - fw > 0)
            scan.push_back(bw - fw);
        }
    
    bool isFlat = true;
    int tmp = scan[0];
    vector<int> dE;
    for (vector<int>::size_type i = 0; i != scan.size(); i++)
        {
        if (scan[i] != tmp)
            isFlat = false;

        if (i + step * 2 < scan.size())
            dE.push_back(deformationIndice(i, scan[i], scan[i + step], scan[i + step * 2]));
        }

    int sp = spikesCounter (dE);
    if (sp == 0 && !isFlat)
        std::cout << "CIRCLE !!" << std::endl;
    else
        std::cout << "SQUARE !!" << std::endl;
    }

int main( int argc, char** argv )
    {
    img = imread (argv[1], 1);
    imagePreprocessing();
    imageAnalyse();
    return 0;
    }
