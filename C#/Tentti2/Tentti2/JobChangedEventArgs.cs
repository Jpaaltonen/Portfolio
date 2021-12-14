using System;
using System.Collections.Generic;
using System.Text;

namespace Tentti2
{
    class JobChangedEventArgs:System.EventArgs
    {
        public Job Job { get; set; }
    }
}
