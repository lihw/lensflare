/**********************************************************\
 *
 * Hongwei Li
 * Copyright (c) Hongwei Li
 *
 * File Name:
 *
 *   main.cpp
 *
 * Abstract: 
 *
 *   The main entry of LensFlare project.
 * 
 * Author: 
 *
 *   Hongwei Li
 *
 * History:
 *   
 *   Created on 2010-09-24
 *
 **********************************************************/

#ifdef _CH_
#pragma package <opencv>
#endif

#define CV_NO_BACKWARD_COMPATIBILITY

#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#include <cmath>
#include <cstdlib>
#endif

#include "effect01_glowball.h"
#include "effect02_spikeball.h"
#include "effect03_starfilter.h"
#include "effect05_circlespread.h"
#include "effect09_stripe.h"
#include "effect10_randomfan.h"
#include "effect15_singlepoly.h"
#include "effect19_sparkle.h"

IplImage* g_pImage = 0;

int g_effectId = 19;

enum {
    EFFECT01     = 1,
    EFFECT02     = 2,
    EFFECT03     = 3,
    EFFECT04     = 4,
    EFFECT05     = 5,
    EFFECT06     = 6,
    EFFECT07     = 7,
    EFFECT08     = 8,
    EFFECT09     = 9,
    EFFECT10     = 10,
    EFFECT11     = 11,
    EFFECT12     = 12,
    EFFECT13     = 13,
    EFFECT14     = 14,
    EFFECT15     = 15,
    EFFECT16     = 16,
    EFFECT17     = 17,
    EFFECT18     = 18,
    EFFECT19     = 19,
    EFFECT20     = 20,
};

effect01_glowball::Effect*      g_pEffect01;
effect02_spikeball::Effect*     g_pEffect02;
effect03_starfilter::Effect*    g_pEffect03;
effect05_circlespread::Effect*  g_pEffect05;
effect10_randomfan::Effect*     g_pEffect10;
effect09_stripe::Effect*        g_pEffect09;
effect15_singlepoly::Effect*    g_pEffect15;
effect19_sparkle::Effect*       g_pEffect19;


// The parameters of rays.
static int g_rayNumber = 10;
static int g_rayLength = 20;
static int g_rayThickness = 20;
static int g_rayAngle    = 133;

static 
void ShowResult()
{
    switch (g_effectId)
    {
        case EFFECT01: cvConvert(g_pEffect01->GetResult(), g_pImage); break;
        case EFFECT02: cvConvert(g_pEffect02->GetResult(), g_pImage); break;
        case EFFECT03: cvConvert(g_pEffect03->GetResult(), g_pImage); break;
        case EFFECT05: cvConvert(g_pEffect05->GetResult(), g_pImage); break;
        case EFFECT09: cvConvert(g_pEffect09->GetResult(), g_pImage); break;
        case EFFECT10: cvConvert(g_pEffect10->GetResult(), g_pImage); break;
        case EFFECT15: cvConvert(g_pEffect15->GetResult(), g_pImage); break;
        case EFFECT19: cvConvert(g_pEffect19->GetResult(), g_pImage); break;
        default:
            cvZero(g_pImage);
            fprintf(stderr, "Err: Not available!\n");
            break;
    }

    cvShowImage("Lens Flare", g_pImage);
}

static
void onTrackbar0(int pos)
{
    ShowResult();
}

static
void onTrackbar1(int pos)
{
    switch (g_effectId)
    {
        case EFFECT01:
            g_pEffect01->SetRingSoftness(g_rayNumber);
            //g_pEffect01->SetRampGamma(g_rayNumber);
            g_pEffect01->Draw();
            break;
        case EFFECT02:
            g_pEffect02->SetNumber(g_rayNumber);
            g_pEffect02->Draw();
            break;
        case EFFECT03:
            //g_pEffect03->SetCount(g_rayNumber);
            g_pEffect03->SetThickness(g_rayNumber);
            g_pEffect03->Draw();
            break;
        case EFFECT05:
            g_pEffect05->SetCount(g_rayNumber);
            g_pEffect05->Draw();
            break;
        case EFFECT09:
            g_pEffect09->SetThickness(g_rayNumber);
            g_pEffect09->Draw();
            break;
        case EFFECT10:
            g_pEffect10->SetNumber(g_rayNumber);
            g_pEffect10->Draw();
            break;
        case EFFECT15:
            g_pEffect15->SetCount(g_rayNumber);
            g_pEffect15->Draw();
            break;
        case EFFECT19:
            g_pEffect19->SetCount(g_rayNumber);
            g_pEffect19->Draw();
            break;
    }

    ShowResult();
}

// \brief adjust the ray length.
static
void onTrackbar2(int pos)
{
    switch (g_effectId)
    {
        case EFFECT01:
            g_pEffect01->SetRingTaper(g_rayLength);
            //g_pEffect01->SetRampScale(g_rayLength);
            g_pEffect01->Draw();
            break;
        case EFFECT02:
            g_pEffect02->SetScale(g_rayLength);
            g_pEffect02->Draw();
            break;
        case EFFECT03:
            g_pEffect03->SetScale(g_rayLength);
            g_pEffect03->Draw();
            break;
        case EFFECT05:
            g_pEffect05->SetSpread(g_rayLength);
            g_pEffect05->Draw();
            break;
        case EFFECT09:
            g_pEffect09->SetLength(g_rayLength);
            g_pEffect09->Draw();
            break;
        case EFFECT10:
            g_pEffect10->SetScale(g_rayLength);
            g_pEffect10->Draw();
        case EFFECT15: 
            g_pEffect15->SetScale(g_rayLength);
            g_pEffect15->Draw();
            break;
        case EFFECT19: 
            g_pEffect19->SetScale(g_rayLength);
            g_pEffect19->Draw();
            break;
    }
    ShowResult();
}

// \brief adjust the ray brightness
static
void onTrackbar3(int pos)
{
    float color[3];
    color[0] = color[1] = color[2] = 255.0f * (float)pos / 100.0f;

    switch (g_effectId)
    {
        case EFFECT01:
            g_pEffect01->SetOuterColor(color);
            g_pEffect01->Draw();
            break;
        case EFFECT02:
            g_pEffect02->SetColor(color);
            g_pEffect02->Draw();
            break;
        case EFFECT03:
            g_pEffect03->SetColor(color);
            g_pEffect03->Draw();
            break;
        case EFFECT05:
            g_pEffect05->SetColor(color);
            g_pEffect05->Draw();
            break;
        case EFFECT09:
            g_pEffect09->SetColor(color);
            g_pEffect09->Draw();
            break;
        case EFFECT10:
            g_pEffect10->SetColor(color);
            g_pEffect10->Draw();
            break;
        case EFFECT15:
            g_pEffect15->SetColor(color);
            g_pEffect15->Draw();
            break;
        case EFFECT19:
            g_pEffect19->SetColor(color);
            g_pEffect19->Draw();
            break;
    }
    ShowResult();
}

// \brief adjust the ray angle
static
void onTrackbar4(int pos)
{
    float rayAngle = M_PI * (float)g_rayAngle / 180.0f;

    switch (g_effectId)
    {
        case EFFECT02:
            g_pEffect02->SetAngle(rayAngle);
            g_pEffect02->Draw();
            break;
        case EFFECT03:
            g_pEffect03->SetAngle(rayAngle);
            g_pEffect03->Draw();
            break;
        case EFFECT05:
            g_pEffect05->SetAngle(rayAngle);
            g_pEffect05->Draw();
            break;
        case EFFECT09:
            g_pEffect09->SetAngle(rayAngle);
            g_pEffect09->Draw();
            break;
        case EFFECT10:
            g_pEffect10->SetAngle(rayAngle);
            g_pEffect10->Draw();
            break;
        case EFFECT15:
            g_pEffect15->SetAngle(rayAngle);
            g_pEffect15->Draw();
            break;
        case EFFECT19:
            g_pEffect19->SetRandSeed(g_rayAngle);
            g_pEffect19->Draw();
        default:
            break;
    }

    ShowResult();
}

int main(int argc, char* argv[])
{
    // Load the input image and texture.
    g_pImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);

    // FIXME: Change the rand seed here.
    srand(10001);

    // Create the glare effect object.
    float color[] = {255, 255, 255};
    float color1[] = {255, 0, 0};

    g_pEffect01 = new effect01_glowball::Effect(
            640, 
            480,
            20,
            30,
            20,
            g_rayLength,
            g_rayNumber,          
            color,
            color1);
    if (!g_pEffect01->Init())
    {
        fprintf(stderr, "Err: effect01 init failed.\n");
        return -1;
    }
    //g_pEffect01->SetPosition(100, 100);
    g_pEffect01->Draw();


    g_pEffect02 = new effect02_spikeball::Effect(
            640, 
            480,
            g_rayLength,           
            g_rayNumber,
            color,
            M_PI * (float)g_rayAngle / 180.0f);
    if (!g_pEffect02->Init())
    {
        fprintf(stderr, "Err: effect02 init failed.\n");
        return -1;
    }
    g_pEffect02->Draw();
    
    g_pEffect03 = new effect03_starfilter::Effect(
            640, 
            480,
            g_rayNumber,           
            g_rayLength,
            color,
            M_PI * (float)g_rayAngle / 180.0f,
            5,
            10);
    if (!g_pEffect03->Init())
    {
        fprintf(stderr, "Err: effect03 init failed.\n");
        return -1;
    }
    g_pEffect03->Draw();
    
    g_pEffect05 = new effect05_circlespread::Effect(
            640, 
            480,
            50,
            g_rayNumber,           
            5,
            50,
            101,
            102,
            M_PI * (float)g_rayAngle / 180.0f,
            color);
    if (!g_pEffect05->Init())
    {
        fprintf(stderr, "Err: effect05 init failed.\n");
        return -1;
    }
    g_pEffect05->Draw();
    
    g_pEffect09 = new effect09_stripe::Effect(
            640, 
            480,
            g_rayLength,           
            g_rayNumber,
            color1,
            true,
            color,
            M_PI * (float)g_rayAngle / 180.0f);
    if (!g_pEffect09->Init())
    {
        fprintf(stderr, "Err: effect09 init failed.\n");
        return -1;
    }
    g_pEffect09->Draw();

    g_pEffect10 = new effect10_randomfan::Effect(
            640, 
            480,
            g_rayNumber,           
            g_rayLength,
            color,
            M_PI * (float)g_rayAngle / 180.0f);
    if (!g_pEffect10->Init())
    {
        fprintf(stderr, "Err: effect10 init failed.\n");
        return -1;
    }
    g_pEffect10->Draw();
    
    g_pEffect15 = new effect15_singlepoly::Effect(
            640, 
            480,
            g_rayLength,
            g_rayNumber,
            0,
            color,
            M_PI * (float)g_rayAngle / 180.0f);
    if (!g_pEffect15->Init())
    {
        fprintf(stderr, "Err: effect15 init failed.\n");
        return -1;
    }
    g_pEffect15->Draw();
    
    g_pEffect19 = new effect19_sparkle::Effect(
            640, 
            480,
            g_rayNumber,
            g_rayLength,
            color,
            g_rayAngle);
    if (!g_pEffect19->Init())
    {
        fprintf(stderr, "Err: effect19 init failed.\n");
        return -1;
    }
    g_pEffect19->Draw();
    
   
    // Create window.
    cvNamedWindow("Lens Flare", 1);
    
    cvCreateTrackbar("Effect",     "Lens Flare", &g_effectId,     20,  onTrackbar0);
    cvCreateTrackbar("Count",      "Lens Flare", &g_rayNumber,    100, onTrackbar1);
    cvCreateTrackbar("Scale",      "Lens Flare", &g_rayLength,    100, onTrackbar2);
    cvCreateTrackbar("Brightness", "Lens Flare", &g_rayThickness, 100, onTrackbar3);
    cvCreateTrackbar("Angle",      "Lens Flare", &g_rayAngle,     180,  onTrackbar4);

    ShowResult();
    
    // Enter the main loop.
    while(1){
        int key = cvWaitKey(10);

        // Exit.
        if (key == 27)
        {
            break;
        }

        switch (key)
        {
            case 'd':
                {
                    static int fileId = 1;
                    char filename[1024];
                    sprintf(filename, "dumpsrc_%04d.bmp", fileId);
                    cvSaveImage(filename, g_pImage);
                }
                break;
        }
    }
    
    cvDestroyWindow("Lens Flare");

    // The end of the main loop.
    cvReleaseImage(&g_pImage);

    delete g_pEffect01;
    delete g_pEffect02;
    delete g_pEffect03;
    delete g_pEffect09;
    delete g_pEffect10;
    delete g_pEffect15;

    return 0;
}

