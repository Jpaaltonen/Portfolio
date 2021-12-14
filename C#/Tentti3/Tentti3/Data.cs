using System;
using System.Collections.Generic;
using System.Linq;

//Class for generatingand storing randomized employee data

namespace Tentti3
{
    public class Data
    {
        private static Random r = new Random();
        public static List<Department> Departments;
        public static List<Employee> Employees;
        public static void GenerateData(int depts = 15, int maxEmpsInDept = 100)
        {
            Departments = new List<Department>();
            Employees = new List<Employee>();
            for (int i = 1; i <= depts; i++)
            {
                //Create and add a new department to the list
                Departments.Add(GenerateDepartment(i, r.Next(1, maxEmpsInDept)));
            }
        }

        //Generate department
        private static Department GenerateDepartment(int id, int emps)
        {
            Department ret = new Department(id, $"Department {id}");
            Employee emp;
            for (int i = 1; i <= emps; i++)
            {
                //Create a new employee and add it to the employee list in the department
                emp = GenerateEmployee();
                ret.Employees.Add(emp);
                emp.Department = ret;
            }
            return ret;
        }

        //Generate a new employee
        private static Employee GenerateEmployee()
        {
            int id = 1;
            
            if (Employees.Count > 0)
            {
                id += Employees.Max(e => e.Id);
            }
            DateTime start = new DateTime(1950, 1, 1),
            end = new DateTime(1997, 12, 31);
            Employee emp = new Employee(id,GenerateFirstName(),GenerateLastName(),GenerateDate(start, end),GenerateSalary());
            Employees.Add(emp);
            return emp;
        }

        //Generate a name for employee - First draw a random first name from the arrays
        private static string GenerateFirstName()
        {
            string[] names =
            {"Antti","Aulis","Aulikki","Bertta","Eemeli","Eetu","Esko","Hannele","Hannu","Heikki","Harri","Heli","Helena",
                "Iines","Ilkka","Ilmari", "Ida", "Irene",
                "Jaakko","Jari","Juha","Jukka","Jaana","Juhani","Kalevi","Kikka","Kaarina","Kalle","Kauko",
                "Kimmo", "Liisa","Leevi","Lilli",
                "Lumi","Martti","Matti","Mauno","Melina","Miisa","Merja","Marja","Niilo","Nina","Niina","Ninna",
                "Oona","Olavi","Oskari","Pentti","Panu","Pertti","Petri","Paula","Pauliina","Pirkko",
                "Raimo", "Rauli", "Riikka", "Ritva", "Raili",
                "Sara", "Saara", "Sauli","Sakari","Seppo","Taina",
                "Tiina","Tuuli","Tuula","Timo","Tino","Tomas","Tuomas","Unto","Uolevi",
                "Veikko","Veera","Vesa","Väinö","Yrjö"};
            return names[r.Next(0, names.Length)];
        }

        //Then draw a random surname using two arrays
        private static string GenerateLastName()
        {
            string[] part1 = { "Aalto", "Joki", "Meri", "Järvi", "Virta", "Vuori", "Lehto",
                "Leppi", "Koivu", "Salo", "Niemi", "Lahti", "Laiho", "Haka", "Ala", "Ylä", "Väli", "Keski"
            };
            string[] part2 = { "", "nen", "talo", "mäki", "pää", "kari", "la" };
            return $"{part1[r.Next(0, part1.Length)]}{part2[r.Next(0, part2.Length)]}";
        }

        //Generate a random birthday
        private static DateTime GenerateDate(DateTime begin, DateTime end)
        {
            int days = (end - begin).Days;
            return begin.AddDays(r.Next(0, days + 1));
        }
        //And a random salary
        private static double GenerateSalary(double min = 1000, double max = 10000)
        {
            return Math.Round(min + r.NextDouble() * (max-min),2);
        }
    }
}
