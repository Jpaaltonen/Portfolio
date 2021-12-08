/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package befunge;
import java.util.*;
/**
 * @author J-P
 * Befunge interpreter
 * Works to at least some degree, though some of the codes from the 'net crash
 */
public class Befunge 
{
    private static Stack<Integer> programStack=new Stack<Integer>();    
    private static int[] movementVector=new int[2]; //2D vector for moving through an xy-grid
    private static Scanner in=new Scanner (System.in);
    
    /*
    EXAMPLE CODE:
    >              v
    v  ,,,,,"Hello"<
    >48*,          v
    v,,,,,,"World!"<
    >25*,@
    */
    
    /*
    
    //Not yet implemented
    p	A "put" call (a way to store a value for later use). Pop y, x, and v, then change the character at (x,y) in the program to the character with ASCII value v
    g	A "get" call (a way to retrieve data in storage). Pop y and x, then push ASCII value of the character at that position in the program
    */
    
    private static void interpret(Vector<String> s)
    {
        //Initial position upper-left corner of the code
        //Initial movement direction right
        int x=0,y=0; 
        movementVector[0]=1;
        movementVector[1]=0;
        
        //Arithmetic operation variables
        int a,b; 

        while(s.get(y).charAt(x)!='@') //Loop until we reach the character that terminates the execution
        {
            switch(s.get(y).charAt(x))
            {
                //0-9	Push this number on the stack
                case '0':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break;
                case '1':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break;
                case '2':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break;
                case '3':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break;
                case '4':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break;
                case '5':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break; 
                case '6':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break;
                case '7':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break;
                case '8':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break;
                case '9':
                    programStack.push((int)(s.get(y).charAt(x)-'0'));
                    break; 
                
                //+	Addition: Pop a and b, then push a+b
                case '+':
                    a=programStack.pop();
                    b=programStack.pop();
                    programStack.push(a+b);
                    break; 
                    
                //-	Subtraction: Pop a and b, then push b-a
                case '-':
                    a=programStack.pop();
                    b=programStack.pop();
                    programStack.push(b-a);
                    break; 
                //*	Multiplication: Pop a and b, then push a*b
                case '*':
                    a=programStack.pop();
                    b=programStack.pop();
                    programStack.push(a*b);
                    break; 
                ///	Integer division: Pop a and b, then push b/a, rounded towards 0.    
                case '/':
                    a=programStack.pop();
                    b=programStack.pop();
                    programStack.push((int)b/a);
                    break;                         
                //%	Modulo: Pop a and b, then push the remainder of the integer division of b/a.
                case '%':
                    a=programStack.pop();
                    b=programStack.pop();
                    programStack.push(b%a);
                    break; 
                    
                //!	Logical NOT: Pop a value. If the value is zero, push 1; otherwise, push zero.
                case '!':
                    if(programStack.pop()==0)
                        programStack.push(1);
                    else
                        programStack.push(0);                   
                    break;
                //`	Greater than: Pop a and b, then push 1 if b>a, otherwise zero.
                case '`':
                    a=programStack.pop();
                    b=programStack.pop();
                    if(b>a)
                        programStack.push(1);
                    else
                        programStack.push(0);
                    break;
                //>	Start moving right
                case '>':
                    movementVector[0]=1;
                    movementVector[1]=0;
                    break;
                //<	Start moving left
                case '<':
                    movementVector[0]=-1;
                    movementVector[1]=0;
                    break;  
                //^	Start moving up
                case '^':
                    movementVector[0]=0;
                    movementVector[1]=-1;
                    break;
                //v	Start moving down
                case 'v':
                    movementVector[0]=0;
                    movementVector[1]=1;
                    break;
                    
                //?	Start moving in a random cardinal direction         
                case '?':
                    switch((int)Math.random()*4) 
                    { 
                        //Up,right,down,left
                        case 0:
                            movementVector[0]=0;
                            movementVector[1]=-1;
                            break;
                        case 1:
                            movementVector[0]=1;
                            movementVector[1]=0;
                            break;
                        case 2:
                            movementVector[0]=0;
                            movementVector[1]=1;                            
                            break;
                        case 3:
                            movementVector[0]=-1;
                            movementVector[1]=0;                            
                            break;                                   
                    }
                    break;
                //_	Pop a value; move right if value=0, left otherwise
                case '_':
                    if(programStack.pop()==0)
                    {
                        movementVector[0]=1;
                        movementVector[1]=0;
                    }
                    else
                    {
                        movementVector[0]=-1;
                        movementVector[1]=0;
                    }
                    break;
                //|	Pop a value; move down if value=0, up otherwise
                case '|':
                    if(programStack.pop()==0)
                    {
                        movementVector[0]=0;
                        movementVector[1]=1;
                    }
                    else
                    {
                        movementVector[0]=0;
                        movementVector[1]=-1;
                    }
                    break;    
                   
                //"	Start string mode: push each character's ASCII value all the way up to the next "
                case '"':
                    x+=movementVector[0];
                    y+=movementVector[1];
                    while(s.get(y).charAt(x)!='"')
                    {
                        programStack.push((int)s.get(y).charAt(x));
                        x+=movementVector[0];
                        if(x>s.get(y).length()-1)
                            x=0;
                        if(x<0)
                            x=s.get(y).length()-1;
                        y+=movementVector[1];
                        if(y<0)
                            y=s.size()-1;
                        if(y>s.size()-1)
                y=0;
                    }  
                    break;
                                     
                //:	Duplicate value on top of the stack
                case ':':
                    programStack.push(programStack.peek());
                    break;
                //\	Swap two values on top of the stack
                case '\\':
                    a=programStack.pop();
                    b=programStack.pop();
                    programStack.push(a);
                    programStack.push(b);
                    break;
                        
                //$	Pop value from the stack and discard it
                case '$':
                    programStack.pop();
                    break;
                //.	Pop value and output as an integer followed by a space
                case '.':
                    System.out.print(programStack.pop()+" ");
                    break;
                //,	Pop value and output as ASCII character
                case ',':
                    System.out.print(Character.toChars(programStack.pop()));
                    break;
                
                //#	Bridge: Skip next cell

                case '#':
                    x+=movementVector[0];
                    if(x>s.get(y).length()-1)
                        x=0;
                    if(x<0)
                        x=s.get(y).length()-1;
                    y+=movementVector[1];
                    if(y<0)
                        y=s.size()-1;
                    if(y>s.size()-1)
                        y=0;
                    break;
                    
                //&	Ask user for a number and push it
                case '&':
                    System.out.println("Enter a number:");
                    programStack.push(in.nextInt());
                    break;                    
                //~	Ask user for a character and push its ASCII value
                case '~':
                    break;
            }
            
            x+=movementVector[0];
            if(x>s.get(y).length()-1)
                x=0;
            if(x<0)
                x=s.get(y).length()-1;
            y+=movementVector[1];
            if(y<0)
                y=s.size()-1;
            if(y>s.size()-1)
                y=0;
            
           
            
        }
    }
    
    public static void main(String[] args) 
    {

        System.out.println("Enter codelines (empty line quits): ");
        Vector<String> code=new Vector<String>();
        String s=in.nextLine();
        while(s.length()>0)
        {
            code.add(s);            
            s=in.nextLine();
        }
        System.out.println("Interpreting...");
        interpret(code);
        System.out.println("Completed");
        
    }
    
}

