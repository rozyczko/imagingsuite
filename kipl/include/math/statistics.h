// Statistics.h: interface for the Statistics class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_STATISTICS_H__B802B410_6183_11D1_8812_00C04FD8E524__INCLUDED_
#define AFX_STATISTICS_H__B802B410_6183_11D1_8812_00C04FD8E524__INCLUDED_

#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#ifdef _MSC_VER
#pragma once
#endif



/*! \brief Class to compute first and second order statistics of data
 *
 *  The class provides the posi 
 */

/// Namespace for numeric functions and support functions
namespace kipl {
namespace math {
    /// \brief A class to compute the statistics of an input sequence of data

    class Statistics
    {
    public:
        /// Returns the minimum value of the data
        double Min() const;
        /// Returns the maximum value of the data
        double Max() const;
        /// Resets the sum variables to zero
        int reset();
        /// Returns the number of elements added to the object
        size_t n() const;
        /// Sums two stochastic variables
        Statistics operator+(Statistics &s);

        /// Returns the standard deviation of the variable
        double s() const;
        /// Returns the variance of the variable
        double V() const;
        /// Returns the mean value of the variable
        double E() const;
        /// Returns the sum of the entered items
        double Sum() {return m_fSum;}
        /// Returns the square sum of the entered items
        double Sum2() {return m_fSum2;}
        /// Add a new item to the variable

        template<typename T>
        size_t put(T *_x, size_t N) {
            for (size_t i=0;i<N; i++) {
                put(_x[i]);
            }

            return N;
        }

        template<typename T>
        size_t put(T _x)
        {
			double x=static_cast<long double>(_x);
			m_fSum+=x;
			m_fSum2+=x*x;
			m_nNdata++;

			m_fMin=std::min(m_fMin,x);
			m_fMax=std::max(m_fMax,x);

			return m_nNdata;
        }

	/// Default constructor
        Statistics();
        /// Copy constructor
        Statistics(const Statistics &s);

        Statistics & operator=(const Statistics &s);

	/// Destructor
        virtual ~Statistics();

    private:
        /// The largest entered item
        double m_fMax;
        /// The smallest entered item
        double m_fMin;
        /// \f$\sum x_i^2\f$
        long double m_fSum2;
        /// \f$\sum x_i\f$
        long double m_fSum;
        /// Number of entered items
        size_t m_nNdata;
    };


}} // End namespace statistics
ostream& operator <<(ostream & os, kipl::math::Statistics & s);
#include "core/statistics.hpp"
#endif // !defined(AFX_STATISTICS_H__B802B410_6183_11D1_8812_00C04FD8E524__INCLUDED_)

