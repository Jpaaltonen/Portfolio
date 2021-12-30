#include <iostream>
#include <vector>
#include "OlcPixelGameEngine.h"

//Conway's Game of Life
//Uses Javidx9's OneLoneCoder PixelGameEngine
//Add the header to your include path first

using namespace std;
using namespace olc;
class Life : public olc::PixelGameEngine
{
public:
	struct Cell
	{
		int x, y;
		bool alive = false;
	};

	int cellSize = 10, cellBorder = 2, windowBorder = 20;
	int w, h, gw, gh; //Screenwidth and -height, gridwidth and -height
	int mx, my; //Mouse x,y coords
	bool execute = false;
	float timer = 0, limit = .1f;
	vector<Cell> cells;

	void clearGrid()
	{
		Clear(BLACK);
		for (int y = 0; y < gh; y++)
			for (int x = 0; x < gw; x++)
				cells[y * gw + x].alive = false;
	}

	void updateGrid()
	{
		//Copy current cells
		vector<Cell> old;
		copy(cells.begin(), cells.end(), back_inserter(old));

		for (int y = 0; y < gh; y++)
		{
			for (int x = 0; x < gw; x++)
			{
				int cnt = 0;
				if (y > 0 && y < gh - 1 && x>0 && x < gw - 1)
				{
					//Loop through each cell surrounding the current one - jump over, if at the current cell
					//Count the alive cells from the previous cycle
					for (int i = -1; i < 2; i++)
						for (int j = -1; j < 2; j++)
						{
							if (j == 0 && i == 0)
								continue;
							if (old[(y + i) * gw + (x + j)].alive)
								cnt++;
						}

					//Apply the rules to the cells in the next cycle
					//Alive cells stay alive with 2 or 3 alive neighbours
					//Dead cells come alive with exactly 3 alive neighbours
					//All other cells die

					if (old[y * gw + x].alive && (cnt == 3 || cnt == 2))
						cells[y * gw + x].alive = true;
					else if (!old[y * gw + x].alive && cnt == 3)
						cells[y * gw + x].alive = true;
					else
						cells[y * gw + x].alive = false;
				}
			}
		}

	}

	void drawGrid()
	{
		//Loop through grid and draw rectangles at the cells x,y position, if it is alive
		//We'll leave a small border at the edges, to make each cell stand out
		Clear(BLACK);
		for (int y = 0; y < gh; y++)
			for (int x = 0; x < gw; x++)
				if (cells[y * gw + x].alive)
					FillRect(cells[y * gw + x].x + cellBorder, cells[y * gw + x].y + cellBorder, cellSize - cellBorder, cellSize - cellBorder, GREEN);
	}



	//Randomize the grid
	void makeGrid()
	{
		clearGrid();
		for (int y = 5; y < gh - 6; y++)
			for (int x = 5; x < gw - 6; x++)
				if (rand() % 100 > 74)
					cells[y * gw + x].alive = true;
	}

	bool OnUserCreate() override
	{		
		srand(time(NULL));
		w = ScreenWidth();
		h = ScreenHeight();
		gw = (w - windowBorder * 2) / cellSize; //Grid does not fill the whole window, there will be a slight border on the edges
		gh = (h - windowBorder * 2) / cellSize;

		for (int y = 0; y < gh; y++)
			for (int x = 0; x < gw; x++)
			{
				//Create a new cell and push it to the vector
				Cell c;
				c.x = windowBorder + x * cellSize;
				c.y = windowBorder + y * cellSize;
				c.alive = false;
				cells.push_back(c);
			}
		makeGrid();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//Update grid only when simulation is running, and the timer has surpassed the limit (speed control)
		if (execute && timer > limit)
		{
			updateGrid();
			timer = 0;
		}
		drawGrid();
		mx = (GetMouseX() - windowBorder) / cellSize;
		my = (GetMouseY() - windowBorder) / cellSize;
		DrawString(1, 1, "SPACE : Run/Stop  C : Clear  R : Randomize  LMB : Set cells when paused");
		DrawString(1, 11, "+ : Faster  - : Slower  ");
		//Draw an unfilled rectangle on the cell to signify which cell would be operated
		if (mx > 0 && mx < gw - 1 && my > 0 && my < gh - 1)
			DrawRect(cells[my * gw + mx].x, cells[my * gw + mx].y, cellSize, cellSize);

		//If paused, clicking on a cell activates/deactivates it
		if (!execute && mx > 0 && mx < gw - 1 && my > 0 && my < gh - 1 && GetMouse(0).bPressed)
			cells[my * gw + mx].alive = !cells[my * gw + mx].alive;

		//Pause
		if (GetKey(Key::SPACE).bPressed)
		{
			execute = !execute;
		}

		//Clear
		if (GetKey(Key::C).bPressed)
		{
			execute = false;
			clearGrid();
		}

		//Randomize
		if (GetKey(Key::R).bPressed)
		{
			makeGrid();
		}

		//Increase speed
		if (GetKey(Key::NP_ADD).bPressed)
		{
			if (limit < 0.02f)
				limit = 0.02f;
		}

		//Decrease speed
		if (GetKey(Key::NP_SUB).bPressed)
		{
			if (limit > 0.3f)
				limit = 0.3f;
		}

		timer += fElapsedTime;
		return true;
	}
};






int main()
{
	Life app = Life();
	if (app.Construct(640, 480, 1, 1))
		app.Start();
}
