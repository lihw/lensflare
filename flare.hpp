/**********************************************************\
 *
 * Hongwei Li
 * Copyright (c) Hongwei Li
 *
 * File Name:
 *
 *   flare.hpp
 *
 * Abstract: 
 *
 *   Small disk-like shape in the lens flare effect.
 * 
 * Author: 
 *
 *   Hongwei Li
 *
 * History:
 *   
 *   Created on 2010-09-25 by hongwei.li@family.ust.hk 
 *
 **********************************************************/

#ifndef FLARE_HPP
#define FLARE_HPP

// \brief the basic one, just a cirle (thin ring)
class Flare
{
public:
    // \brief constructor
    // \param canvasWidth the width of the canvas.
    // \param canvasHeight ditto.
    // \param cx the x corodinate of the center.
    // \param cy ditto.
    // \pram radius the radius of the circle.
    // \param thickness the thickness of the circle.
    // \praram rgb the color of the ring.
    Flare(int canvasWidth, 
          int canvasHeight,
          int cx, 
          int cy, 
          float radius, 
          float thickness, 
          float rgb[])
    {
        m_canvasWidth = canvasWidth;
        m_canvasHeight = canvasHeight;

        m_cx = cx;
        m_cy = cy;

        m_radius = radius;

        m_innerRadius = radius - thickness * 0.5f;
        m_outerRadius = radius + thickness * 0.5f;

        m_thickness = thickness;

        m_rgb[0] = rgb[0];
        m_rgb[1] = rgb[1];
        m_rgb[2] = rgb[2];
    };

    // \brief get the pixel of the canvas in which
    // the circle is.
    //
    // \param i the pixel y coordinate.
    // \param j the pixel x coordinate.
    // \param c the returned color of the pixel.
    void GetPixel(int i, int j, float c[])
    {
        float dx = (float)(j - m_cx);
        float dy = (float)(i - m_cy);
        float d = sqrt(dx * dx + dy * dy);

        float d1 = d - m_innerRadius;
        float d2 = d - m_outerRadius;

        // Out of the circle.
        if (d1 < 0 || d2 > 0) 
        {
            c[0] = c[1] = c[2] = 0;
            return;
        }

        c[0] = m_rgb[0];
        c[1] = m_rgb[1];
        c[2] = m_rgb[2];
        
        // Anti-aliasing 
        if (d1 < 1.0f)
        {
            c[0] *= d1;
            c[1] *= d1;
            c[2] *= d1;
        }
        else if (d2 > -1.0f)
        {
            d2 = -d2;
            c[0] *= d2;
            c[1] *= d2;
            c[2] *= d2;
        }
    };

private:
    int m_canvasWidth; // FIXME: no use now.
    int m_canvasHeight;

    int m_cx;
    int m_cy;
    float m_radius;
    float m_thickness;
    float m_rgb[3];

    float m_innerRadius;
    float m_outerRadius;
};

// \brief the solid disk.
class FlareSolid
{
public:
    FlareSolid(int canvasWidth,
               int canvasHeight,
               int cx,
               int cy,
               float radius,
               float rgb[])
    {
        m_canvasWidth = canvasWidth;
        m_canvasHeight = canvasHeight;

        m_cx = cx;
        m_cy = cy;

        m_radius = radius;

        m_rgb[0] = rgb[0];
        m_rgb[1] = rgb[1];
        m_rgb[2] = rgb[2];
    };

    void GetPixel(int i , int j, float c[])
    {
        float dx = (float)(j - m_cx);
        float dy = (float)(i - m_cy);
        float d = sqrt(dx * dx + dy * dy);

        float o = d - m_radius;

        // Out of the circle.
        if (o > 0) 
        {
            c[0] = c[1] = c[2] = 0;
            return;
        }

        c[0] = m_rgb[0];
        c[1] = m_rgb[1];
        c[2] = m_rgb[2];
        
        // Anti-aliasing 
        if (o > -1.0f)
        {
            o = -o;

            c[0] *= o;
            c[1] *= o;
            c[2] *= o;
        }
    };

private:
    int m_canvasWidth; // FIXME: no use now.
    int m_canvasHeight;

    int m_cx;
    int m_cy;
    float m_radius;
    float m_rgb[3];
};

// \brief the solid disk with gradient filling inside.
class FlareGradient
{
public:
    FlareGradient(int canvasWidth,
               int canvasHeight,
               int cx,
               int cy,
               float radius,
               float rgb[],
               float gamma)
    {
        m_canvasWidth = canvasWidth;
        m_canvasHeight = canvasHeight;

        m_cx = cx;
        m_cy = cy;

        m_radius = radius;

        m_rgb[0] = rgb[0];
        m_rgb[1] = rgb[1];
        m_rgb[2] = rgb[2];

        m_gamma = gamma;
    };
    
    void GetPixel(int i , int j, float c[])
    {
        float dx = (float)(j - m_cx);
        float dy = (float)(i - m_cy);
        float d = sqrt(dx * dx + dy * dy);

        float o = d - m_radius;

        // Out of the circle.
        if (o > 0) 
        {
            c[0] = c[1] = c[2] = 0;
            return;
        }

        c[0] = m_rgb[0];
        c[1] = m_rgb[1];
        c[2] = m_rgb[2];

        // FIXME: the faster sigma computation
        // TODO: using lookup table?
        float sigma = pow(1.0f - d / m_radius, m_gamma);
        
        // Gradient
        c[0] *= sigma;
        c[1] *= sigma;
        c[2] *= sigma;
        
    };

private:
    int m_canvasWidth; // FIXME: no use now.
    int m_canvasHeight;

    int m_cx;
    int m_cy;
    float m_radius;
    float m_rgb[3];

    float m_gamma;
};

#endif // !FLARE_HPP
