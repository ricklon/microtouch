/* 
** Copyright (c) 2011, Rick Anderson 
**  
** Permission to use, copy, modify, and/or distribute this software for  
** any purpose with or without fee is hereby granted, provided that the  
** above copyright notice and this permission notice appear in all copies.  
**  
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL  
** WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED  
** WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR  
** BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES  
** OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,  
** WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  
** ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS  
** SOFTWARE.  
*/

//Hello graphics
#include "Platform.h"

#define GREY(_x) TOCOLOR(_x,_x,_x)
#define YELLOW (TOCOLOR(0xFA,0xFA,0x00))
/*
short RGBToColor(short r, short g, short b)
{
	r = bound(r,0,255);
	g = bound(g,0,255);
	b = bound(b,0,255);
	return TOCOLOR(r,g,b);
}
*/

#define TOTALENERGY 240
int CurrentEnergy;

class Thermo
{
public:
	void Draw(int x, int y, int color)
	{
		//Freshen the background
		background();	

		//The tap
		Graphics.Circle(x,y,10,color,true);			


	}

	void setup()
	{			CurrentEnergy = 240;		//One time don't set to 0
				background();	
				Graphics.Rectangle(0, 0, 240, 40, YELLOW);//Top
				DotDrawStr(PStr(Shell_AppName()),8,18,68,RED,true);
	}
	
	//x is percentage of energy between 0 and 100
	void drawEnergy(int n)
	{
		int energy = n;		
		//Graphics.Rectangle(0, 0, energy ,40 , TOCOLOR( 0xFF, 0xFF, 0xFF));//Energy
		Graphics.Rectangle(0, 0, TOTALENERGY - energy, 40, TOCOLOR( 0x00, 0x00, 0x00));//Spent		
	}
	
	
	void background()
	{
						//Rectangles are x,y plus width, height, color
				Graphics.Rectangle(0, 40, 240, 220, RED);//screen
				Graphics.Rectangle(0, 260, 240, 60, BLUE);//Bottom

				//The corners
				Graphics.Circle(0,0,10,GREEN,true);
				Graphics.Circle(0,320,10,RED,true);
				Graphics.Circle(240,0,10,RED,true);
				Graphics.Circle(240,320,10,RED,true);

	}

	void GameOver()
	{
		background();
		DotDrawStr(PStr(Shell_AppName()),8,18,68,RED,true);
		DotDrawStr("Game Over",50,18,68,RED,true);	
	}

//Careful with adding etra things into this event loop. Put stuff in a function called once.

	int TouchMove(int x, int y, int color)
	{
		Draw(x, y,color);
		drawEnergy(CurrentEnergy);
		CurrentEnergy--;
		if (CurrentEnergy <= 0)
			{
				return 0;
			}
		return CurrentEnergy;
	}

	int OnEvent(Event* e)
	{
		switch (e->Type)
		{
			case Event::OpenApp:
				setup();
				break;

			case Event::TouchDown:
				if (e->Touch->y > 320)
					return -1;		// Quit

			case Event::TouchMove:
				if (TouchMove(e->Touch->x,e->Touch->y,YELLOW) <= 0)
				{				
					GameOver();
					break;
					//return -1;
				}
				break;
			default:
				;
		}
		return 0;
	}
};

INSTALL_APP(Thermo,Thermo);
