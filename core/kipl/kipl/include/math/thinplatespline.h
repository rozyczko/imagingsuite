//<LICENSE>

#ifndef THINPLATESPLINE_H
#define THINPLATESPLINE_H

#include "../kipl_global.h"

#include <vector>
#include <string>
#include <sstream>

#include <armadillo>

#include "../../include/logging/logger.h"
#include "../../include/base/timage.h"

namespace kipl {
namespace math {

class KIPLSHARED_EXPORT ThinPlateSpline 
{
    kipl::logging::Logger logger;
public:
    ThinPlateSpline();
    ~ThinPlateSpline();

    void fit(const std::vector<float> &x, const std::vector<float> &y, const std::vector &value);
    kipl::base::TImage<float,2> predict(const std::vector<size_t> &ROI);
private:
    std::vector<float> radialDistance(float x, float y);
    std::vector<float> radialDistance(const std::vector<float> &x, const std::vector<float> &y);
    

    std::vector<float> controlPoints;

};

}
}
#endif