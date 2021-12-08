/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Brainfuck;
import java.util.*;

/**
 *
 * @author J-P
 * A Brainfuck interpreter
 */
public class Brainfuck {
    
    private static Scanner reader=new Scanner (System.in);
    private static int ptr=0;
    private static int memSize=65535;
    private static byte[] mem=new byte[memSize];
    
    private static boolean validate(String s)            
    {
        //Check for balanced brackets 
        //Loop through the code, push the index in to the stack every time a bracket is opened and pop the index when the bracket is closed
        //If correctly balanced, the stack will be empty at the end
        Stack<Integer> stack=new Stack<Integer>();
        for(int i=0;i<s.length()-1;i++)
        {
            if(s.charAt(i)=='[')
                stack.push(i);
            if(s.charAt(i)==']')
                if(stack.empty())
                {
                    System.out.println("Unopened bracket at "+(i+1));                    
                    return false;
                }
                else
                    stack.pop();            
        }
        if(stack.empty())
            return true;        
        else
        {
            System.out.println("Unclosed bracket at "+stack.peek());
            return false;
        }
    }
    
    private static void interpret(String s)
    {
        int cnt=0; //variable for keeping track of brackets
        for(int i=0;i<s.length();i++)
        {
            switch(s.charAt(i))
            {
                case '>':
                    if(ptr>memSize-1)
                        ptr=0;
                    else
                        ptr++;
                    break;
                case '<':
                    if(ptr==0)
                        ptr=memSize-1;                        
                    else
                        ptr--;
                    break;
                case '+':
                    mem[ptr]++;
                    break;
                case '-':
                    mem[ptr]--;
                    break;
                case '.':
                    System.out.print((char)(mem[ptr]));
                    break;
                case ',':
                    mem[ptr]=(byte)reader.next().charAt(0);
                    break;
                case '[':
                    if(mem[ptr]==0)
                    {
                        i++;
                        while(cnt>0||s.charAt(i)!=']')
                        {
                            if (s.charAt(i) == '[')
                                cnt++;
                            else if (s.charAt(i) == ']')
                                cnt--;
                            i++; 
                        }
                    }
                    break;
                case ']':
                    if(mem[ptr]!=0)
                    {
                        i--;
                        while(cnt>0||s.charAt(i)!='[')
                        {
                            if (s.charAt(i) == ']')
                                cnt++;
                            else if (s.charAt(i) == '[')
                                cnt--;
                            i--; 
                        }
                    }
                    
                    break;                                       
            }
        }
    }
    
    public static void main(String[] args) 
    {
        System.out.println("Enter code to interpret:");
        String code=reader.nextLine();
        
        if(validate(code))
        {
            System.out.println("Output:");
            interpret(code);            
        }
        else
            System.out.println("Code validation failed");
        System.out.println();
        
    }
    
}
