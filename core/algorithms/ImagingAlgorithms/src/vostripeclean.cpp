//<LICENSE>
#include "../include/vostripeclean.h"
#include <base/timage.h>
#include <list>

VoStripeClean::VoStripeClean()
{

}

kipl::base::TImage<float,2> VoStripeClean::removeStripeBasedSorting(kipl::base::TImage<float,2> &sinogram, size_t size)
{
//    """
//    Algorithm 3 in the paper. Remove stripes using the sorting technique.
//    Work particularly well for removing partial stripes.
//    Angular direction is along the axis 0
//    ---------
//    Parameters: - sinogram: 2D array.
//                - size: window size of the median filter.
//    ---------
//    Return:     - stripe-removed sinogram.
//    """
//    sinogram = np.transpose(sinogram)
//    (nrow, ncol) = sinogram.shape
//    listindex = np.arange(0.0, ncol, 1.0)
//    matindex = np.tile(listindex,(nrow,1))
//    matcomb = np.asarray(np.dstack((matindex, sinogram)))
//    matsort = np.asarray(
//        [row[row[:, 1].argsort()] for row in matcomb])
//    matsort[:, :, 1] = median_filter(matsort[:, :, 1],(size,1))
//    matsortback = np.asarray(
//        [row[row[:, 0].argsort()] for row in matsort])
//    sino_corrected = matsortback[:, :, 1]
//    return np.transpose(sino_corrected)
   kipl::base::TImage<float,2> res;

   return res;
}

kipl::base::TImage<float,2> VoStripeClean::remove_stripe_based_filtering(kipl::base::TImage<float,2> &sinogram, float sigma, size_t size)
{
//    """
//    Algorithm 2 in the paper. Remove stripes using the filtering technique.
//    Angular direction is along the axis 0
//    ---------
//    Parameters: - sinogram: 2D array.
//                - sigma: sigma of the Gaussian window which is used to separate
//                        the low-pass and high-pass components of the intensity
//                        profiles of each column.
//                - size: window size of the median filter.
//    ---------
//    Return:     - stripe-removed sinogram.
//    """
//    pad = 150 # To reduce artifacts caused by FFT
//    sinogram = np.transpose(sinogram)
//    sinogram2 = np.pad(sinogram,((0, 0),(pad, pad)), mode = 'reflect')
//    (_, ncol) = sinogram2.shape
//    window = signal.gaussian(ncol, std = sigma)
//    listsign = np.power(-1.0,np.arange(ncol))
//    sinosmooth = np.zeros_like(sinogram)
//    for i,sinolist in enumerate(sinogram2):
//        #sinosmooth[i] = np.real(ifft(fft(sinolist*listsign)*window)*listsign)[pad:ncol-pad]
//        sinosmooth[i] = np.real(fft.ifft(fft.fft(sinolist*listsign)*window)*listsign)[pad:ncol-pad]
//    sinosharp = sinogram - sinosmooth
//    sinosmooth_cor = median_filter(sinosmooth,(size,1))
//    return np.transpose(sinosmooth_cor + sinosharp)
    kipl::base::TImage<float,2> res;

    return res;
}


kipl::base::TImage<float,2> VoStripeClean::_2d_window_ellipse(size_t height, size_t width, float sigmax, float sigmay)
{
//    """
//    Create a 2D Gaussian window.
//    ---------
//    Parameters: - height, width: shape of the window.
//                - sigmax, sigmay: sigmas of the window.
//    ---------
//    Return:     - 2D window.
//    """
//    centerx = (width-1.0)/2.0
//    centery = (height-1.0)/2.0
//    y,x = np.ogrid[-centery:height-centery,-centerx:width-centerx]
//    numx = 2.0*sigmax*sigmax
//    numy = 2.0*sigmay*sigmay
//    win2d = np.exp(-(x*x/numx+y*y/numy))
//    return win2d
    kipl::base::TImage<float,2> res;

    return res;
}

kipl::base::TImage<float,2> VoStripeClean::_2d_filter(kipl::base::TImage<float,2> mat, float sigmax, float sigmay, size_t pad)
{
//    """
//    Filtering an image using 2D Gaussian window.
//    ---------
//    Parameters: - mat: 2D array.
//                - sigmax, sigmay: sigmas of the window.
//                - pad: padding for FFT
//    ---------
//    Return:     - filtered image.
//    """
//    matpad = np.pad(mat,((0, 0), (pad, pad)), mode = 'edge')
//    matpad = np.pad(matpad,((pad, pad), (0, 0)), mode = 'mean')
//    (nrow, ncol) = matpad.shape
//    win2d = _2d_window_ellipse(nrow, ncol, sigmax, sigmay)
//    listx = np.arange(0, ncol)
//    listy = np.arange(0, nrow)
//    x,y = np.meshgrid(listx, listy)
//    matsign = np.power(-1.0,x+y)
//    #matfilter = np.real(ifft2(fft2(matpad*matsign)*win2d)*matsign)
//    matfilter = np.real(fft.ifft2(fft.fft2(matpad*matsign)*win2d)*matsign)
//    return matfilter[pad:nrow-pad,pad:ncol-pad]
    kipl::base::TImage<float,2> res;

    return res;
}

kipl::base::TImage<float,2> VoStripeClean::remove_stripe_based_fitting(kipl::base::TImage<float, 2> &sinogram, int order, float sigmax, float sigmay)
{
//    """
//    Algorithm 1 in the paper. Remove stripes using the fitting technique.
//    Angular direction is along the axis 0
//    ---------
//    Parameters: - sinogram: 2D array.
//                - order: polynomical fit order.
//                - sigmax, sigmay: sigmas of the Gaussian window.
//    ---------
//    Return:     - stripe-removed sinogram.
//    """
//    (nrow, _) = sinogram.shape
//    nrow1 = nrow
//    if nrow1%2==0:
//        nrow1 = nrow1 - 1
//    sinofit = savgol_filter(sinogram, nrow1, order, axis=0,mode = 'mirror')
//    sinofitsmooth = _2d_filter(sinofit, sigmax, sigmay, 50)
//    num1 = np.mean(sinofit)
//    num2 = np.mean(sinofitsmooth)
//    sinofitsmooth = num1*sinofitsmooth/num2
//    return sinogram/sinofit*sinofitsmooth
    kipl::base::TImage<float,2> res;

    return res;
}

std::list<size_t> VoStripeClean::detect_stripe(listdata, snr)
{
//    """
//    Algorithm 4 in the paper. Used to locate stripe positions.
//    ---------
//    Parameters: - listdata: 1D normalized array.
//                - snr: ratio used to discriminate between useful
//                    information and noise.
//    ---------
//    Return:     - 1D binary mask.
//    """
//    numdata = len(listdata)
//    listsorted = np.sort(listdata)[::-1]
//    xlist = np.arange(0, numdata, 1.0)
//    ndrop = np.int16(0.25 * numdata)
//    (_slope, _intercept) = np.polyfit(
//        xlist[ndrop:-ndrop-1], listsorted[ndrop:-ndrop - 1], 1)
//    numt1 = _intercept + _slope * xlist[-1]
//    noiselevel = np.abs(numt1 - _intercept)
//    val1 = np.abs(listsorted[0] - _intercept) / noiselevel
//    val2 = np.abs(listsorted[-1] - numt1) / noiselevel
//    listmask = np.zeros_like(listdata)
//    if (val1 >= snr):
//        upper_thresh = _intercept + noiselevel * snr * 0.5
//        listmask[listdata > upper_thresh] = 1.0
//    if (val2 >= snr):
//        lower_thresh = numt1 - noiselevel * snr * 0.5
//        listmask[listdata <= lower_thresh] = 1.0
//    return listmask
    std::list<size_t> listmask;

    return listmask;
}

kipl::base::TImage<float,2> VoStripeClean::remove_large_stripe(kipl::base::TImage<float,2> &sinogram, float snr, size_t size)
{
//    """
//    Algorithm 5 in the paper. Remove large stripes by: locating stripes,
//    normalizing to remove full stripes, using the sorting technique to
//    remove partial stripes.
//    Angular direction is along the axis 0.
//    ---------
//    Parameters: - sinogram: 2D array.
//                - snr: ratio used to discriminate between useful
//                    information and noise.
//                - size: window size of the median filter.
//    ---------
//    Return:     - stripe-removed sinogram.
//    """
//    badpixelratio = 0.05
//    (nrow, ncol) = sinogram.shape
//    ndrop = np.int16(badpixelratio * nrow)
//    sinosorted = np.sort(sinogram, axis=0)
//    sinosmoothed = median_filter(sinosorted, (1, size))
//    list1 = np.mean(sinosorted[ndrop:nrow - ndrop], axis=0)
//    list2 = np.mean(sinosmoothed[ndrop:nrow - ndrop], axis=0)
//    listfact = list1 / list2
//    listmask = detect_stripe(listfact, snr)
//    listmask = binary_dilation(listmask, iterations=1).astype(listmask.dtype)
//    matfact = np.tile(listfact,(nrow,1))
//    sinogram = sinogram / matfact
//    sinogram1 = np.transpose(sinogram)
//    listindex = np.arange(0.0, nrow, 1.0)
//    matindex = np.tile(listindex,(ncol,1))
//    matcombine = np.asarray(np.dstack((matindex, sinogram1)))
//    matsort = np.asarray(
//        [row[row[:, 1].argsort()] for row in matcombine])
//    matsort[:, :, 1] = np.transpose(sinosmoothed)
//    matsortback = np.asarray(
//        [row[row[:, 0].argsort()] for row in matsort])
//    sino_corrected = np.transpose(matsortback[:, :, 1])
//    listxmiss = np.where(listmask > 0.0)[0]
//    sinogram[:, listxmiss] = sino_corrected[:, listxmiss]
//    return sinogram
    kipl::base::TImage<float,2> res;

    return res;
}

kipl::base::TImage<float,2> VoStripeClean::remove_unresponsive_and_fluctuating_stripe(kipl::base::TImage<float,2> &sinogram, float snr, size_t size)
{
    kipl::base::TImage<float,2> res;
    res.Clone(sinogram);

    size_t nrow = res.Size(1);

//    sinosmoothed = np.apply_along_axis(uniform_filter1d, 0, sinogram, 10)
//    listdiff = np.sum(np.abs(sinogram - sinosmoothed), axis=0)
//    nmean = np.mean(listdiff)
//    listdiffbck = median_filter(listdiff, size)
//    listdiffbck[listdiffbck == 0.0] = nmean
//    listfact = listdiff / listdiffbck
//    listmask = detect_stripe(listfact, snr)
//    listmask = binary_dilation(listmask, iterations=1).astype(listmask.dtype)
//    listmask[0:2] = 0.0
//    listmask[-2:] = 0.0
//    listx = np.where(listmask < 1.0)[0]
//    listy = np.arange(nrow)
//    matz = sinogram[:, listx]
//    finter = interpolate.interp2d(listx, listy, matz, kind='linear')
//    listxmiss = np.where(listmask > 0.0)[0]
//    if len(listxmiss) > 0:
//        matzmiss = finter(listxmiss, listy)
//        sinogram[:, listxmiss] = matzmiss
//    # Use algorithm 5 to remove residual stripes
//    #sinogram = remove_large_stripe(sinogram, snr, size)

    kipl::base::TImage<float,2> res;

    return res;
}

kipl::base::TImage<float,2> VoStripeClean::removeAllStripe(kipl::base::TImage<float,2> &sinogram, float snr, size_t la_size, size_t sm_size)
{
    kipl::base::TImage<float,2> res;
    res.Clone(sinogram);
    res = remove_unresponsive_and_fluctuating_stripe(res, snr, la_size);
    res = remove_large_stripe(res, snr, la_size);
    res = removeStripeBasedSorting(res, sm_size);

    return res;
}

//# ----------------------------------------------------------------------------
//# Example of use:
//# sinogram = remove_stripe_based_sorting(sinogram, 31)
//# sinogram = remove_stripe_based_filtering(sinogram, 3, 31)
//# sinogram = remove_stripe_based_fitting(sinogram, 1, 5, 20)
//# sinogram = remove_unresponsive_and_fluctuating_stripe(sinogram1, 3, 81)
//# sinogram = remove_large_stripe(sinogram1, 3, 81)
//# sinogram = remove_all_stripe(sinogram, 3, 81, 31)