#include <iostream>
#include <QString>
#include <QtTest>
#include <base/timage.h>
#include <io/io_tiff.h>
#include <filters/nonlocalmeans.h>


class TKiplAdvFiltersTest : public QObject
{
    Q_OBJECT

public:
    TKiplAdvFiltersTest();

private Q_SLOTS:
    void NLMeans_process();
};

TKiplAdvFiltersTest::TKiplAdvFiltersTest()
{
}

void TKiplAdvFiltersTest::NLMeans_process()
{
    kipl::base::TImage<float,2> img, res;
    kipl::io::ReadTIFF(img,"../data/scroll_256.tif");
    kipl::io::WriteTIFF(img,"orig_scroll.tif");


    akipl::NonLocalMeans nlfilter(11,1.5,8192);

    QBENCHMARK {
        nlfilter(img,res);
    }

    kipl::io::WriteTIFF(res,"nl_scroll.tif");

}

QTEST_APPLESS_MAIN(TKiplAdvFiltersTest)

#include "tst_tkipladvfilterstest.moc"
