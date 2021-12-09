/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Salesman;

/**
 *
 * @author J-P
 * 
 * Salesman problem using a greedy algorithm
 * 
 */
import java.util.*;
        
public class Salesman {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        int iWidth=300, iHeight=600, iPlaces=50,cnt=0; //Init values for map size, places to visit and counter
        int iPosX,iPosY; //location coords
        Random rnd=new Random();       
        HashMap<Integer, Location> locMap=new HashMap<>(); //As XY-coords form a grid, the hashmap uses the number of the grid square as a key to prevent same coordinates
        ArrayList<Location> route=new ArrayList<>(); //The route travelled will be saved as a list
        while(cnt<iPlaces) //loop while we haven't randomized coordinates for all of the places
        {
            iPosX=rnd.nextInt(iWidth); //Draw random values for XY
            iPosY=rnd.nextInt(iHeight);
            if(!locMap.containsKey((iPosY*iWidth)+iPosX)) //if a grid square designated by the coords is available, add it to the map
            {
                locMap.put((iPosY*iWidth)+iPosX, new Location(iPosX,iPosY));
                cnt++; //inc counter
            }                                                
        }     

     
        //Greedy solution
        int tmpKey=locMap.keySet().stream().findFirst().get(); //First key entry in the map will be the starting point
        double dDistance=0; //init distance
        Location tmpLoc=new Location(locMap.get(tmpKey)); //Copy the location designated by the key in from the map to temporary Location
        locMap.remove(tmpKey);        //Remove the map entry
        route.add(tmpLoc);            //Add the copy to a list
        while(locMap.size()>1)        //loop while the map has at least two places to choose from
        {
            tmpKey=locMap.keySet().stream().findFirst().get(); //Save the first key in the current map
            dDistance=getDistance(tmpLoc, locMap.get(tmpKey)); //Calculate the distance between the previously copied Location and the first Location on the hashmap as a comparison value
            for (Map.Entry me : locMap.entrySet()) //Loop for each map entry (including the one above)
            {
                System.out.println("key: "+me.getKey()+" Position: "+me.getValue().toString()+" Distance: "+getDistance(tmpLoc,(Location)me.getValue()));
                if(getDistance(tmpLoc, (Location)me.getValue())<dDistance) //If the distance between the current map entry and the one copied previously is less than the one calculated and saved previously
                { 
                    dDistance=getDistance(tmpLoc, locMap.get((int)me.getKey())); //Save it for later comparison
                    tmpKey=(int)me.getKey(); //And the key too, as it will designate the entry that had the shortest distance
                }
            }
            System.out.println("\n key chosen: "+tmpKey+" Position: "+locMap.get(tmpKey)+" Distance: "+getDistance(tmpLoc,locMap.get(tmpKey))+"\n");
            tmpLoc=new Location(locMap.get(tmpKey)); //Copy the location that had the shortest distance to the placeholder
            locMap.remove(tmpKey); //Pop it from the map
            route.add(tmpLoc); //Add it to the route
        }                
        route.add(new Location(locMap.get(locMap.keySet().stream().findFirst().get()))); //Add the remaining Location to the list
        locMap.clear(); //Clear the map
        //End Greedy
        
        //Print out results
        double dTotalDistance=0;        //Init var for total distance for greedy
        for(int i=1;i<route.size();i++) //Loop through the routelist, and print out the locations and distances between them
        {            
            dDistance=getDistance(route.get(i-1),route.get(i)); //Get the distance between i-1 and i
            dTotalDistance+=dDistance; //Add the distance to total distance            
            System.out.println("Distance from "+route.get(i-1).toString()+" to "+route.get(i).toString()+": "+dDistance);
        }
        //do the above for the last and first locations on the list        
        dDistance=getDistance(route.get(route.size()-1),route.get(0)); 
        dTotalDistance+=dDistance;                                                    
        System.out.println("Distance from "+route.get(route.size()-1).toString()+" to "+route.get(0).toString()+": "+getDistance(route.get(route.size()-1),route.get(0)));
        System.out.println("Total distance travelled: "+dTotalDistance); //Print out the total travelling distance
        
        
        
        
        
        
    }
    
    public static double getDistance(Location l1, Location l2)
    {        
        return Math.sqrt(
               Math.pow(l1.getX()-l2.getX(), 2)+
               Math.pow(l1.getY()-l2.getY(), 2)
               );
    }             
    
}
