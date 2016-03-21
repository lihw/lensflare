/**********************************************************\
 *
 * Hongwei Li
 * Copyright (c) Hongwei Li
 *
 * File Name:
 *
 *   ColorConv.cpp
 *
 * Abstract: 
 *
 *   Convert different color spaces.
 * 
 * Author: 
 *
 *   Hongwei Li
 *
 * History:
 *   
 *   Modified from conv.inl in gImage package 
 *       2010-09-17 by hongwei.li@family.ust.hk
 *
 **********************************************************/


#include <cstdio>

#ifndef COLOR_CONV_H
#define COLOR_CONV_H

void rgb2xyz(float* rgb, float* xyz);
void xyz2rgb(float* xyz, float* rgb);
void xyz2lab(float* xyz, float* lab);
void lab2xyz(float* lab, float* xyz);
void rgb2lab(float* rgb, float* lab);
void lab2rgb(float* lab, float* rgb);
void rgb2hsv(float* rgb, float* hsv);
void hsl2rgb(float* hsl, float* rgb);
void hsv2rgb(float* hsv, float* rgb);
void rgb2hsl(float* rgb, float* hsl);


// suppose the original file is in the sRGB colorspace
// http://www.brucelindbloom.com/index.html?Equations.html


// rgb and xyz can be at the same memory address
static inline
void rgb2xyz(float* rgb, float* xyz)
{
    float r = rgb[0];
    float g = rgb[1];
    float b = rgb[2];

    if (r < 0.04045f) r = r / 12.92f;
    else r = pow((r + 0.055f) / 1.055f, 2.4f);
    if (g < 0.04045f) g = g / 12.92f;
    else g = pow((g + 0.055f) / 1.055f, 2.4f);
    if (b < 0.04045f) b = b / 12.92f;
    else b = pow((b + 0.055f) / 1.055f, 2.4f);

    float M[][3] = {
        {0.4124564f,  0.3575761f,  0.1804375f,}, 
        {0.2126729f,  0.7151522f,  0.0721750f,},
        {0.0193339f,  0.1191920f,  0.9503041f,},
    };
        
    xyz[0] = M[0][0] * r + M[0][1] * g + M[0][2] * b;
    xyz[1] = M[1][0] * r + M[1][1] * g + M[1][2] * b;
    xyz[2] = M[2][0] * r + M[2][1] * g + M[2][2] * b;
}

static inline
void xyz2rgb(float* xyz, float* rgb)
{
    float x = xyz[0];
    float y = xyz[1];
    float z = xyz[2];
    
    float M[][3] = {
        { 3.2404542f, -1.5371385f, -0.4985314f,},
        {-0.9692660f,  1.8760108f,  0.0415560f,},
        { 0.0556434f, -0.2040259f,  1.0572252f,},
    };

    float r = M[0][0] * x + M[0][1] * y + M[0][2] * z;
    float g = M[1][0] * x + M[1][1] * y + M[1][2] * z;
    float b = M[2][0] * x + M[2][1] * y + M[2][2] * z;

    if (r <= 0.0031308) r = r * 12.92f;
    else r = 1.055f * pow(r, 1.0f / 2.4f) - 0.055f;
    if (g <= 0.0031308) g = g * 12.92f;
    else g = 1.055f * pow(g, 1.0f / 2.4f) - 0.055f;
    if (b <= 0.0031308) b = b * 12.92f;
    else b = 1.055f * pow(b, 1.0f / 2.4f) - 0.055f;
        
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

static inline
void xyz2lab(float* xyz, float* lab)
{
    float x = xyz[0] / 0.950470f; // reference white in D65
    float y = xyz[1];
    float z = xyz[2] / 1.088830f;

    if (x > 0.008856f) x = pow(x, 1.0f / 3.0f);
    else x = (x * 903.3f + 16.0f) / 116.0f;
    if (y > 0.008856f) y = pow(y, 1.0f / 3.0f);
    else y = (y * 903.3f + 16.0f) / 116.0f;
    if (z > 0.008856f) z = pow(z, 1.0f / 3.0f);
    else z = (z * 903.3f + 16.0f) / 116.0f;

    if (y > 0.008856f) 
        lab[0] = y * 116.0f - 16.0f;
    else
        lab[0] = y * 903.3f;

    lab[1] = (x - y) * 500.0f;
    lab[2] = (y - z) * 200.0f;
}

static inline
void lab2xyz(float* lab, float* xyz)
{
    float l = lab[0];
    float a = lab[1];
    float b = lab[2];

    float y = (l + 16.0f) / 116.0f;
    float x = a / 500.0f + y;
    float z = y - b / 200.0f;

    float x3 = x * x * x;
    if (x3 > 0.008856f) xyz[0] = x3;
    else xyz[0] = (116.0f * x - 16.0f) / 903.3f;

    float y3 = (l + 16.0f) / 116.0f;
    y3 = y3 * y3 * y3;
    if (l > 0.008856f * 903.3f) xyz[1] = y3;
    else xyz[1] = l / 903.3f;

    float z3 = z * z * z;
    if (z3 > 0.008856f) xyz[2] = z3;
    else xyz[2] = (116.0f * z - 16.0f) / 903.3f;

    xyz[0] *= 0.950470f;
    xyz[2] *= 1.088830f;
}

static inline
void rgb2lab(float* rgb, float* lab)
{
    float xyz[3];
    rgb2xyz(rgb, xyz);
    xyz2lab(xyz, lab);
}

static inline
void lab2rgb(float* lab, float* rgb)
{
    float xyz[3];
    lab2xyz(lab, xyz);
    xyz2rgb(xyz, rgb);
}

/**
 * \param rgb in range of [0,1]
 * \param hsv in range of [0,1]
 *
 * \note forget about the code style of funtions related 
 *   hsv and hsl cause I got them from Lei.
 *
 * \see rgb2xyz
 */
static inline
void rgb2hsl(float* rgb, float* hsl)
{
   float H, S, L;

   float var_R = rgb[0];           
   float var_G = rgb[1];
   float var_B = rgb[2];

   float var_Min = MIN(var_R, MAX(var_G, var_B));    //Min. value of RGB
   float var_Max = MAX(var_R, MAX(var_G, var_B));    //Max. value of RGB
   float del_Max = var_Max - var_Min;           //Delta RGB value

   L = (var_Max + var_Min) / 2;

   if (del_Max == 0) {                    //This is a gray, no chroma...
       H = 0;                             //HSL results from 0 to 1
       S = 0;
   } else {                               //Chromatic data...
       if ( L < 0.5 )
           S = del_Max / ( var_Max + var_Min );
       else
           S = del_Max / ( 2 - var_Max - var_Min );

       float del_R = (((var_Max - var_R ) / 6.f ) + (del_Max / 2.f)) / del_Max;
       float del_G = (((var_Max - var_G ) / 6.f ) + (del_Max / 2.f)) / del_Max;
       float del_B = (((var_Max - var_B ) / 6.f ) + (del_Max / 2.f)) / del_Max;

       if (var_R == var_Max)
           H = del_B - del_G;
       else if (var_G == var_Max)
           H = (1.f / 3.f) + del_R - del_B;
       else if ( var_B == var_Max)
           H = (2.f / 3.f) + del_G - del_R;

       if (H < 0)
           H += 1;
       if (H > 1)
           H -= 1;
   }
   hsl[0] = H;
   hsl[1] = S;
   hsl[2] = L;
}

/**
 *
 * \see rgb2hsl
 */
static inline
void rgb2hsv(float* rgb, float* hsv)
{
   float H, S, V;

   float var_R = rgb[0];          
   float var_G = rgb[1];
   float var_B = rgb[2];

   float var_Min = MIN(var_R, MIN(var_G, var_B));    //Min. value of RGB
   float var_Max = MAX(var_R, MAX(var_G, var_B));    //Max. value of RGB
   float del_Max = var_Max - var_Min  ;           //Delta RGB value

   V = var_Max;

   if ( del_Max == 0) {                    //This is a gray, no chroma...
       H = 0;                                //HSL results from 0 to 1
       S = 0;
   } else {                                  //Chromatic data...
       S = del_Max / var_Max;

       float del_R = (((var_Max - var_R) / 6.f) + (del_Max / 2.f)) / del_Max;
       float del_G = (((var_Max - var_G) / 6.f) + (del_Max / 2.f)) / del_Max;
       float del_B = (((var_Max - var_B) / 6.f) + (del_Max / 2.f)) / del_Max;

       if ( var_R == var_Max )
           H = del_B - del_G;
       else if ( var_G == var_Max )
           H = ( 1.f / 3.f ) + del_R - del_B;
       else if ( var_B == var_Max )
           H = ( 2.f / 3.f ) + del_G - del_R;

       if ( H < 0 )
           H += 1;
       if ( H > 1 )
           H -= 1;
   }

   hsv[0] = H;
   hsv[1] = S;
   hsv[2] = V;
}


static inline
float hue2rgb(float v1, float v2, float vH)
{
   if (vH < 0)
       vH += 1;
   if (vH > 1)
       vH -= 1;
   if (6 * vH < 1)
       return ( v1 + (v2 - v1) * 6 * vH);
   if (2 * vH < 1)
       return ( v2 );
   if ( 3 * vH < 2)
       return (v1 + (v2 - v1) * (2.f / 3.f - vH) * 6);
   return v1 ;
}

static inline
void hsl2rgb(float* hsl, float* rgb)
{
   float H, S, L;
   H = hsl[0];
   S = hsl[1];
   L = hsl[2];

   if ( S == 0 ) {                     // HSL from 0 to 1
       rgb[0] = L;                     // RGB results from 0 to 1
       rgb[1] = L;
       rgb[2] = L;
   } else {
       float var_1, var_2;
       if (L < 0.5)
           var_2 = L * (1 + S);
       else
           var_2 = (L + S) - (S * L);

       var_1 = 2 * L - var_2;

       rgb[0] = hue2rgb(var_1, var_2, H + (1.f / 3.f));
       rgb[1] = hue2rgb(var_1, var_2, H);
       rgb[2] = hue2rgb(var_1, var_2, H - (1.f / 3.f));
   }
}

static inline
void hsv2rgb(float* hsv, float* rgb)
{
   float R, G, B, H, S, V;
   H = hsv[0];
   S = hsv[1];
   V = hsv[2];

   if (S == 0) {                      //HSL from 0 to 1
       rgb[0] = V;                    //RGB results from 0 to 1
       rgb[1] = V;
       rgb[2] = V;
   }
   else
   {
       float var_h = H * 6.f;
       if (var_h == 6.f)
           var_h = 0;      //H must be < 1
       float var_i = floor(var_h) ;            //Or ... var_i = floor( var_h )
       float var_1 = V * (1 - S);
       float var_2 = V * (1 - S * (var_h - var_i));
       float var_3 = V * (1 - S * (1 - (var_h - var_i)));

       if      ( var_i == 0 ) { R = V     ; G = var_3 ; B = var_1; }
       else if ( var_i == 1 ) { R = var_2 ; G = V     ; B = var_1; }
       else if ( var_i == 2 ) { R = var_1 ; G = V     ; B = var_3; }
       else if ( var_i == 3 ) { R = var_1 ; G = var_2 ; B = V;     }
       else if ( var_i == 4 ) { R = var_3 ; G = var_1 ; B = V;     }
       else                   { R = V     ; G = var_1 ; B = var_2; }
       
       rgb[0] = R;                    //RGB results from 0 to 1
       rgb[1] = G;
       rgb[2] = B;
   }
}




#endif // !COLOR_CONV_H
