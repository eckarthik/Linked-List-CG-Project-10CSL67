/*********
   Author: Karthik E C (1NC14CS043)
   Website: http:/eckarthik.github.io
*********/

#include<iostream>
#include<GL/glut.h>
#include<Windows.h>
int n,item,key;
void display();
void writeText(int font_type,char *str,float x,float y);
void myinit();
void writeElement(int font_type,int element,float x,float y);
void displayLinkedList();
void mymenu(int choice);
int writeAddr(int font_type,char *str,float x,float y);
struct node
{
    int info;
    struct node *link;
};
typedef struct node* NODE;
static NODE first=NULL;
NODE getnode()
{
    NODE x;
    x=(NODE)malloc(sizeof(struct node));
    if(x==NULL)
    {
            printf("insufficient memory \n");
            exit(0);
    }
    return x;
}

NODE insert_rear(int item,NODE first)
{
    NODE temp;   
    NODE cur;
    temp=getnode();
    temp->info=item;
    temp->link=NULL;
    if(first==NULL)
    return temp;
    cur=first;
while(cur->link!=NULL)
    {
        cur=cur->link;
    }
    cur->link=temp;
    return first;
}

NODE delete_rear(NODE first)
{
    NODE cur,prev;
    if(first==NULL)
    {
        printf("list is empty cannot delete ");
        displayLinkedList();
        return first;
    }
        if(first->link==NULL)
    {
        printf("item to be deleted is %d \n",first->info);
        free(first);
        return NULL;
    }
    prev=NULL;
    cur=first;
    while(cur->link!=NULL)
    {
        prev=cur;
        cur=cur->link;
    }
printf("item deleted is %d \n",cur->info);
    free(cur);
    prev->link=NULL;
return first;
}

NODE delete_specified(NODE first)
{
    NODE prev,cur;
    if(first==NULL)
    {
        printf("list is empty\n");
        displayLinkedList();
        return NULL;
    }
    printf("enter the key");
    scanf("%d",&key);
    if(key==first->info)
    {
        cur=first;
        first=first->link;
        free(cur);
        return first;
    }
    prev=NULL;
    cur=first;
    while(cur!=NULL)
    {
        if(key==cur->info)
            break;
        prev=cur;
        cur=cur->link;
    }
    if(cur==NULL)
    {
     printf("search is unsuccessful\n");   
     return first;    
    }
    prev->link=cur->link;
    free(cur);
    return first;
}
NODE insert_front(int item,NODE first)
{
     NODE temp;
     temp=getnode();
     temp->info=item;
     temp->link=first;
     first=temp;
     return first;
}
void mymenu(int choice)
{
     int i;
    switch(choice)
        {
        case 1:
            printf("enter the item to be inserted"); //Insert Rear
            scanf("%d",&item);
            first=insert_rear(item,first);
            displayLinkedList();
            break;
        case 2:printf("enter the item to be inserted"); //Insert front
            scanf("%d",&item);
            first=insert_front(item,first);
            displayLinkedList();
            break;
        case 3: first=delete_rear(first);
                displayLinkedList();
                break;
        case 4: first=delete_specified(first);
                displayLinkedList();
              //sprintf(action,"Use Keyboard to choose the element to be deleted");
              //glColor3f(0.0,0.4,0.199218);
              //writeText(18,action,150,200);
              //glutSwapBuffers();
            //printf("Use Keyboard to choose the element to be deleted \n");
            break;
        case 5:
            exit(0);
        }
}
void myinit()
{
     glClearColor(1.0,1.0,1.0,1.0);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0,499.0,0.0,499.0);
}
void display()
{
     glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
	displayLinkedList();
	glClearColor(1.0,1.0,1.0,1.0);
 	glFlush();
     
}
void displayLinkedList()
{
     double ddx=40.0;
     char element;
     int i=0;
     char ele;
     glClear(GL_COLOR_BUFFER_BIT);
	 //glClearColor(0.0,0.0,0.0,0.0);
	 writeText(18,"Elements Entered: ",150,400);
	 if(first==NULL)
          writeText(18,"List is empty",150,300);
       struct node *ptr = first;
	  //start from the beginning
      while(ptr != NULL) {
      glColor3f(0.0,0.0,0.0);
      element = ptr->info+'0';
      writeElement(18,element,(240+(10*i)),400);  
      ptr = ptr->link;
       i=i+1;       
     }
     glFlush();
     ptr = first;
     while(ptr != NULL) 
     {
     element = ptr->info;
     glBegin(GL_POLYGON); //Data part of the node
     glColor3f(1.0,1.0,0.0);
     glVertex2f(ddx,100.0);
     glVertex2f(ddx+30.0,100.0);
     glVertex2f(ddx+30.0,130.0);
     glVertex2f(ddx,130.0);
     glEnd();
     glColor3f(0.0,0.0,0.0);
     //writeElement(10,element,20.0+ddx+15.0,115.0);
     ele = element+'0';
     glRasterPos2f(ddx+15.0,115.0); //Specifies where to display the text
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,ele);
     /*
     glScissor(150,200,200,200);
     glEnable(GL_SCISSOR_TEST);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glDisable(GL_SCISSOR_TEST);
     sprintf(action,"Operation:",element);
     glColor3f(1.0,0.0,0.0);
     writeText(18,action,100,200);
     sprintf(action,"Add(%d)",element);
     glColor3f(0.0,0.4,0.199218);
     writeText(18,action,150,200);
     */
     glBegin(GL_POLYGON); //Link part of the node
     glColor3f(0.0,0.9,0.5);
     glVertex2f(ddx+30.0,100.0);
     glVertex2f(ddx+50.0,100.0);
     glVertex2f(ddx+50.0,130.0);
     glVertex2f(ddx+30.0,130.0);
     glEnd();
     
     glFlush();
     
     if(ptr->link==NULL)
     {
     glColor3f(0.0,0.0,0.0);
     writeAddr(12,"NULL",ddx+30.0,110.0); //Writing NULL at the link part of last node
     glFlush();
     break;
     }
     glColor3f(0.0,0.0,0.0);
     glBegin(GL_POLYGON); //Arrow 
     glColor3f(0.0,0.0,0.0);
     glVertex2f(ddx+50.0,112.5);
     glVertex2f(15.0+ddx+50.0,112.5);
     glVertex2f(15.0+ddx+50.0,117.5);
     glVertex2f(ddx+50.0,117.5);
     glEnd();
     glBegin(GL_POLYGON); //Arrow Head
     glColor3f(0.0,0.0,0.0);
     glVertex2f(15.0+ddx+50.0,110.0);
     glVertex2f(20.0+ddx+50.0,115.0);
     glVertex2f(15.0+ddx+50.0,120.0);
     glEnd();
     ddx+=70.0;
     ptr = ptr->link;
     }
     
}


void writeText(int font_type,char *str,float x,float y)
{
     /* 10 - GLUT_BITMAP_HELVETICA_10
        12 - GLUT_BITMAP_HELVETICA_12
        18 - GLUT_BITMAP_HELVETICA_18
        11 - GLUT_BITMAP_TIMES_ROMAN_10
        24 - GLUT_BITMAP_TIMES_ROMAN_24
        */
     char *ch;
     glRasterPos2f(x,y); //Specifies where to display the text
     for(ch=str;*ch!='\0';ch++)
     {
                 if(font_type==10)              
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *ch);
                 else if(font_type==12)              
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *ch);
                 else if(font_type==18)              
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch);
                 else if(font_type==11)              
                 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *ch);
                 else if(font_type==24)              
                 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *ch);
                 
                 
     }     
}
void writeElement(int font_type,int element,float x,float y)
{
     /* 10 - GLUT_BITMAP_HELVETICA_10
        12 - GLUT_BITMAP_HELVETICA_12
        18 - GLUT_BITMAP_HELVETICA_18
        11 - GLUT_BITMAP_TIMES_ROMAN_10
        24 - GLUT_BITMAP_TIMES_ROMAN_24
        */
     glRasterPos2f(x,y); //Specifies where to display the text
                 if(font_type==10)              
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, (char)element); //Type casting element to char because glutBitmapCharacter expects a argument of character type
                 else if(font_type==12)              
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (char)element);
                 else if(font_type==18)              
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (char)element);
                 else if(font_type==11)              
                 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (char)element);
                 else if(font_type==24)              
                 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (char)element);
                            
}
int writeAddr(int font_type,char *str,float x,float y)
{
     /* 10 - GLUT_BITMAP_HELVETICA_10
        12 - GLUT_BITMAP_HELVETICA_12
        18 - GLUT_BITMAP_HELVETICA_18
        11 - GLUT_BITMAP_TIMES_ROMAN_10
        24 - GLUT_BITMAP_TIMES_ROMAN_24
        */
        char *ch;
     glRasterPos2f(x,y); //Specifies where to display the text
                 for(ch=str;*ch!='\0';ch++)
     {
                 if(font_type==10)              
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *ch);
                 else if(font_type==12)              
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *ch);
                 else if(font_type==18)              
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch);
                 else if(font_type==11)              
                 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *ch);
                 else if(font_type==24)              
                 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *ch);
                 
                 
     }    
     return 1; 
                            
}

int main(int argc,char **argv)
{
    int i;
    printf("                     SINGLY LINKED LIST                       \n\n");
    printf("          USE RIGHT MOUSE BUTTON TO SELECT AN OPERATION  \n\n");
    Sleep(2500);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(900,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Linked List Demonstration"); 
    glutDisplayFunc(display);
    myinit();
    glutCreateMenu(mymenu);
    glutAddMenuEntry("Insert Rear",1);
    glutAddMenuEntry("Insert Front",2);
    glutAddMenuEntry("Delete Rear",3);
    glutAddMenuEntry("Delete Specified",4);
    glutAddMenuEntry("Exit",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 1;
    
}
