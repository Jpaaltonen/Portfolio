using System;
using System.Collections.Generic;
using System.Text;
using static System.Console;
using System.Linq;
using System.Reflection;

//A demo of a console application for querying data using Linq
//Originally an exam task for a course in advanced concepts of C#

namespace Tentti3
{
    public static class Application
    {
        static List<MenuItem> Menu;

        
        static void WriteResult<T>(int itemid, List<T> result) 
        {
            string row;
            //Headers
            WriteLine();
            WriteLine(Menu.Where(mi => mi.Id == itemid).First().Name.ToUpper());
            WriteLine("‐".PadRight(18 * result[0].GetType().GetProperties().Length + 2, '‐'));
            //Columns
            if (result.Count > 0)
            {
                row = "";
                foreach (PropertyInfo property in result[0].GetType().GetProperties())
                {
                    row += $"{property.Name}".PadRight(16) + " | ";
                }
                WriteLine(row);
            }
            WriteLine("‐".PadRight(18 * result[0].GetType().GetProperties().Length + 2, '‐'));
            //datarows
            foreach (object item in result)
            {
                row = "";
                foreach (PropertyInfo property in item.GetType().GetProperties())
                {
                    row += $"{property.GetValue(item, null).ToString()}".PadRight(16) + " | ";
                }
                WriteLine(row);
            }
            WriteLine("‐".PadRight(18 * result[0].GetType().GetProperties().Length + 2, '‐'));
            WriteLine();
            Write("Press Enter");
            ReadLine();
        }
        static void InitializeMenu()
        {
            Menu = new List<MenuItem>(); //Create and populate the menu with menuItems
            Menu.Add(new MenuItem() { Id = 1, Name = "50 year old employees" });
            Menu.Add(new MenuItem() { Id = 2, Name = "Departments with over 50 employees" });
            Menu.Add(new MenuItem() { Id = 3, Name = "Employees under given surname" });
            Menu.Add(new MenuItem() { Id = 4, Name = "Largest salaries in departments" });
            Menu.Add(new MenuItem() { Id = 5, Name = "Five most common surnames" });
            Menu.Add(new MenuItem() { Id = 6, Name = "Age distributions of departments" });

            //Queries - mixed selection of methods and query forms.
            Menu[0].ItemSelected += (obj, a) =>
            {
                //Query the department name, employee name and employee name from the list of departments generated in Data class
                //Show above info for all the persons who are 50 years old
                var res = Data.Departments.SelectMany(d => d.Employees, (d, e) => new { Department = d.Name, Age=e.Age, Name=e.Name });
                var result = from e in res
                             where e.Age == 50
                             select new
                             {
                                 Name = e.Name,
                                 Age = e.Age,
                                 Department =  e.Department
                             };

                WriteResult(a.ItemId, result.ToList());
            };

            //Query all departments with over 50 employees from the list of departments
            //Sort in descending order and show department ID, name and headcount
            Menu[1].ItemSelected += (obj, a) =>
            {

                var result = from d in Data.Departments
                             where d.EmployeeCount > 50
                             orderby d.EmployeeCount descending
                             select new
                             {
                                 Id = d.Id,
                                 Name = d.Name,
                                 Headcount = d.EmployeeCount
                             };

                WriteResult(a.ItemId, result.ToList());
            };

            //Query for given surname in list of employees in Data class
            //Query is done with case sensitivity and with no wildcards
            //Show employee ID and name
            Menu[2].ItemSelected += (obj, a) =>
            {
                Write("Enter a surname: ");
                string input = ReadLine();

                var result = from e in Data.Employees
                             where e.LastName==input                             
                             select new
                             {
                                 Id = e.Id,
                                 Name=$"{e.LastName} {e.FirstName}"
                             };

                WriteResult(a.ItemId, result.ToList());
            };

              //Query for department name and employee salaries from the list of Departments
              //Group query by department and show department name and maximum salary

              Menu[3].ItemSelected += (obj, a) =>
              {

                 var res = Data.Departments.SelectMany(d => d.Employees, (d, e) => new { Dept = d.Name, Salary = e.Salary });

                 var result = from e in res.GroupBy(o=>o.Dept)
                              select new
                              {
                                   Dept=e.Key,
                                   MaxSalary=e.Max(p=>p.Salary)
                              };
                  WriteResult(a.ItemId, result.ToList());
              };

            //Query for all employees in the list of employees
            //Group the result by surname, sort in descending order and select and show top five surnames with count
            Menu[4].ItemSelected += (obj, a) =>
            {
                var res = from e in Data.Employees
                          group e by e.LastName into empGroup
                          select new
                          {
                              Surname = empGroup.Key,
                              Amount = empGroup.Count()
                          };


                var result = (from n in res
                              orderby n.Amount descending
                              select n).Take(5);
                             

                WriteResult(a.ItemId, result.ToList());
            };

            //Query for department name and employee ages in the list of departments
            //Create new fields for people under 30, 30-50 and over 50 years old
            Menu[5].ItemSelected += (obj, a) =>
            {
                var result = from d in Data.Departments
                             select new
                             {
                                 Nimi = d.Name,
                                 Under30 = d.Employees.Select(s => s).Where(s=>s.Age<30).Count(),
                                 Between30_50 = d.Employees.Select(s => s).Where(s=>s.Age>=30 && s.Age<=50).Count(),
                                 Over50 = d.Employees.Select(s => s).Where(s=>s.Age>50).Count()
                             };
                WriteResult(a.ItemId, result.ToList());
            };
        }

        public static void Initialize()
        {
            //Initialize menu and generate data
            InitializeMenu();
            Data.GenerateData();
        }

        public static int ReadFromMenu()
        {

            Clear();//Clear and print the menu
            WriteLine("Options");
            for (int i = 0; i < Menu.Count; i++)
                WriteLine($"{i+1}. {Menu[i].Name}");
            Write("Choose (0 to quit): ");
            String input = ReadLine();
            int parse;
            if (int.TryParse(input, out parse))
            {
                if (parse >= 0 && parse <=6) 
                    return parse;
                else
                    throw new Exception("Not a valid option"); //Index out of range
            }
            else
                throw new Exception("Not a valid option"); //input not an integer

        }

        public static void Run()
        {

            Initialize();
            int input;
            do
            {
                try
                {
                    input = ReadFromMenu(); 
                    if (input == 0)
                        break; 
                    Menu[input - 1].Select(); //Subtract 1 from input to fit it into the right range
                }
                catch(Exception e)
                {
                    WriteLine(e.Message);
                    Write("Press Enter");
                    ReadLine();
                }
            } while (true);
        }
        
    }
}
