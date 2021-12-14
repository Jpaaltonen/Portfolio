using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Tentti3
{
    //Class for holding employee data
    public class Employee
    {
        private double _salary;
        public int Id { get;}
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public Department Department { get; set; }
        public DateTime StartDate { get; set; }
        public DateTime? EndDate { get; set; }
        public DateTime? DateOfBirth { get; set; }
        public string Name { get => $"{LastName} {FirstName}"; }
        public int Age
        {
            get
            {
                if (DateOfBirth.HasValue) //If date of birth is not null
                {
                    int age= DateTime.Now.Year - DateOfBirth.Value.Year;
                    if (DateTime.Now.DayOfYear < DateOfBirth.Value.DayOfYear) //Subtract 1 if persons birthday has not yet been reached
                        return age - 1; 
                    else
                        return age;
                }
                else
                    return 0;
            }
        }

        public double Salary 
        {
            get  => Math.Round(_salary,2); 
            set 
            {
                if (value < 0)
                    throw new Exception("Negative salary");
                else
                    _salary = value;
            }
        }

        public Employee(int id, string first, string last, DateTime? dob, double salary)
        {
            Id = id;
            FirstName = first;
            LastName = last;
            DateOfBirth = dob;
            Salary = salary;
            StartDate = DateTime.Now.Date;
            EndDate = null;
        }

        public override string ToString()
        {
            return $"{Id} {FirstName} {LastName}";
        }

    }
}
