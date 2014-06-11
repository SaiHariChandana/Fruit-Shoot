#include<stdio.h>
#include<stdlib.h>
#include<OpenGL/gl.h>
#include<GLUT/glut.h>
#include<string.h>
#include <sys/time.h>
#include<math.h>
#include<iostream>


using namespace std;

static int dispno=0;

char title1[]={"COMPUTER GRAPHICS PROJECT"};
char heading[]={"FRUIT SHOOT"};
char score_string[]={"Score : 0 "};
char balls_remaining_string[]={"Balls Remaining: 8"};
char by[]={"By"};
char chandana[]={"Sai Chandana       1PE10CS042"};
char karan[]={"Karan Rajpal       1PE10CS043"};

int color,RED=0,YELLOW=1,BLUE=2,BLACK=3;
float ex=100.0,ey=200.0;
static double lasttime;
int MOVE=0;
int FRUIT=0;
float start_x,start_y;
float yex,why;
int ctr=0;
float fruits_x[10];
float fruits_y[10];
int rock_size=20;
float catapult_x=100;
float catapult_y=200;
int last_collided=0;
int balls_remaining=8;
int score=0;


class fruit
{
public:
    float fx;
    float fy;
    fruit()
    {
        
    }
    fruit( float x, float y, float r =12, bool filled = true, unsigned int subdivs = 20 ) {
        draw_fruit(x,y,r,filled,subdivs);
    }
    void draw_fruit( float x, float y, int color=YELLOW,float r =20, bool filled = true, unsigned int subdivs = 20 ) {
        fx=x;
        fy=y;
        if(color==RED)
            glColor3f(1.0, 0.0, 0.0);
        else if(color==YELLOW)
            glColor3f(1.0,1.0,0.0);
        else if(color==BLUE)
            glColor3f(0.0,0.0,1.0);
        glBegin( GL_TRIANGLE_FAN );
        glVertex2f( x, y );
        
        
        for( unsigned int i = 0; i <= subdivs; ++i ) {
            float angle = i * ((2.0f * 3.14159f) / subdivs);

            if(i==5)
                glVertex2f( x + (r-4) * cos(angle), y + (r-4) * sin(angle) );    
            else
                glVertex2f( x + r * cos(angle), y + r * sin(angle) );
        }
        
        glEnd();
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(0.5);
        glBegin(GL_LINES);
        glVertex2f(x, y+16);
         glVertex2f(x+6, y+25);
        glEnd();

        
        
        
    }

    
};
fruit *a,*b,*c,*d,*e,*f;
 
double getftime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec*1e-6;
}
void draw_ground()
{
    glBegin(GL_POLYGON);
    glColor3f(0.42, 0.28, 0.11);
    glVertex2f(0.0,0.0);
    glVertex2f(0.0,100.0);
    glVertex2f(1000.0,100.0);
    glVertex2f(1000.0,0.0);
    glEnd();
    
}

void draw_tree()
{
    
    glPushMatrix();
    glScalef(1.7, 1.9, 0.0);
    glTranslatef(-200, -100, 0);
    
    glBegin(GL_POLYGON);        //bark
    glColor3f(0.6,0.0,0.0);
    glVertex2f(550 ,125 );
    glVertex2f(550 ,200 );
    glVertex2f(500 ,200 );
    glVertex2f(500 ,125 );
    glEnd();

    
    
    glBegin(GL_POLYGON);    //tree1-lower1
    glColor3f(0.0,1.0,0.0);
    glVertex2f(450 ,200 );
    glVertex2f(425 ,230 );
    glVertex2f(450 ,255 );
    glVertex2f(600 ,255 );
    glVertex2f(625 ,230 );
    glVertex2f(600 ,200 );
    glEnd();

    
    glBegin(GL_POLYGON);    //tree-lower2
    glColor3f(0.0,1.0,0.0);
    glVertex2f(460 ,255 );
    glVertex2f(435 ,260 );
    glVertex2f(460 ,310 );
    glVertex2f(590 ,310 );
    glVertex2f(615 ,260 );
    glVertex2f(590 ,255 );
    glEnd();

    
    glBegin(GL_POLYGON);    //tree-lower3
    glColor3f(0.0,1.0,0.0);
    glVertex2f(475 ,310 );
    glVertex2f(450 ,330 );
    glVertex2f(475 ,380 );
    glVertex2f(575 ,380 );
    glVertex2f(600 ,330 );
    glVertex2f(575 ,310 );
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(500 ,380 );
    glVertex2f(475 ,400 );
    glVertex2f(500 ,420 );
    glVertex2f(550 ,420 );
    glVertex2f(575 ,400 );
    glVertex2f(550 ,380 );
    glEnd();
    
    glPopMatrix();
    
}

void draw_catapult()
{
    
    GLint x=catapult_x,y=catapult_y;
    
    glColor3f(1.0, 1.0, 0.0);
    glLineWidth(20.0);
    glBegin(GL_LINES);
    glVertex2i(x, y);
    glVertex2i(x, y - 150);
    glEnd();
    
    glLineWidth(10.0);
    glBegin(GL_LINES);
    glVertex2i(x, y);
    glVertex2i(x - 45,y + 45);
    glEnd();
    
    
    glBegin(GL_LINES);
    glVertex2i(x, y);
    glVertex2i(x + 45, y + 45);
    glEnd();
}

void draw_rock( float x, float y, float r =20, bool filled = true, unsigned int subdivs = 20 ) {
    
    glColor3f(0.50, 0.50, 0.20);
        glBegin( GL_TRIANGLE_FAN );
        glVertex2f( x, y );
    
    for( unsigned int i = 0; i <= subdivs; ++i ) {
        float angle = i * ((2.0f * 3.14159f) / subdivs);
        glVertex2f( x + r * cos(angle), y + r * sin(angle) );
    }
    
    glEnd();
}



void string_display(double x, double y, char *str,int color=BLACK, int size=15)
{

	if(color==BLACK)
        glColor3f(0.45,0.45,0.45);
    else if(color==RED)
        glColor3f(1.0, 0.0, 0.0);
    else if(color==BLUE)
        glColor3f(0.0, 0.0, 0.9);
    else if(color==YELLOW)
        glColor3f(1.0, 1.0, 0.0);
	int len;
	int i=0;
	glRasterPos2f(x,y);
	len=strlen(str);
	for(i=0;i<len;i++)
	{
        if(size==15)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15,str[i]);
        else if(size==18)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
        else if(size==24)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);

	}
}


void display1()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.8);
    glColor3f(1.0,0.0,0.0);
    
    string_display(200,560,"A Computer Graphics Project",BLUE,24);
    string_display(260,600,"FRUIT SHOOT",BLUE,24);
    string_display(60, 400, "Instructions",RED,24);
    string_display(60, 370, "1. The Aim is to shoot down the Red and Yellow Fruits ",BLACK,18);
    string_display(60, 340, "2. The player can use the Mouse to aim the rock and shoot using the catapult",BLACK,18);
    string_display(60, 310, "3. The player is given only 8 balls to attempt to shoot down these fruits",BLACK,18);
   string_display(60, 280, "4. The Red and Yellow Fruits are 10 points each but the Blue balls are -5",BLACK,18); 
     
    string_display(400,70,by);
    string_display(420,45,chandana);
    string_display(420,30,karan);
    string_display(200,200,"Press Enter to begin shooting ",BLACK,18);
    glutSwapBuffers();}



 

void calculate_motion(int fruit_no)
{
    double finishtime, delta_t;
    finishtime = getftime();
    delta_t = finishtime - lasttime;
    if(MOVE)
    {
        
        float theta= atan (start_y/start_x);
        //theta=theta*180/3.142;
        cout<<endl<<"start y "<<start_y<<" start_x "<<start_x<<endl;
        cout<<"Theta "<<theta<<endl;
        float tee;
        cout<<"cos "<<cos(theta)<<endl;
        int force=7;
        if(start_y<50||start_x<50)
            force=14;
        if(start_y<75||start_x<75)
            force=16;
        if(start_y>1||start_x>1)
            force=-10;
        ex+=force*cos(theta);
        tee=ex/100.0;
        ey+=force*sin(theta)-0.5*tee*tee;   
        
    }
    if(FRUIT){
        why-=4;
        cout<<"vaii is "<<why<<endl;
        fruits_y[fruit_no]=why;
    }
    if(why<-700)
    {
        FRUIT=0;
    }
    if(ex>1600){
        MOVE=0;
        ex=catapult_x;
        ey=catapult_y;
    }
    
        
    if(ex<-5000)
    {
        MOVE=0;
        ex=catapult_x;
        ey=catapult_y;
    }
    
    
}


int check_collision()
{
    if(sqrt(pow(ex-a->fx, 2)+pow(ey-a->fy,2))<=rock_size+10)                 
    {
        
        FRUIT=1;
        cout<<"Collision scenes a"<<endl;
        if(last_collided!=0){
        score+=10;
        sprintf(score_string, "%s %d", "Score : ",score);
        MOVE=0;
        ex=catapult_x;
        ey=catapult_y;
        
        }
        last_collided=0;
        return 0;
    }
    
    if(sqrt(pow(ex-b->fx, 2)+pow(ey-b->fy,2))<=rock_size+10)                 
    {
        FRUIT=1;
        cout<<"Collision scenes b"<<endl;
        if(last_collided!=1){
        score-=5;
        sprintf(score_string, "%s %d", "Score : ",score);
            MOVE=0;
            ex=catapult_x;
            ey=catapult_y;

        }
        last_collided=1;
        return 1;
    }

    if(sqrt(pow(ex-c->fx, 2)+pow(ey-c->fy,2))<=rock_size+10)                 
    {
        FRUIT=1;
        cout<<"Collision scenes c"<<endl;
        if(last_collided!=2){
        score+=10;
        sprintf(score_string, "%s %d", "Score : ",score);
            MOVE=0;
            ex=catapult_x;
            ey=catapult_y;

        }
        last_collided=2;
        return 2;
    }
    if(sqrt(pow(ex-d->fx, 2)+pow(ey-d->fy,2))<=rock_size+10)                 
    {
        FRUIT=1;
        cout<<"Collision scenes d"<<endl;
        if(last_collided!=3){
            score+=10;
        sprintf(score_string, "%s %d", "Score : ",score);
            MOVE=0;
            ex=catapult_x;
            ey=catapult_y;

        }
        last_collided=3;
        return 3;
    }
    
    if(sqrt(pow(ex-e->fx, 2)+pow(ey-e->fy,2))<=rock_size+10)                 
    {
        FRUIT=1;
        cout<<"Collision scenes e"<<endl;
        if(last_collided!=4){
            
        
            score-=5;
        sprintf(score_string, "%s %d", "Score : ",score);
            MOVE=0;
            ex=catapult_x;
            ey=catapult_y;

        }
        last_collided=4;
        return 4;
    }
    
    if(sqrt(pow(ex-f->fx, 2)+pow(ey-f->fy,2))<=rock_size+10)                 
    {
        FRUIT=1;
        cout<<"Collision scenes f"<<endl;
        if(last_collided!=5){
            score+=10;
            sprintf(score_string, "%s %d", "Score : ",score);
            MOVE=0;
            ex=catapult_x;
            ey=catapult_y;
        }
        last_collided=5;
        return 5;
    }

    return last_collided;
}

void display2()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    string_display(100,675,score_string,RED,24);
    string_display(100,620,balls_remaining_string,RED,24);
    draw_tree();
    draw_catapult();
    draw_ground();
    draw_rock(ex, ey,rock_size);
    int fruit_no=check_collision();
    switch(fruit_no)
    {
        case 0:
            yex=a->fx;
            why=a->fy;
            calculate_motion(fruit_no);
            a->draw_fruit(yex, why);
            b->draw_fruit(fruits_x[1], fruits_y[1],BLUE);
            c->draw_fruit(fruits_x[2] , fruits_y[2]);
            d->draw_fruit(fruits_x[3], fruits_y[3], RED);
            e->draw_fruit(fruits_x[4], fruits_y[4], BLUE);
            f->draw_fruit(fruits_x[5], fruits_y[5], RED);
            break;
        case 1:
            yex=b->fx;
            why=b->fy;
            calculate_motion(fruit_no);
            a->draw_fruit(fruits_x[0], fruits_y[0]);
            b->draw_fruit(yex, why, BLUE);
            c->draw_fruit(fruits_x[2] , fruits_y[2]);
            d->draw_fruit(fruits_x[3], fruits_y[3],RED);
            e->draw_fruit(fruits_x[4], fruits_y[4], BLUE);
            f->draw_fruit(fruits_x[5], fruits_y[5], RED);
            break;
        case 2:
            yex=c->fx;
            why=c->fy;
            calculate_motion(fruit_no);
            a->draw_fruit(fruits_x[0], fruits_y[0]);    
            b->draw_fruit(fruits_x[1], fruits_y[1],BLUE);
            c->draw_fruit(yex, why);
            d->draw_fruit(fruits_x[3], fruits_y[3],RED);
            e->draw_fruit(fruits_x[4], fruits_y[4], BLUE);
            f->draw_fruit(fruits_x[5], fruits_y[5], RED);
            break;
        case 3:
            yex=d->fx;
            why=d->fy;
            calculate_motion(fruit_no);
            a->draw_fruit(fruits_x[0], fruits_y[0]);
            b->draw_fruit(fruits_x[1], fruits_y[1],BLUE);
            c->draw_fruit(fruits_x[2] , fruits_y[2]);
            d->draw_fruit(yex, why,RED);
            e->draw_fruit(fruits_x[4], fruits_y[4], BLUE);
            f->draw_fruit(fruits_x[5], fruits_y[5], RED);
            break;
        case 4:
            yex=e->fx;
            why=e->fy;
            calculate_motion(fruit_no);
            a->draw_fruit(fruits_x[0], fruits_y[0]);
            b->draw_fruit(fruits_x[1], fruits_y[1],BLUE);
            c->draw_fruit(fruits_x[2] , fruits_y[2]);
            d->draw_fruit(fruits_x[3], fruits_y[3],RED);
            e->draw_fruit(yex,why, BLUE);
            f->draw_fruit(fruits_x[5], fruits_y[5], RED);
            break;
        case 5:
            yex=f->fx;
            why=f->fy;
            calculate_motion(fruit_no);
            a->draw_fruit(fruits_x[0], fruits_y[0]);
            b->draw_fruit(fruits_x[1], fruits_y[1],BLUE);
            c->draw_fruit(fruits_x[2] , fruits_y[2]);
            d->draw_fruit(fruits_x[3], fruits_y[3],RED);
            e->draw_fruit(fruits_x[4], fruits_y[4], BLUE);
            f->draw_fruit(yex, why, RED);
            break;
        default:       
            calculate_motion(fruit_no);
            a->draw_fruit(fruits_x[0], fruits_y[0]);
            b->draw_fruit(fruits_x[1], fruits_y[1],BLUE);
            c->draw_fruit(fruits_x[2] , fruits_y[2]);
            d->draw_fruit(fruits_x[3], fruits_y[3],RED);
            e->draw_fruit(fruits_x[4], fruits_y[4], BLUE);
            f->draw_fruit(fruits_x[5], fruits_y[5], RED);
    }
    




    glutSwapBuffers();
    if(balls_remaining==0 && MOVE==0 && FRUIT==0)
        dispno=2;
    
}
void display3(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.8);
    glColor3f(1.0,0.0,0.0);
    string_display(250,650,heading,BLUE,24);    
    string_display(250,560,"Game Over",RED,24);
    string_display(200,450,"Game Developed By",BLUE,24);
    string_display(200,400,chandana,BLACK,18);
    string_display(200,350,karan,BLACK,18);
    sprintf(score_string, "%s %d","Your score is : ",score);
    string_display(250,200,score_string,RED,24);
    
    glutSwapBuffers();
 
}

void display()
{
    if(dispno==0)
    {
        display1();
    }
    else if(dispno==1)
    {
        
        display2();
    }
    else if(dispno==2)
    {
        display3();
    }
}


void keys(unsigned char key, int x,int y)
{
    int i;
    if(dispno==0 && key==13)
    {
        dispno=1;
        display();
    }
    //Cheat Codes
    //Increase number of balls
   if(dispno==1 && key==49)
   {
       balls_remaining++;
       sprintf(balls_remaining_string, "%s %d","Balls Remaining : ",balls_remaining);
       display();
   }

    //Stop playing
    if (dispno==1 && key=='s') {
        balls_remaining=0;
        sprintf(balls_remaining_string, "%s %d","Balls Remaining : ",balls_remaining);
        display();
    }
    //Increase Rock Size
    if(dispno==1 && key=='b') {
        rock_size=50;
    }
    
    
}

void shoot(int startx,int starty)
{
    start_x=(startx-catapult_x);
    start_y=(starty-catapult_y);
    cout<<endl<<"new x is "<<start_x<<endl<<"new y is "<<start_y;
    
    MOVE=1;
}

void mouse(int mouse, int state, int x, int y){
    switch(mouse){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_UP){
                y=700.0-y;
                
                if(x<catapult_x-100)
                    x=catapult_x-100;
                if(x>catapult_x+50)
                    x=catapult_x+50;
                if(y>catapult_y+50)
                    y=catapult_y+50;
                if(y<catapult_y-100)
                    y=catapult_y-100;                   
                balls_remaining--;
                sprintf(balls_remaining_string, "%s %d","Balls Remaining : ",balls_remaining);
                shoot(x,y);
            }

            break;
            
    }
    
}


void myInit(void) {
    glClearColor(0.0,0.0,0.0,0.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,700.0,0.0,700.0);
    last_collided=100;
    yex=600;
    why=320;
    fruits_x[0]=500; fruits_y[0]=300;
    fruits_x[1]=590; fruits_y[1]=280;
    fruits_x[2]=590; fruits_y[2]=440;
    fruits_x[3]=600; fruits_y[3]=540;
    fruits_x[4]=500; fruits_y[4]=600;
    fruits_x[5]=450; fruits_y[5]=430;
    a = new fruit();
    b=new fruit();
    c=new fruit();
    d=new fruit();
    e=new fruit();
    f=new fruit();
    
    
}

void drag(int x, int y){
    ex = x/1.0;
    ey = 700.0 - (y/1.0);
    if(x<catapult_x-100)
        ex=catapult_x-100;
    if(x>catapult_x+50)
        ex=catapult_x+50;
    
    if(ey>catapult_y+50)
        ey=catapult_y+50;
    if(ey<catapult_y-100)
        ey=catapult_y-100;
    
    
    
}
void reshape(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
    else
        glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}


int main(int argc, char *argv[]) {
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700.0 , 700.0);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Fruit Shoot");
    myInit();
    glutDisplayFunc(display);
    glutIdleFunc(glutPostRedisplay);
//    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMouseFunc(mouse);
    glutMotionFunc(drag);
	glutMainLoop();
	return 0;
}

