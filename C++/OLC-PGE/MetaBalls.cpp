#include <iostream>
#include <olcPixelGameEngine.h>
#include <vector>

using namespace std;

//2D Metaballs travelling on some Lissajous curves
//Uses Javidx9's OneLoneCoder PixelGameEngine
//Add the header to your include path first




class MetaBalls : public olc::PixelGameEngine
{
public:
    MetaBalls()
    {
        sAppName = "MetaBalls";
    }

    struct Point //Struct defining the metaball data
    {
        double x, y, size, speed, xdiv,  ydiv;
        int col;
    };

    vector<Point> source; //Vector for holding metaballs
    int h, w; //Width and height
    double brightness; //Brightness
    int maxSource =6;
    float t = 0; //Time
    int timeMul=10; //Time multiplier
    float r, g, b; //RGB components
    bool OnUserCreate()
    {
        //srand(time(NULL));
        h = ScreenHeight();
        w = ScreenWidth();
        int col = 0;
        for (int i = 0; i < maxSource; i++)
        {
            Point p;
            p.x = 0;
            p.y = 0;
            p.speed = 1 + (rand() % 2)/2;
            p.xdiv = 3 + rand() % (1+i);
            p.ydiv = 3 + rand() % (1+i);
            p.col = col%3;
            col++;
            source.push_back(p);
        }
     

        return true;
    }

    bool OnUserUpdate(float fElapsedTime)
    {     
        Clear(olc::BLACK);
        //Calculate a new position on for each ball
        for (int i = 0; i < maxSource; i++)
        {            
            source[i].x = (w / 2) + (w / source[i].xdiv) * sin(t * source[i].speed * source[i].xdiv * 3.14 / 180);
            source[i].y = (h / 2) + (h / source[i].ydiv) * cos(t * source[i].speed * source[i].ydiv * 3.14 / 180);
        }
        
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                brightness = 0.0;
                //For each pixel, calculate it's distance from the center of each metaball
                //Add these values together to get a brightness value
                for (int i = 0; i < maxSource; i++)
                {
                    if (((x - source[i].x) * (x - source[i].x) + (y - source[i].y) * (y - source[i].y)) > 0)
                        brightness += (1.0 / ((x - source[i].x) * (x - source[i].x) + (y - source[i].y) * (y - source[i].y))) / .001;

                    //Do the same for RGB components
                    if (source[i].col == 0)
                    {
                        r += (1.0 / ((x - source[i].x) * (x - source[i].x) + (y - source[i].y) * (y - source[i].y))) / .001;
                    }

                    else if (source[i].col == 1)
                    {
                        g += (1.0 / ((x - source[i].x) * (x - source[i].x) + (y - source[i].y) * (y - source[i].y))) / .001;
                    }   

                    else
                        b += (1.0 / ((x - source[i].x) * (x - source[i].x) + (y - source[i].y) * (y - source[i].y))) / .001;
                }                
                r += brightness / 1.5;
                g += brightness / 1.5;
                b += brightness / 2;               
                r > 1 ? r = 255 : r *= 255.0;
                g > 1 ? g = 255 : g *= 255.0;
                b > 1 ? b = 255 : b *= 255.0;
                Draw(x, y, olc::Pixel((int)r, (int)g, (int)b));
                r = g = b = 0.0;

            }
        }
        t += timeMul*fElapsedTime;
        return true;
    }

};




int main()
{
    MetaBalls mb;
    if (mb.Construct(320, 240, 2, 2))
        mb.Start();

    return 0;
}

