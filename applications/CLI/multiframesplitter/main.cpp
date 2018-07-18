#include <iostream>
#include <sstream>
#include <map>

#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QDebug>

#include <analyzefileext.h>
#include <base/timage.h>
#include <base/KiplException.h>
#include <base/kiplenums.h>
#include <logging/logger.h>
#include <strings/filenames.h>

#include <imagereader.h>
#include <imagewriter.h>
#include <readerexception.h>

kipl::logging::Logger logger("MultiFrameSplitter");

int process(QCoreApplication &a);

int parseArguments(QVector<QString> qargs, std::map<string, string> &pars);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    process(a);

    return a.exec();
}

int process(QCoreApplication &a)
{
    std::ostringstream msg;
    QVector<QString> qargs=a.arguments().toVector();

    std::map<std::string,std::string> args;
    parseArguments(qargs,args);


    int cnt=qargs.size();
    if (cnt==1) {
        logger(logger.LogMessage,"No arguments");
        qDebug() << "No arguments";
        return 0;
    }

    size_t dims[10];
    int nDims=0;
    ImageReader reader;

    std::string srcfname=args["infile"];
    nDims=reader.GetImageSize(srcfname,1.0f,dims);

    qDebug() << "nDims:" <<nDims;
    if (nDims<3) {
        logger(logger.LogWarning,"This is a single frame image");
        return 0;
    }

    cnt=dims[2];

    msg.str("");
    msg<<srcfname<<" has "<<cnt<<" slices";
    logger(logger.LogMessage,msg.str());
    qDebug() << QString::fromStdString(msg.str());

    std::string path;
    std::string fname;
    std::vector<std::string> exts;

    kipl::strings::filenames::StripFileName(srcfname,path,fname,exts);

    std::string fmask=args["outfile"];

    if (fmask.empty()) {
        fmask=path+fname+"_#####.tif";
    }

    int first = 0 ;
    int last  = cnt-1;
    if (args["first"].empty()==false)
        first = std::stoi(args["first"]);

    if (args["last"].empty()==false)
        last = std::stoi(args["last"]);

    kipl::base::eImageRotate rotate=kipl::base::ImageRotateNone;

    if (args["rotate"].empty()==false)
        string2enum(args["rotate"],rotate);

    qDebug() << QString::fromStdString(fmask) << ", first="<<first<<", last="<<last<<QString::fromStdString(enum2string(rotate));

    std::string destname,ext;
    ImageWriter writer;
    kipl::base::TImage<float,2> img;
    try {
        for (int i=first; i<=last; ++i) {
            img=reader.Read(srcfname,kipl::base::ImageFlipNone,rotate,1.0,nullptr,i);
            kipl::strings::filenames::MakeFileName(fmask,i,destname,ext,'#','0');

            writer.write(img,destname);
        }
    }
    catch (ReaderException &e) {
        qDebug() << QString::fromStdString(e.what());
    }
    catch (kipl::base::KiplException &e) {
        qDebug() << QString::fromStdString(e.what());
    }
    return cnt;
}

int parseArguments(QVector<QString> qargs, std::map<std::string,std::string> &pars)
{
    auto item=qargs.begin();
    ++item;
    for ( ; item!= qargs.end() ; ++item) {
        if ((*item)[0]!='-')
            throw kipl::base::KiplException("Invalid argument",__FILE__,__LINE__);
        if (*item=="-i") {
            ++item;
            if (item==qargs.end())
                throw kipl::base::KiplException("Too few arguments",__FILE__,__LINE__);

            pars.insert(std::make_pair("infile",item->toStdString()));
        }

        if (*item=="-o") {
            ++item;
            if (item==qargs.end())
                throw kipl::base::KiplException("Too few arguments",__FILE__,__LINE__);

            pars.insert(std::make_pair("outfile",item->toStdString()));
        }

        if (*item=="-first") {
            ++item;
            if (item==qargs.end())
                throw kipl::base::KiplException("Too few arguments",__FILE__,__LINE__);

            pars.insert(std::make_pair("first",item->toStdString()));
        }

        if (*item=="-last") {
            ++item;
            if (item==qargs.end())
                throw kipl::base::KiplException("Too few arguments",__FILE__,__LINE__);

            pars.insert(std::make_pair("last",item->toStdString()));
        }

        if (*item=="-rot") {
            ++item;
            if (item==qargs.end())
                throw kipl::base::KiplException("Too few arguments",__FILE__,__LINE__);
            std::string rotstring="ImageRotate"+(*item == "0" ? "None" : item->toStdString());
            pars.insert(std::make_pair(std::string("rotate"),rotstring));
        }
    }

    for (auto par : pars) {
        std::cout<<par.first<<"="<<par.second<<std::endl;
    }

    return pars.size();
}
