using System;
using System.Collections.Generic;
using System.Text;
using static System.Console;

namespace Tentti2
{
    class ConsoleControl
    {
        public List<string> Items { get; set; }
        public int Column { get; set; }
        public int Row { get; set; }
        public int Width { get; set; }
        public int Height { get; set; }
        public ConsoleColor BackColor { get; set; }
        public ConsoleColor TextColor { get; set; }

        public ConsoleControl(int c, int r, int w, int h)
        {           
            Column = c;
            Width = w;
            Height = h;
            Row = r;
            BackColor = System.Console.BackgroundColor;
            TextColor = System.Console.ForegroundColor;
            Items = new List<string>();
        }

        public void Draw()
        {
            int org_column = CursorLeft, org_row = CursorTop; //Save original cursor position
            ConsoleColor org_fore = ForegroundColor, org_back = BackgroundColor; //Change back- and foreground colours
            ForegroundColor = TextColor;
            BackgroundColor = BackColor;
            for (int i = 0; i < Height; i++) //Loop through the rows i the window
            {
                SetCursorPosition(Column - 1, Row - 1 + i); //Set cursor position to position designated by Column and Row properties
                if (Items != null && i < Items.Count) //If i is less than amount of rows in the list, use i as an index
                {
                    //Print data from the list row by row, pad the row with space so it fills the window
                    Write(Items[i].PadRight(Width, ' ')); 
                }
                else //If the list is empty or i has surpassed the amount of items in the list
                {
                        Write("".PadRight(Width, ' ')); //Print an empty string, and pad it to fill the whole row
                }
            }
            SetCursorPosition(org_column, org_row); //Return the cursor to it's original position
            ForegroundColor = org_fore; //And reset the colours
            BackgroundColor = org_back;
        }

    }
}
