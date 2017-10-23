#include "opencv2/imgproc/imgproc.hpp"
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

float deformationIndice(int i, int a, int b, int c) {
  float sba = std::sqrt(std::pow((step + i) - i, 2) + std::pow(b - a, 2));
  float sbc = std::sqrt(std::pow((step + i) - ((step * 2) + i), 2) + std::pow(b - c, 2));
  float sac = std::sqrt(std::pow(i - ((step * 2) + i), 2) + std::pow(a - c, 2));
  float angle = (std::pow(sba, 2) + std::pow(sbc, 2) - std::pow(sac, 2)) / (2 * sba * sbc);
  int value = std::acos(angle) * (180/3.14);
  return value;
}

int spikesCounter(std::vector<int>& v) {
  int sum = 0;
  for(std::vector<int>::size_type i = 0; i != v.size(); i++) {
    sum += v[i];
  }
  sum /= v.size();
  int limit = sum - (sum / 10);
  int spikes = 0;
  bool isUnder = false;
  for(std::vector<int>::size_type i = 0; i != v.size(); i++) {
    if (v[i] < limit && !isUnder) {
      spikes++;
      isUnder = true;
    }
    if (v[i] > limit && isUnder) {
      isUnder = false;
    }
  }
  return spikes;
}

void imageAnalyse() {
  std::vector<int> scan;
  step =  (10 * img.cols) / 100;
  for (int i = 0; i < img.rows; ++i)
  {
      cv::Vec3b* pixel = img.ptr<cv::Vec3b>(i);
      int fw = 0;
      int bw = img.cols - 1;
      while (fw < img.cols && pixel[fw][2] == 255) {
        fw++;
      }
      while (bw >= 0 && pixel[bw][2] == 255) {
        bw--;
      }
      if (bw - fw > 0) {
        scan.push_back(bw - fw);
      }
  }

  bool isFlat = true;
  int tmp = scan[0];
  std::vector<int> dE;
  for(std::vector<int>::size_type i = 0; i != scan.size(); i++) {
    if (scan[i] != tmp)
      isFlat = false;
    if (i + (step * 2) < scan.size())
      dE.push_back(deformationIndice(i, scan[i], scan[i + step], scan[i + (step * 2)]));
  }
  int sp = spikesCounter(dE);
  if (sp == 0 && !isFlat)
    std::cout << "CIRCLE !!" << std::endl;
  else
    std::cout << "SQUARE !!" << std::endl;
}

int main( int argc, char** argv )
{
    img = imread( argv[1], 1 );
    imagePreprocessing();
    imageAnalyse();
    return 0;
}
