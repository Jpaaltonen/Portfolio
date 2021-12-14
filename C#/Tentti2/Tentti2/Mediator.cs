using System;
using System.Collections.Generic;
using System.Text;

namespace Tentti2
{
    sealed class Mediator
    {
        private static Mediator INSTANCE=new Mediator(); //Create a singleton of Mediator
        public static Mediator Instance
        {
            get
            {
                return INSTANCE;
            }
        }

        private Mediator()
        { }

        public event System.EventHandler<JobChangedEventArgs> JobChanged; //Create an event
        public void OnJobChanged(object sender, Job job)
        {
            
            System.EventHandler<JobChangedEventArgs> jobChangeDelegate=JobChanged as System.EventHandler<JobChangedEventArgs>; //Assign an event to a delegate
            if (jobChangeDelegate != null) //If delegate is not null there has been an event
            {
                JobChangedEventArgs e = new JobChangedEventArgs(); //Create a new JCEA instance
                e.Job = job; //Assign the job given as parameter as the new instances Job
            
                jobChangeDelegate(sender,e); //Execute the delegate with the sender and the new JCEA instance
            }
            
            
        }
    }
}
