/**********************************************************\
 *
 * Hongwei Li
 * Copyright (c) Hongwei Li
 *
 * File Name:
 *
 *   common.h
 *
 * Abstract: 
 *
 *   common helper functions.
 * 
 * Author: 
 *
 *   Hongwei Li
 *
 * History:
 *   
 *   Created on 2010-10-05 by hongwei.li@family.ust.hk
 **********************************************************/

#include <cstdlib>
#include <cmath>
#include <cv.h>

#ifndef COMMON_H
#define COMMON_H

#ifndef M_PI
# define M_PI 3.1415926f
#endif

// \brief return a uniform random number within [-v, v].
static inline
float myRandom(float limit)
{
    return ((float)rand() / (float)RAND_MAX - 0.5f) * 2.0f * limit;
}

static inline
float myRandom(float inf, float sup)
{
    return ((float)rand() / (float)RAND_MAX) * (sup - inf) + inf;
}

static inline
float myRandom()
{
    return (float)rand() / (float)RAND_MAX;
}


class MyRandom {
public:
    MyRandom(unsigned long seed = 10001)
    {
        m_prevRandom = seed;
    };

    unsigned int GetUInt()
    {
        m_prevRandom =  rand31(m_prevRandom);

        return m_prevRandom;
    };

    int GetInt()
    {
        m_prevRandom =  rand31(m_prevRandom);

        return (int)m_prevRandom;
    };

    float GetFloat()
    {
        return (float)GetInt() / 0x7FFFFFFF;
    };

    float GetFloat(float inf, float sup)
    {
        assert(inf < sup);

        return GetFloat() * (sup - inf) + inf;
    }

    void SetSeed(unsigned long seed)
    {
        m_prevRandom = seed;
    };
    
    unsigned long GetSeed() const
    {
        return m_prevRandom;
    };

private:
    unsigned long m_prevRandom;

    // \brief Park-Miller "minimal standard" 31 bit
    // pseudo-random number generator, implemented with
    // David G. Carta's optimization: with 32 bit math
    // and without division.
    long unsigned int rand31(unsigned long int seed)
    {
        long unsigned int hi, lo;

        lo = 16807 * (seed & 0xFFFF);
        hi = 16807 * (seed >> 16);

        lo += (hi & 0x7FFF) << 16;
        lo += hi >> 15;

        if (lo > 0x7FFFFFFF)
        {
            lo -= 0x7FFFFFFF;
        }

        return (unsigned long int)lo;
    }
};

static inline
float mySqrt(float v)
{
    return sqrt(v);
}

static inline
float myPow(float v, float e)
{
    return pow(v, e);
}

// \brief return fading factor.
//
// \param t a value in [0, 1]
static inline
float fading(float t)
{
    return ((((10.2182f * t - 30.6413f) * t  + 32.0970f) * t - 12.0388f) * t - 0.6378f) * t + 1.0028f;
}

static inline
int clip(int x, int inf, int sup)
{
    if (x < inf) 
    {
        return inf;
    }
    else if (x > sup)
    {
        return sup;
    }
    
    return x;
}

// Liang-Barsky line clipping algorithm.
// Looks lots of optimization should be done here.
static inline
void clip(int& x, int& y, 
         int x0, int y0,
         int bx, int by)
{
    if (x <= bx && x >= 0 &&
        y <= by && y >= 0)
    {
        return ;
    }

    float xdelta = (float)(x - x0);
    float ydelta = (float)(y - y0);

    float t = 1.0f, tt;
    
    if (y != y0)
    {
        // top y.
        tt = -(float)y0 / ydelta;
        if (tt < t && tt > 0) 
        {
            t = tt;
        }
        // bottom y
        tt = (float)(by - y0) / ydelta;
        if (tt < t && tt > 0) 
        {
            t = tt;
        }
    }

    if (x != x0)
    {
        // right x
        tt = (float)(bx - x0) / xdelta;
        if (tt < t && tt > 0) 
        {
            t = tt;
        }
        // left x
        tt = -(float)(x0) / xdelta;
        if (tt < t && tt > 0) 
        {
            t = tt;
        }
    }

    x = x0 + (int)(xdelta * t);
    y = y0 + (int)(ydelta * t);

    if (x < 0)
    {
        x = 0;
    }
    if (x > bx)
    {
        x = bx;
    }
    if (y < 0)
    {
        y = 0;
    }
    if (y > by)
    {
        y = by;
    }
}

/*
// \brief approximation of gaussian integral.
double P_1(double x)
{
    // Based on Abramowitz and Stegun, 26.2.16, p. 932
    // from C. Hastings, Approximations for Digital Computers
    // |e(x)| < 1.0 * 10^-5

    const float a1 = 0.4361836;
    const float a2 = -0.1201676;
    const float a3 = 0.9372980;
    const float p = 0.3326700;
    const float t = 1.0 / (1.0 + p*x);

    // return 1-Z(x) * (a1*t + a2*t*t + a3*t*t*t);
    return 1-Z(x) * (t*(a1 + t*(a2 + a3*t)));
}
*/


#endif // !COMMON_H
