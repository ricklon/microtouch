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
#define BLACK (TOCOLOR( 0x00, 0x00, 0x00))
#define WHITE (TOCOLOR( 0xFF, 0xFF, 0xFF))


	
//Game Values
#define MAX_PARTICLES 15
#define TOTALENERGY 240
#define PARTICLE_RADIUS 5
#define WIDTH 240
#define HEIGHT 320 
#define TOP_MARGIN 40




class HeatDeath
{
	
//Game Area
 int CurrentEnergy;
 int Particles[MAX_PARTICLES][5];

/*
	0 =	int rr;
	1 =	int xx;
	2 = int yy;
	3 = int vel;
	4 =	int angle;
	
*/		

public:
	void Draw(int xx, int yy, int color)
	{
		//Freshen the background
		background();	

		//The tap
		Graphics.Circle(xx,yy,10,color,true);	
		drawParticles();

				
	}
	
	void drawParticles()
	{
		for (int nn = 0; nn < MAX_PARTICLES; nn++)
		{
				Graphics.Circle(Particles[nn][1], Particles[nn][2], Particles[nn][0], RED, true);
				moveParticle(Particles[nn][1], Particles[nn][2], Particles[nn][3], Particles[nn][4]);
		}	
	}

	void moveParticle(int &xx, int &yy,  int &dxx, int &dyy)
	{
		xx += dxx;	
		yy += dyy;	
		 if ( xx + dxx > WIDTH )
			{
				xx = 0;
			}
		if (xx + dxx < 0)
			{
			xx = 240;
			}			
		if (yy + dyy > HEIGHT)
			{ 	
				yy = TOP_MARGIN + 4;			
			}
		if (yy + dyy < TOP_MARGIN+4)
			{
				yy = 320;
			}				
	}

	void setup()
	{			
				background();	
				Graphics.Rectangle(0, 0, 240, 40, YELLOW);//Top
				DotDrawStr(PStr(Shell_AppName()),8,2,68,RED,true);

				for (int nn = 0; nn < MAX_PARTICLES; nn++)
				{
					u16 xx = RandomBits(16);
					u16 yy = RandomBits(16);
					int dx = nn % xx;
					int dy = nn % yy;
					switch (nn % 3) 
					{
						case 0:
							dx = -dx;
						case 1:
							dy = -dy;
						case 2:
							dx = -dx;
							dy - dy;
						default:
						;
						
					}		
							
										
					Particles[nn][0] = PARTICLE_RADIUS;
					Particles[nn][1] = xx/240; //xx
					Particles[nn][2] =  yy/320 + 40; //yy 
					Particles[nn][3] =  dx; //dx
					Particles[nn][4] =  dy; //dy
				

				}
				drawParticles();
	}
	
	//x is percentage of energy between 0 and 100
	void drawEnergy(int n)
	{
		int energy = n;		
		//Graphics.Rectangle(0, 0, energy ,40 , TOCOLOR( 0xFF, 0xFF, 0xFF));//Energy
		Graphics.Rectangle(0, 0, TOTALENERGY - energy, 40, BLACK);//Spent		
	}
	/*
	bool isPointInside(int xx, int yy, int targetxx, int targetyy)
	{
		if (((xx - targetxx)^2 + (yy - targetyy)^2 ) < (PARTICLE_RADIUS)^2) 
		{
			return true;
		}
		else
		{	
			return false;
		}
	}
	
	*/
	
	void background()
	{
						//Rectangles are x,y plus width, height, color
				Graphics.Rectangle(0, 40, 240, 220, BLACK);//screen
				Graphics.Rectangle(0, 260, 240, 60, BLACK);//Bottom

	}

	void GameOver()
	{
		background();
		DotDrawStr("Game Over",20,1,68,RED,true);	
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
				CurrentEnergy = 240;
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

INSTALL_APP(HeatDeath,HeatDeath);
