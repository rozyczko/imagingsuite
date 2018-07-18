#include <QString>
#include <QtTest>


#include <base/timage.h>
#include <base/index2coord.h>
#include <math/mathconstants.h>
#include <drawing/drawing.h>
#include <io/io_tiff.h>
#include <math/statistics.h>

#include <contrastsampleanalysis.h>
#include <resolutionestimators.h>

class TImagingQAAlgorithmsTest : public QObject
{
    Q_OBJECT

public:
    TImagingQAAlgorithmsTest();

private Q_SLOTS:
    void testContrastSampleAnalysis();
    void testResEstAdmin();
    void testResEstAlg();
};

TImagingQAAlgorithmsTest::TImagingQAAlgorithmsTest()
{
}

void TImagingQAAlgorithmsTest::testContrastSampleAnalysis()
{
    ImagingQAAlgorithms::ContrastSampleAnalysis csa;
    const size_t N=512;
    size_t dims[2]={N,N};

    kipl::base::TImage<float,2> orig(dims);
    const float resolution=0.05f;
    const float radius=3.0f/resolution;
    const float ringRadius=9.0f/resolution;
    kipl::drawing::Circle<float> inset(radius);

    for (int i=0; i<6; ++i) {
        int x=N/2.0f+ringRadius*cos(i*fPi/3.0f);
        int y=N/2.0f+ringRadius*sin(i*fPi/3.0f);
        float val=1.0f+i*0.1f;
      //  std::cout<<x<<", "<<y<<": "<<val<<std::endl;
        inset.Draw(orig,x,y,val);
    }
    kipl::io::WriteTIFF32(orig,"csa_test_orig.tif");

    kipl::math::Statistics stats[6];
    kipl::base::coords3Df centers[6];

    csa.saveIntermediateImages=true;

    csa.setImage(orig);

    csa.analyzeContrast(resolution);

}



void TImagingQAAlgorithmsTest::testResEstAlg()
{

}

QTEST_APPLESS_MAIN(TImagingQAAlgorithmsTest)

#include "tst_timagingqaalgorithmstest.moc"
