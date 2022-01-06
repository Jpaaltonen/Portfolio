// Pendulum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "OlcPixelGameEngine.h"

using namespace std;

//A multiple weight pendulum simulation
//Uses Javidx9's OneLoneCoder PixelGameEngine
//Add the header to your include path first

class Pendulum :public olc::PixelGameEngine
{
public:
	struct weight
	{
		int x, y, m, l;	//Weight position, mass, length of rod
		float av, aa; //Angular velocity and acceleration
		float theta; //Angle
	};

	vector<weight> weights;
	vector<olc::Pixel> buf; //A screen buffer - the curve is plotted to the buffer and drawn from there


	const int MAXWEIGHTS = 2;
	const int BRIGHTNESS = 25; //How bright will the colour be for the plotting curve
	const float HARDNESS = 3;  //Divisor to determine the brightness of neighbouring pixels
	int cx, cy, h, w; //Screen center, width and height
	float g;
	float t = 0, limit = 1.f;


	bool OnUserCreate() override
	{
		srand(time(NULL));
		w = ScreenWidth();
		h = ScreenHeight();
		cx = w / 2;
		cy = h / 2;
		g = 2;
		for (int i = 0; i < h * w; i++)
			buf.push_back(olc::BLACK);

		//First entry in the vector is the hinge point
		weight pw;
		pw.av = 0;
		pw.aa = 0;
		pw.m = 0;
		pw.l = 0;
		pw.theta = 0;
		pw.x = cx;
		pw.y = cy;

		weights.push_back(pw);
		for (int i = 0; i < MAXWEIGHTS; i++)
		{
			weight pw;
			pw.av = 0;
			pw.aa = 0;
			//pw.m = (1 + rand() % 2) * 10; //Random weight
			pw.m = 10; //Uniform weight
			//pw.l = (10 + rand() % 5) * 10; //Random length
			//pw.l = 25+50*i; //Increasing length
			pw.l = 125; //Uniform length
			pw.theta = 3.14 /2; //90 degree angle - 0 points down and the rotation is anti-clockwise
			weights.push_back(pw);
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		//Draw the curves the weights make
		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++)
			{
				Draw(x, y, buf[x + y * w]);
			}

		float a, b, c, d, e; //Just to make the equation more readable

		//Physics calculations - there's probably something wrong with these, as the motion does not completely correspond to the example footage
		//Furthermore, I'm not actually sure how accurate the equation gets when you add more weights in the pendulum.
		//Do you treat each weight like the second weight in the double pendulum, or somehow else?
		//It's not absolutely horrendous looking though

		//First weight is calculated separately, since we apply another calculation to the rest of the weights
		a = -g * (2 * weights[1].m + weights[2].m) * sin(weights[1].theta);
		b = -weights[2].m * g * sin(weights[1].theta - 2 * weights[2].theta);
		c = -2 * sin(weights[1].theta - weights[2].theta) * weights[2].m;
		d = weights[2].av * weights[2].av * weights[2].l + weights[1].av * weights[1].av * weights[1].l * cos(weights[1].theta - weights[2].theta);
		e = weights[1].l * (2 * weights[1].m + weights[2].m - weights[2].m * cos(2 * weights[1].theta - 2 * weights[2].theta));
		weights[1].aa = (a + b + c * d) / e;

		for (int i = 2; i <= MAXWEIGHTS; i++)
		{		
			a = 2 * sin(weights[i - 1].theta - weights[i].theta);
			b = weights[i - 1].av * weights[i - 1].av * weights[i - 1].l * (weights[i - 1].m + weights[i].m);
			c = g * (weights[i - 1].m + weights[i].m) * cos(weights[i - 1].theta);
			d = weights[i].av * weights[i].av * weights[i].l * weights[i].m * cos(weights[i - 1].theta - weights[i].theta);
			e = weights[i].l * (2 * weights[i - 1].m + weights[i].m - weights[i].m * cos(2 * weights[i - 1].theta - 2 * weights[i].theta));
			weights[i].aa = (a * (b + c + d)) / e;
		}		

		//Update the positions, angular velocities and angles and draw the pendulum
		for (int i = 1; i <= MAXWEIGHTS; i++)
		{		
			weights[i].x = weights[i - 1].x + weights[i].l * sin(weights[i].theta);
			weights[i].y = weights[i - 1].y + weights[i].l * cos(weights[i].theta);
			weights[i].av += weights[i].aa * fElapsedTime;
			weights[i].theta += weights[i].av;
			DrawLine(weights[i - 1].x, weights[i - 1].y, weights[i].x, weights[i].y);
			FillCircle(weights[i].x, weights[i].y, weights[i].m, olc::BLUE);
		}

		//Weights start from index 1, so changing the starting value between 1-MAXWEIGHTS determines how many curves will be plotted
		for (int i = MAXWEIGHTS; i <= MAXWEIGHTS; i++)
		{
			if (weights[i].x > 0 && weights[i].x < w && weights[i].y>0 && weights[i].y < h)
			{
				//BW visualisization
				//Increase the rgb components of the pixel in the buffervector
				buf[weights[i].x + weights[i].y * w].r = buf[weights[i].x + weights[i].y * w].g = buf[weights[i].x + weights[i].y * w].b += BRIGHTNESS;
				
				//Multi-colour
				/*if (i == 1)
					buf[weights[i].x + weights[i].y * w].r += BRIGHTNESS;
				if (i % 2 == 0 && i % 4 != 0)
				{
					buf[weights[i].x + weights[i].y * w].r += BRIGHTNESS;
					buf[weights[i].x + weights[i].y * w].g += BRIGHTNESS;
				}
				if (i % 3 == 0)
				{
					buf[weights[i].x + weights[i].y * w].r += BRIGHTNESS;
					buf[weights[i].x + weights[i].y * w].b += BRIGHTNESS;
				}
				if (i % 4 == 0)
				{
					buf[weights[i].x + weights[i].y * w].b += BRIGHTNESS;
					buf[weights[i].x + weights[i].y * w].g += BRIGHTNESS;
				}*/
			}

			if (weights[i].x > 1 && weights[i].x < w - 1 && weights[i].y>1 && weights[i].y < h - 1)
			{
				//BW
				buf[weights[i].x - 1 + weights[i].y * w].r = buf[weights[i].x - 1 + weights[i].y * w].g = buf[weights[i].x - 1 + weights[i].y * w].b += BRIGHTNESS / HARDNESS;
				buf[weights[i].x + 1 + weights[i].y * w].r = buf[weights[i].x + 1 + weights[i].y * w].g = buf[weights[i].x + 1 + weights[i].y * w].b += BRIGHTNESS / HARDNESS;
				buf[weights[i].x + (weights[i].y - 1) * w].r = buf[weights[i].x + (weights[i].y - 1) * w].g = buf[weights[i].x + (weights[i].y - 1) * w].b += BRIGHTNESS / HARDNESS;
				buf[weights[i].x + (weights[i].y + 1) * w].r = buf[weights[i].x + (weights[i].y + 1) * w].g = buf[weights[i].x + (weights[i].y + 1) * w].b += BRIGHTNESS / HARDNESS;

				//Multi-colour
				/*if (i == 1)
				{
					buf[weights[i].x - 1 + weights[i].y * w].r += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + 1 + weights[i].y * w].r += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y - 1) * w].r += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y + 1) * w].r += BRIGHTNESS / HARDNESS;
				}

				if (i % 2 == 0 && i % 4 != 0)
				{
					buf[weights[i].x - 1 + weights[i].y * w].r += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + 1 + weights[i].y * w].r += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y - 1) * w].r += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y + 1) * w].r += BRIGHTNESS / HARDNESS;

					buf[weights[i].x - 1 + weights[i].y * w].g += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + 1 + weights[i].y * w].g += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y - 1) * w].g += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y + 1) * w].g += BRIGHTNESS / HARDNESS;
				}
				if (i % 3 == 0)
				{
					buf[weights[i].x - 1 + weights[i].y * w].r += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + 1 + weights[i].y * w].r += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y - 1) * w].r += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y + 1) * w].r += BRIGHTNESS / HARDNESS;

					buf[weights[i].x - 1 + weights[i].y * w].b += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + 1 + weights[i].y * w].b += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y - 1) * w].b += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y + 1) * w].b += BRIGHTNESS / HARDNESS;
				}
				if (i % 4 == 0)
				{
					buf[weights[i].x - 1 + weights[i].y * w].g += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + 1 + weights[i].y * w].g += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y - 1) * w].g += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y + 1) * w].g += BRIGHTNESS / HARDNESS;

					buf[weights[i].x - 1 + weights[i].y * w].b += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + 1 + weights[i].y * w].b += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y - 1) * w].b += BRIGHTNESS / HARDNESS;
					buf[weights[i].x + (weights[i].y + 1) * w].b += BRIGHTNESS / HARDNESS;
				}*/
			}
		}
		DrawString(1,1,"Click LMB to place the pendulum on cursor - Hold LMB to drag the pendulum");
		if (GetMouse(0).bHeld)
		{
			weights[0].x = GetMouseX();
			weights[0].y = GetMouseY();
		}
		return true;

	}

};





int main()
{
	Pendulum p;
	if (p.Construct(640, 480, 1, 1))
		p.Start();
}
