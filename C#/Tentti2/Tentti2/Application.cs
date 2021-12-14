using System;
using System.Collections.Generic;
using System.Text;
using static System.Console;

//A small demo of a console based application that utilizes events
//For showing a number of jobs, their performers and a timeframe
//Each in it's own window

namespace Tentti2
{
    static class Application
    {
        //Define three instances of ConsoleControl class
        private static ConsoleControl JOBMENU, JOBDETAILS, JOBEMPLOYEES;

        private static void BindMenuData(List<Job> list)
        {
            //Fill the list with jobs
            foreach (Job i in list)
            {                
                JOBMENU.Items.Add($"{i.Id} {i.Title}");
            }
        }              
        private static void BindDetailsData(Job job)
        {
            if (JOBDETAILS.Items != null)
                JOBDETAILS.Items.Clear(); //If the list of details is not empty, clear it

            //Fill the list with details of the job
            JOBDETAILS.Items.Add("JOB DETAILS");
            JOBDETAILS.Items.Add($"Id: {job.Id}");
            JOBDETAILS.Items.Add($"Name: {job.Title}");
            JOBDETAILS.Items.Add($"Starts: {job.StartDate.ToShortDateString()}");
            JOBDETAILS.Items.Add($"Ends: {job.EndDate.ToShortDateString()}");
        }

        private static void BindEmployeesData(Job job)
        {
            if (JOBEMPLOYEES.Items != null)
                JOBEMPLOYEES.Items.Clear(); //Clear the list of employees, if not already empty

            foreach(Employee e in Data.employees)
            {
                foreach(Job j in e.Jobs)
                {
                    if (job.Id == j.Id)
                    {
                        JOBEMPLOYEES.Items.Add(e.Name); //Populate the list with the employees assigned to the job given in parameters
                    }
                }
            }
        }

        private static void Initialize()
        {
            //Create new instances for menus
            JOBMENU = new ConsoleControl(1,2,(System.Console.WindowWidth/2)-1,Data.jobs.Count);
            JOBDETAILS = new ConsoleControl((System.Console.WindowWidth / 2) + 1, 2, (System.Console.WindowWidth / 2) - 1, 5);
            JOBEMPLOYEES = new ConsoleControl((System.Console.WindowWidth / 2) + 1,JOBDETAILS.Height+3, (System.Console.WindowWidth / 2) - 1,System.Console.WindowHeight-JOBDETAILS.Height-1);
            JOBMENU.BackColor = ConsoleColor.Blue;
            JOBMENU.TextColor = ConsoleColor.Yellow;
            JOBDETAILS.BackColor = ConsoleColor.Magenta;
            JOBDETAILS.TextColor = ConsoleColor.Yellow;
            JOBEMPLOYEES.BackColor = ConsoleColor.Blue;
            JOBEMPLOYEES.TextColor = ConsoleColor.Yellow;
            
            BindMenuData(Data.jobs);
            Mediator.Instance.JobChanged += Handler;  //Add an eventhandler to Mediator
        }

        private static void Handler(object sender, JobChangedEventArgs e)
        {
            BindDetailsData(e.Job);
            BindEmployeesData(e.Job);
        }

        private static void MenuSelectionChanged(int id)
        {
            foreach (Job j in Data.jobs)
            {
                if (j.Id == id) //If given id matches a one in the list of jobs
                {
                    Mediator.Instance.OnJobChanged(JOBMENU, j); //Send the job and JOBMENU instance to Mediator
                    break;
                }
            }
            JOBDETAILS.Draw(); //Draw the job and emplyee windows
            JOBEMPLOYEES.Draw();
            
        }

        public static void Run()
        {
            Initialize(); //Initialize            
            int input;
             
            do
            {
                JOBMENU.Draw();
                
                SetCursorPosition(0, 0);
                Write("".PadRight(WindowWidth, ' '));
                SetCursorPosition(0, 0);
                Write("Give a jobnumber (0 to quit): ");
                if (Int32.TryParse(ReadLine(), out input))
                { 
                    if (input < 0 || input > JOBMENU.Items.Count)
                    {

                        SetCursorPosition(0, 0);
                        Write("Not a valid input. Press Enter.".PadRight(WindowWidth, ' '));
                        ReadLine();

                    }
                    else if (input == 0)
                        break;
                    else
                        MenuSelectionChanged(input);
                }
                else
                {
                    SetCursorPosition(0, 0);
                    Write("Not a valid input. Press Enter.".PadRight(WindowWidth, ' '));
                    ReadLine();
                }
                
                
            } while (true);
        }       
    }
}
