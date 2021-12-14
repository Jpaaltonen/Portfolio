using System;
using System.Collections.Generic;
using System.Text;

namespace Tentti3
{
    //Class for holding department data
    public class Department
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public List<Employee> Employees { get; set; }
        public int EmployeeCount
        {
            get => Employees.Count;
        }

        public Department()
        {
            Employees = new List<Employee>();

        }
        public Department(int id, string name):this()
        {
            Id = id;
            Name = name;
        }

        public override string ToString()
        {
            return $"{Name} ({EmployeeCount})";
        }
    }
}
