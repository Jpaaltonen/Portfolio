using System;
using System.Collections.Generic;
using System.Text;

namespace Tentti2
{
    //Class for holding employee data
    class Employee
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public List<Job> Jobs { get; set; }
    }
}
