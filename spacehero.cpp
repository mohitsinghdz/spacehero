#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<GL/glut.h>
#include<limits.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include<cstring>
#include<iostream>
#include<vector>
#include"reshape.cpp"
using namespace std;
struct missile{
  int x,y;
};

struct ship{
  int shipx;
  int shipy;
  bool sl,sr;
}hero;


GLdouble width=1920, height=1080; //windows frame;
double segmentlen;
int state;//represents the state of the game 0 =home;1=in game;2=pause;3=exit;


//Background
int star[200][2],numstar,k;
float starsize[200];

//Score
int Score;

//enimies
GLfloat enemypos[50][2];
int enemycol[50][3];
bool enemypresent[50];
int enemycount;

void initialize()
{
  //set_settings();
  int i,seg_len=1920/50;
  srand(time(NULL));
  Score=0;
  k=0;
  hero.shipx= 915,
  hero.shipy= 20;
  hero.sl=false;
  hero.sr=false;
  state=0;
  for(i=0;i<50;i++)
  {
    enemypos[i][0]=(seg_len*i) + 15 + rand()%((int)(seg_len -31));
    enemypos[i][1]=height-(3*15);
    enemypresent[i]=true;
    enemycol[i][0]=rand()%10000;
    enemycol[i][1]=rand()%10000;
    enemycol[i][2]=rand()%10000;

  }
  enemycount=50;

}

//hero ship design
void draw_main_ship(int x, int y)
{
    glPushMatrix();
    glTranslatef(hero.shipx,hero.shipy,0);
    //Letf Wing
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(30,0);
        glVertex2f(30,50/2.0);
    glEnd();

    //Right Wing
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(60,0);
        glVertex2f(90,0);
        glVertex2f(30,50/2.0);
    glEnd();

    //Main Body
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f(30,0);
        glVertex2f(60,0);
        glVertex2f(60,V=50);
        glVertex2f(30+30/2.0, (4.0*50)/3.0);
        glVertex2f(30,50);
    glEnd();

    //Main Body's Window
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
        glVertex2f(30+(30/3.0), 50/2.0);
        glVertex2f(30 + (2.0*30)/3.0, 50/2.0);
        glVertex2f(30 + (2.0*30)/3.0, (3*50)/4.0);
        glVertex2f(30+(30/3.0), (3*50)/4.0);
    glEnd();
    glPopMatrix();
    glFlush();
}

void draw_string(string str)
{
    for(unsigned int i=0;i<str.length();i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin()+i));
    }
}

void draw_background()
{
    k = (k+1)%BACKGROUND_REFRESH_DELAY;
    if(k==1)
    {
        num_stars = STARS_MIN + rand()%((int)(STARS_MAX-STARS_MIN + 1));
        for(int i=1;i<=num_stars;i++)
        {
            star_pos[i][0] = rand()%((int)width);
            star_pos[i][1] = rand()%((int)height);
            star_size[i] = (STARS_MIN_SIZE + rand()%((int)(STARS_MAX_SIZE - STARS_MIN_SIZE + 1))) / (100.0);
        }
    }
    glColor3f(252/255.0,228/255.0,94/255.0);
    for(int i=0;i<num_stars;i++)
    {
        glPointSize(star_size[i]);
        glBegin(GL_POINTS);
        glVertex2f(star_pos[i][0], star_pos[i][1]);
        glEnd();
    }
}



int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize((int) width, (int) height);
  glutCreateWindow("spacehero");
  glutFullScreen();
  initialize();
  glutReshapeFunc(void *reshape(int w, int h)//takes pointer to the function; glutReshapeFunc sets the reshape callback for the current window. The reshape callback is triggered when a window is reshaped. A reshape callback is also triggered immediately before a window's first display callback after a window is created or whenever an overlay for the window is established. The width and height parameters of the callback specify the new window size in pixels. Before the callback, the current window is set to the window that has been reshaped.
  {
      hero.shipx = (hero.shipx*w)/width;
      width = (GLdouble) w;
      height = (GLdouble) h;
    //  adjust_menu_bounds();
      segmentlen = width/50;
      glViewport(0, 0, (GLsizei) width, (GLsizei) height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0, width, 0.0, height);
      glMatrixMode(GL_MODELVIEW);
  }
);


  return 0;
}
