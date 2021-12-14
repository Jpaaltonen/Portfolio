using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Tentti3
{
    public class MenuItem
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public event EventHandler<MenuItemEventArgs> ItemSelected; //Create an event

        public void Select()
        {
            EventHandler<MenuItemEventArgs> ItemDelegate = ItemSelected; //Create a delegate for an event
            if(ItemDelegate!=null) //If the delegate is not null, execute the method
                ItemDelegate(this, new MenuItemEventArgs() { ItemId = Id });
        }

        public override string ToString()
        {
            return $"{Id} {Name}";
        }
    }
}
