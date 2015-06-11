//
// This file is part of the Inspector library by Anders Kaestner
// (c) 2011 Anders Kaestner
// Distribution is only allowed with the permission of the author.
//
// Revision information
// $Author: kaestner $
// $File$
// $Date: 2012-12-21 15:25:10 +0100 (Fri, 21 Dec 2012) $
// $Rev: 1417 $
// $Id: SaveProjections.cpp 1417 2012-12-21 14:25:10Z kaestner $
//

#include "stdafx.h"
#include "SaveProjections.h"

#include <io/io_stack.h>

SaveProjections::SaveProjections() :
	PreprocModuleBase("SaveProjections"),
	m_eImageType(ReconConfig::cProjections::ImageType_Projections)
{
}

SaveProjections::~SaveProjections() {
}

std::map<std::basic_string<char>, std::basic_string<char> > SaveProjections::GetParameters()
{
	std::map<std::basic_string<char>, std::basic_string<char> > parameters;

	parameters["filemask"]="./projections_####.tif";
	kipl::strings::filenames::CheckPathSlashes(parameters["filemask"],false);

	parameters["imagetype"]=enum2string(m_eImageType); 

	return parameters;
}

int SaveProjections::Configure(ReconConfig config, std::map<std::basic_string<char>, std::basic_string<char> > parameters)
{
	m_config=config;

	m_sFileMask  = parameters["filemask"];
	string2enum(parameters["imagetype"],m_eImageType);

	return 0;
}

int SaveProjections::ProcessCore(kipl::base::TImage<float,3> &img, std::map<std::string,std::string> &parameters)
{
	switch (m_eImageType) {
		case ReconConfig::cProjections::ImageType_Projections :
			kipl::io::WriteImageStack(img,m_sFileMask,
				0.0f, 0.0f,
				0, img.Size(2), 1,
				kipl::io::TIFFfloat,kipl::base::ImagePlaneXY);
			break;
		case ReconConfig::cProjections::ImageType_Sinograms : 
			{
				kipl::base::TImage<float,2> sino;
				std::string fname,ext;
				for (size_t i=0; i<img.Size(1); i++) {	
					ExtractSinogram(img,sino,i);
					kipl::strings::filenames::MakeFileName(m_sFileMask,i+m_config.ProjectionInfo.nFirstIndex,fname,ext,'#','0');
					kipl::io::WriteTIFF32(sino,fname.c_str());
				}
			}
			break;
		default: break;
	}

	return 0;
}
