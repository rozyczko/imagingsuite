#include <QtTest>
#include <QDebug>

// add necessary includes here
#include <stltools/stlvecmath.h>

class STLVecOperations : public QObject
{
    Q_OBJECT

public:
    STLVecOperations();
    ~STLVecOperations();

private slots:
    void test_medianFilter();
    void test_MAD();

};

STLVecOperations::STLVecOperations()
{

}

STLVecOperations::~STLVecOperations()
{

}

void STLVecOperations::test_medianFilter()
{
    size_t N=10000000;
    std::vector<float> orig(N);
    std::vector<float> result(N);

    float val=1;
    for (auto &x : orig)
    {
        x+=val;
        val+=x;
    }
    orig=medianFilter(orig,7);
    if (N<30)
    {
        auto it=result.begin();
        for (auto &x: orig) 
        {
            qDebug()<<x<<(*it);
            ++it;
        }

    }



}

void STLVecOperations::test_MAD()
{
    std::vector<float> v={0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1000.0f};

    auto mad = MAD(v);

    QVERIFY(mad==3.0);

}

QTEST_APPLESS_MAIN(STLVecOperations)

#include "include/tst_stlvecoperations.moc"
