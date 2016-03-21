/**********************************************************\
 *
 * Hongwei Li
 * Copyright (c) Hongwei Li
 *
 * File Name:
 *
 *   LensFlare.h
 *
 * Abstract: 
 *
 *   The base class of all effects.
 * 
 * Author: 
 *
 *   Hongwei Li
 *
 * History:
 *   
 *   Created on 2010-10-02 by hongwei.li@family.ust.hk
 **********************************************************/

#ifdef _CH_
#pragma package <opencv>
#endif

#define CV_NO_BACKWARD_COMPATIBILITY

#ifndef _EiC
#include "cxcore.h"
#include "cv.h"
#endif

#ifndef LENS_FLARE_H
#define LENS_FLARE_H

class Effect
{
public:
    // \brief constructor.
    //
    // \param width the width of the effect image.
    // \param height ditto.
    Effect() 
    {
        m_pImage = 0;
        m_pRayCaster = 0;
    };

    ~Effect();

    IplImage* GetResult() 
    {
        return m_pImage;
    };

    RayCaster* GetRayCaster()
    {
        return m_pRayCaster;
    };

    // \brief initialization.
    // \return false if failed and true if OK.
    bool Init();

    // \brief generate the effect.
    void Run();

private:
    IplImage* m_pImage; // A float image.
    int m_width;
    int m_height;

    RayCaster* m_pRayCaster;
};


#endif // !LENS_FLARE_H

