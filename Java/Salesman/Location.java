/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Salesman;

/**
 *
 * @author J-P
 */
public class Location {
    private int iPosX, iPosY;
    
    public Location(int x, int y)
    {
        this.iPosX=x;
        this.iPosY=y;
    }
    
    public Location(Location l)
    {
        this.iPosX=l.iPosX;
        this.iPosY=l.iPosY;
    }
    
    public int getX()
    {
        return iPosX;
    }
    
    public int getY()
    {
        return iPosY;
    }
    
    @Override
    public String toString()
    {
        return iPosX+","+iPosY;
    }
    
}

