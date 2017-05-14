#!/usr/bin/python
#Abhishek Polavarapu
#Assignment 3
#UIN:01028922

import random
import math
import re
import turtle
from turtle import Turtle, mainloop

#from cImage import *# This variable holds the current state of the machine
state_num = 0

x1,y1,x2,y2 = 0,0,0,0
color1 = 0
color2 = 0
color3 = 0
click_count = 0
fillornot = "";
colors = ["red", "green", "blue", "yellow", "white", "pink", "brown", "purple", "gray", "orange"]


class KeysMouseEvents:
    def __init__(self):     
        self.T=Turtle()
        self.screen=self.T.getscreen()
        self.T.pensize(5)
        self.T.speed(0)
        self.T.penup()
        self.screen.onkey(self.quit,"q")
        self.screen.onkey(self.clear,"c")
        self.screen.onclick(self.maindraw)
        self.screen.listen()

# set a random colors set    
    def setrandomcolor(self):
        global color1, color2, color3
        color1 = random.randint(0,9)
        while True:
            color2 = random.randint(0,9)
            if (color1 !=color2):
                break
        while True:
            color3 = random.randint(0,9)
            if (color3 !=color1):
                if (color3 !=color2):
                    break         
    def drawPolygon (self, sideLength, color , fillornot):
        self.T.pendown()
        if(fillornot==1):    
            self.T.color("black")
        else:
            self.T.color(color)
        self.T.left(54)
        for i in range(5): 
            self.T.left(72)
            self.T.forward(sideLength)
         
    #Quit by "q" keypress
    def quit(self):
        self.T.screen.bye()

    #Clear screen by "c" keypress
    def clear(self):
        self.T.screen.clear()
        self.__init__()

    def maindraw(self,x,y):
        self.T.penup()
        global click_count, x1, y1, x2, y2
        
        global state_num
        if state_num == 0: #check if the turtle finish or nor finish drawing
            if (x1 == x) and (y1 == y):
                print ("Start and End position conflict.Start from new position")
                #exit()
            else:
                click_count = click_count + 1
                self.T.goto(x,y)
                self.T.pensize(3)
                self.T.dot()
                self.T.pensize(5)
                
                if (click_count % 2 == 0):
                    state_num = 1
                    print ("Got end and start points")
                    self.setrandomcolor()
                    x2 = x
                    y2 = y

                    #caculate the radius
                    radius = math.sqrt ( math.pow(x1-x2,2)+math.pow(y1-y2,2))
                    dx,dy = x2-x1,y2-y1
                    #This is the angle aka slope
                    rads = math.atan2(dx,dy)
                    degs = math.degrees(rads)
                    small_radius = radius/pow(2,0.5)
                
                    
                    #Big Pentagon Draw Method
                    self.T.penup()
                    self.T.goto(x1 , y1)
                    self.T.pendown()
                    R = radius * (1/math.cos(math.pi/5))
                    #print R , "Radius of outer pentagon"
                    radan = math.sin(math.pi/5);
                    #print radan , "sinpibyn"
                    radius1 = 2*R * radan
                    #print radius1 , "radius1"
                    self.T.setheading(90)
                    self.T.forward(R)
                    fillornot=1
                    self.drawPolygon(radius1, "black" , fillornot)
                    
                    #Big Pentagon Fill Method
                    self.T.penup()
                    self.T.color(colors[color1])
                    self.T.goto(x1 , y1)
                    self.T.setheading(90)
                    self.T.forward(R-2)
                    self.T.pendown()
                    self.T.begin_fill()
                    fillornot= 0 
                    self.drawPolygon(radius1-1.8, colors[color1] , fillornot)
                    self.T.end_fill()


                    #Circle
                    self.T.penup()
                    self.T.color("black")
                    self.T.goto(x2, y2)
                    self.T.pendown()
                    self.T.setheading(180-degs)
                    self.T.circle(radius)
                    
                    #fill the circle
                    self.T.penup()
                    self.T.color(colors[color2])
                    self.T.goto(x1-small_radius+1,y1-small_radius+1)
                    self.T.pendown()
                    self.T.begin_fill()
                    self.T.setheading(315)
                    self.T.circle(radius-2)
                    self.T.end_fill()
                    
                    #small polygon method draw
                    self.T.penup()
                    self.T.goto(x1 , y1)
                    #print radius , "radius"
                    #side length 
                    radan = math.sin(math.pi/5);
                    #print radan , "sinpibyn"
                    radius1 = 2* radius * radan
                    #print radius1 , "radius1"
                    self.T.setheading(90)
                    self.T.forward(radius)
                    fillornot = 0
                    self.drawPolygon(radius1, "black" , fillornot)
                    
                    
                    #small polygon method fill
                    self.T.penup()
                    self.T.color(colors[color3])
                    self.T.goto(x1 , y1)
                    self.T.setheading(90)
                    self.T.forward(radius-2)
                    self.T.pendown()
                    self.T.begin_fill()
                    fillornot= 0 
                    self.drawPolygon(radius1-1.8, colors[color3] , fillornot)
                    self.T.end_fill()
                    self.T.goto(x1,y1)
                    self.T.color("black")
                    self.T.pensize(3)
                    self.T.dot()
                    self.T.hideturtle()
                    state_num = 0
                else:
                    
                    #print ("first point")
                    self.T.penup()
                    self.T.goto(x, y)
                    x1 = x
                    y1 = y
                    print (x1, y1)
                    
                    state_num = 0 #turtle finish its job. Ready for another drawing.
                
            

    def main(self):
        mainloop()
    
def drawcir():
    draw=KeysMouseEvents() 
    draw.main()
drawcir()