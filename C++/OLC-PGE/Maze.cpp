#include <iostream>
#include <vector>
#include "OlcPixelGameEngine.h"
#include <stack>
using namespace std;

//A quick visualized maze generator using backtracking without recursion
//Uses Javidx9's OneLoneCoder PixelGameEngine
//Add the header to your include path first

class Maze : public olc::PixelGameEngine
{

public:
	struct cell
	{
		int x, y, gx, gy; //Screen and grid co-ordinates
		vector<boolean> walls = { true,true,true,true };
		bool visited = false;
	};
	const int CELLSIZE = 20;
	const int BORDER = 20;
	int mW, mH;
	vector<cell> cells; //Vector for storing the cells
	stack<cell*> stack; //Stack of pointers to cells for backtracking
	cell* current; //Pointer to a cell in the vector that is our current position
	float t, limit = .01f; //Timer and a limit for visualization purposes

	Maze()
	{
		sAppName = "Maze";
	}

	bool OnUserCreate() override
	{
		srand(time(NULL));
		//Size of the maze
		mW = (ScreenWidth() - BORDER * 2) / CELLSIZE;
		mH = (ScreenHeight() - BORDER * 2) / CELLSIZE;

		for (int y = 0; y < mH; y++)
			for (int x = 0; x < mW; x++)
			{
				cell c;
				c.gx = x;
				c.gy = y;
				c.x = BORDER + x * CELLSIZE;
				c.y = BORDER + y * CELLSIZE;
				cells.push_back(c);
			}
		//Start from the first cell in vector and set it as visited, push it to the stack
		current = &cells[0];
		current->visited = true;		
		stack.push(current);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		DrawMaze();
		//Draw a filled rectangle to current cell for visualization
		FillRect(current->x, current->y, CELLSIZE, CELLSIZE, olc::RED);
		if (t > limit)
		{
			t = 0;
			current = ConstructMaze(current);
		}
		
		t += fElapsedTime;
		return true;
	}

	void DrawMaze()
	{
		//Loop through the vector and draw each wall that exists
		for (int i = 0; i < cells.size(); i++)
		{
			//Draw filled rectangles for visited cells for visualization
			if (cells[i].visited)
				FillRect(cells[i].x , cells[i].y , CELLSIZE , CELLSIZE, olc::BLUE);

			if (cells[i].walls[0])
				DrawLine(cells[i].x, cells[i].y, cells[i].x + CELLSIZE, cells[i].y);
			if (cells[i].walls[1])
				DrawLine(cells[i].x + CELLSIZE, cells[i].y, cells[i].x + CELLSIZE, cells[i].y + CELLSIZE);
			if (cells[i].walls[2])
				DrawLine(cells[i].x + CELLSIZE, cells[i].y + CELLSIZE, cells[i].x, cells[i].y + CELLSIZE);
			if (cells[i].walls[3])
				DrawLine(cells[i].x, cells[i].y, cells[i].x, cells[i].y + CELLSIZE);
		}
	}

	cell* ConstructMaze(cell* c)
	{
		cell* next = NULL;
		int rnd;
		int unvisited = 0;

		//Count the unvisited neighbouring cells 
		if (c->gy > 0) 
		{
			unvisited += !cells[mW * (c->gy - 1) + c->gx].visited;
		}
		if (c->gy < mH-1)
		{
			unvisited += !cells[mW * (c->gy + 1) + c->gx].visited;
		}

		if (c->gx > 0)
		{
			unvisited += !cells[mW * c->gy + c->gx-1].visited;
		}
		if (c->gx < mW-1)
		{
			unvisited += !cells[mW * c->gy + c->gx+1].visited;
		}

		//If no unvisited neighbours and stack is not empty
		//Pop the top cell and return it
		//If the stack IS empty, the maze is complete
		if (unvisited == 0 && stack.size()>0)
		{
			next = stack.top();
			stack.pop();
			return next;
		}

		//While the next cell is null or visited
		//Randomize the direction from which to pick the next cell
		while (!next || next->visited)
		{			
			rnd = rand() % 4;

			//Up
			if (rnd == 0 && c->gy > 0)
				next = &cells[mW * (c->gy - 1) + c->gx];
			//Right
			if (rnd == 1 && c->gx < mW - 1)
				next = &cells[mW * c->gy + c->gx + 1];
			//Down
			if (rnd == 2 && c->gy < mH - 1)
				next = &cells[mW * (c->gy + 1) + c->gx];
			//Left
			if (rnd == 3 && c->gx > 0)
				next = &cells[mW * c->gy + c->gx - 1];			
		}


		//A quick calculation on what direction did we move and set remove corresponding walls from
		//Both cells
		int a = c->gx - next->gx;
		int b = c->gy - next->gy;

		//Up
		if (b == 1)
		{
			c->walls[0] = false;
			next->walls[2] = false;
			next->visited = true;			
		}
		//Down
		if (b == -1)
		{
			c->walls[2] = false;
			next->walls[0] = false;
			next->visited = true;
		}

		//Left
		if (a == 1)
		{
			c->walls[3] = false;
			next->walls[1] = false;
			next->visited = true;
		}
		//Right
		if (a == -1)
		{
			c->walls[1] = false;
			next->walls[3] = false;
			next->visited = true;
		}

		//Push the current cell to stack for backtracking
		stack.push(next);
		return next;
	}

};

int main()
{
	Maze m;
	if (m.Construct(640, 480, 1, 1))
		m.Start();
}
