#ifndef VOSTRIPECLEAN_H
#define VOSTRIPECLEAN_H

#include <base/timage.h>
#include <list>
class VoStripeClean
{
public:
    VoStripeClean();
    /// \brief  Algorithm 3 in the paper. Remove stripes using the sorting technique. Work particularly well for removing partial stripes. Angular direction is along the axis 0
    /// \param sinogram: 2D array.
    /// \param size: window size of the median filter.
    /// \returns stripe-removed sinogram.
    kipl::base::TImage<float,2> removeStripeBasedSorting(kipl::base::TImage<float,2> &sinogram, size_t size);

    /// \brief Algorithm 2 in the paper. Remove stripes using the filtering technique. Angular direction is along the axis 0
    ///  \param sinogram: 2D array.
    ///  \param sigma: sigma of the Gaussian window which is used to separate the low-pass and high-pass components of the intensity profiles of each column.
    ///  \param size: window size of the median filter.
    ///  \returns stripe-removed sinogram.
    kipl::base::TImage<float,2> remove_stripe_based_filtering(kipl::base::TImage<float,2> &sinogram, float sigma, size_t size);

    /// \brief Algorithm 1 in the paper. Remove stripes using the fitting technique. Angular direction is along the axis 0
    /// \param sinogram: 2D array.
    /// \param order: polynomical fit order.
    /// \param sigmax, sigmay: sigmas of the Gaussian window.
    /// \returns stripe-removed sinogram.
    kipl::base::TImage<float,2> remove_stripe_based_fitting(kipl::base::TImage<float,2> &sinogram, int order, float sigmax, float sigmay);

    /// \brief Algorithm 5 in the paper. Remove large stripes by: locating stripes, normalizing to remove full stripes, using the sorting technique to remove partial stripes. Angular direction is along the axis 0.
    /// \param sinogram: 2D array.
    /// \param snr: ratio used to discriminate between useful information and noise.
    /// \param size: window size of the median filter.
    /// \returns stripe-removed sinogram.
    kipl::base::TImage<float,2> remove_large_stripe(kipl::base::TImage<float,2> &sinogram, float snr, size_t size);

    ///    \brief Algorithm 6 in the paper. Remove unresponsive or fluctuating stripes by locating stripes, correcting by interpolation. Angular direction is along the axis 0.
    ///    \param sinogram: 2D array.
    ///    \param snr: ratio used to discriminate between useful information and noise
    ///    \param size: window size of the median filter.
    ///    \returns stripe-removed sinogram.
    kipl::base::TImage<float,2> remove_unresponsive_and_fluctuating_stripe(kipl::base::TImage<float,2> &sinogram, float snr, size_t size);

    ///    \brief Remove all types of stripe artifacts by combining algorithm 6, 5, and 3. Angular direction is along the axis 0.
    ///    \param sinogram: 2D array.
    ///    \param snr: ratio used to discriminate between useful information and noise
    ///    \param la_size: window size of the median filter to remove large stripes.
    ///    \param sm_size: window size of the median filter to remove small-to-medium stripes.
    ///    \return stripe-removed sinogram.
    kipl::base::TImage<float,2> removeAllStripe(kipl::base::TImage<float,2> &sinogram, float snr, size_t la_size, size_t sm_size);



private:
    /// \brief Create a 2D Gaussian window.
    /// \param height
    /// \param width: shape of the window.
    /// \param sigmax
    /// \param sigmay: sigmas of the window.
    /// \returns 2D window.
    kipl::base::TImage<float,2> _2d_window_ellipse(size_t height, size_t width, float sigmax, float sigmay);

    /// \brief Filtering an image using 2D Gaussian window.
    /// \param mat: 2D array.
    /// \param sigmax, sigmay: sigmas of the window.
    /// \param pad: padding for FFT
    /// \returns filtered image.
    kipl::base::TImage<float,2> _2d_filter(kipl::base::TImage<float,2> mat, float sigmax, float sigmay, size_t pad);

    ///    Algorithm 4 in the paper. Used to locate stripe positions.
    ///    Parameters: - listdata: 1D normalized array.
    ///                - snr: ratio used to discriminate between useful
    ///                    information and noise.
    ///    Return:     - 1D binary mask.
    std::list<size_t> detect_stripe(std::list<size_t >listdata, float snr);

};

#endif // VOSTRIPECLEAN_H




// ----------------------------------------------------------------------------
// Example of use:
// sinogram = remove_stripe_based_sorting(sinogram, 31)
// sinogram = remove_stripe_based_filtering(sinogram, 3, 31)
// sinogram = remove_stripe_based_fitting(sinogram, 1, 5, 20)
// sinogram = remove_unresponsive_and_fluctuating_stripe(sinogram1, 3, 81)
// sinogram = remove_large_stripe(sinogram1, 3, 81)
// sinogram = remove_all_stripe(sinogram, 3, 81, 31)
