/*=============================================================================
 *
 *  Copyright (c) 2019 Sunnybrook Research Institute
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 *=============================================================================*/

#ifndef STAINANALYSIS_MACENKOHISTOGRAM_H
#define STAINANALYSIS_MACENKOHISTOGRAM_H

#include <cassert>
#include <random>

//OpenCV include
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace sedeen {
namespace image {

class MacenkoHistogram {
public:
    ///An enum to identify which axis the input vectors are arranged in (outputs will match)
    enum VectorDirection {
        COLUMNVECTORS,
        ROWVECTORS
    };

public:
    MacenkoHistogram();
    ~MacenkoHistogram();

    ///Which signs should be used for the basis vectors? Test projecting some source points, try to get ++ quadrant projections
    void OptimizeBasisVectorSigns(cv::InputArray sourcePixels, 
        cv::InputArray inputVectors, cv::OutputArray outputVectors, 
        VectorDirection basisVecDir = VectorDirection::COLUMNVECTORS);

    ///Set/Get the numTestingPixels member variable
    inline void SetNumTestingPixels(int n) { m_numTestingPixels = n; }
    ///Set/Get the numTestingPixels member variable
    inline  int GetNumTestingPixels() { return m_numTestingPixels; }

protected:
    ///Randomly choose numberOfPixels rows from sourcePixels, copy them to the subsample OutputArray.
    void CreatePixelSubsample(cv::InputArray sourcePixels, cv::OutputArray subsample, int numberOfPixels);


protected:
    ///Allow derived classes access to the random number generator (64-bit Mersenne Twister)
    std::mt19937_64 m_rgen; //64-bit Mersenne Twister

private:
    int m_numTestingPixels;

};

} // namespace image
} // namespace sedeen
#endif