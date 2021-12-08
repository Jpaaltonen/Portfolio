/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package CopyFile;

import java.io.*;
import java.util.*;
/**
 *
 * @author J-P
 * 
 * A small asynchronous file copier that reads characters from a file one by one in to a buffer and then writes them from to an output file
 * Using FIFO principle
 * Works best with text files
 */

public class Copier {

    /**
     * @param args the command line arguments
     */
    static int c,bufSize=8;
    public static Vector<Character> buf=new Vector<Character>();
    static File inFile=new File ("in.txt"); //Change the path of the file as needed - no input file provided
    static File outFile=new File ("out.txt");
    static boolean completed=false;
    static FileWriter fw;
    static FileReader fr;
    
    public static void main(String[] args) throws InterruptedException
    {       
        //Reading thread
        new Thread(new Runnable()
        {
            public void run()
            {
                try
                {
                    fr=new FileReader(inFile);
                    int c=0;
                    while(c!=-1) //Loop as long as there are characters to be read
                    {
                        if(buf.size()<bufSize-1) //Read a character and add it to buffer if the buffer has not yet maxed out
                        {
                            c=fr.read();
                            buf.add((char)c);
                        }
                    }
                    completed=true;
                    fr.close();
                }
                //No exception handling
                catch(FileNotFoundException e)
                {                    
                }
                catch(IOException e)
                {                    
                }
            }
        }
        ).start();
        
        
        //Writing thread
        new Thread(new Runnable()
        {
            public void run()
            {
                try
                {
                    fw=new FileWriter(outFile);;
                    while(buf.size()>0 || !completed) //Loop until the reader has completed reading the file and the buffer is empty
                    {
                        if(buf.size()>0) //If the buffer is not empty, write the first character in it to output file, then remove it from the buffer
                        {                    
                            fw.write(buf.get(0));
                            buf.remove(0);
                        } 
                    }

                    fw.close();
                }
                catch(FileNotFoundException e)
                {                    
                }
                catch(IOException e)
                {                    
                }
            }
        }
        ).start();
 
    }
    
}
