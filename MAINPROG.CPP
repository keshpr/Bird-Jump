

#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<iostream.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<fstream.h>


#define BODYBCOLOR YELLOW
#define BODYCOLOR YELLOW
#define EYEBCOLOR BLACK
#define EYECOLOR BLACK
#define WINGBCOLOR RED
#define WINGCOLOR RED
#define XR 30
#define YR 15
#define EYERAD 5
#define WINGRADIUS 10
#define EOFFSET 15
#define WOFFSET 10
#define GRAV 300
#define PIPESPEED 10
#define BSPEED 150
#define TIME 90
#define LOWERLIMIT 400
#define UPPERLIMIT 40
#define LEFTLIMIT 0
#define RIGHTLIMIT 400
#define LANDSCAPECOLOR BROWN
#define LINELO 440
#define LINEUP 25
#define JUMPTIME 3
#define MAXBULLETS 30
#define BULLETLENGTH 20
#define BULLETBREADTH 10
#define BULLETCOLOR RED
#define BULLETBCOLOR RED
#define BULLETX 400
#define BIRDTIME 10
#define MINBIRDTIME 1
#define MAXBIRDS 10
#define BSPEEDRANGE 30
#define BSPEEDMIN 10
#define GPATH "C:\\TC\\BGI" //This is the path to the BGI folder within Turbo C++

#define X 100
#define Y 200
#define AL .001
#define ROFFSET 25
#define LOFFSET 5
#define TOFFSET 18
#define BOFFSET 10
class Object
{
   float x,y;
   protected:
   float lm,rm,tm,bm;
   int color, bcolor;
   public:
   void setXY(float a,float b)
   {
     x=a;
     y=b;
   }
   void setColors(int col, int bcol)
   {
     color = col;
     bcolor = bcol;
   }
   float returnX()
   {
     return(x);
   }
   float returnY()
   {
     return(y);
   }
   float returnL()
   {
     return(lm);
   }
   float returnR()
   {
     return(rm);
   }
   float returnT()
   {
     return(tm);
   }
   float returnB()
   {
     return(bm);
   }
   void moveVert(float a)
   {
      y = y + a;
   }
   void moveHor(float a)
   {
      x = x + a;
   }
   int inContact(Object* obj)
   {

       if((abs(tm - obj->returnB()) - abs(bm-tm+obj->returnB()-obj->returnT()))<0
       &&(abs(rm - obj->returnL()) - abs(rm-lm+obj->returnR()-obj->returnL()))<0
       )
	  return 1;
       return 0;
   }

};
class Circle : public Object
{
   int rad;
   public:
   void setPoints()
   {
       lm = returnX()-rad;
       rm = returnX()+rad;
       tm = returnY()-rad;
       bm = returnY()+rad;
   }
   void setRadius(int r)
   {
     rad = r;
   }
   void draw()
   {
     setcolor(color);
     setfillstyle(1,bcolor);
     circle(returnX(),returnY(),rad);
     floodfill(returnX(),returnY(),color);
   }
};
class Ellipse : public Object
{
   int stangle,endangle, xrad, yrad;
   public:
   void setPoints()
   {
       lm = returnX()-xrad + LOFFSET;
       rm = returnX()+xrad - ROFFSET;
       tm = returnY()-yrad + TOFFSET;
       bm = returnY()+yrad + BOFFSET;
   }
   void setStangle(int r)
   {
     stangle = r;
   }
   void setEndangle(int r)
   {
     endangle = r;
   }
   void setXRadius(int r)
   {
     xrad = r;
   }
   void setYRadius(int r)
   {
     yrad = r;
   }
   void draw()
   {
     setcolor(color);
     setfillstyle(1,bcolor);
     ellipse(returnX(),returnY(),stangle,endangle,xrad,yrad);
     floodfill(returnX(),returnY(),color);

   }
};
class PieSlice : public Object
{
   int stangle,endangle, radius;
   public:
   void setStangle(int a)
   {
      stangle = a;
   }
   void setEndangle(int a)
   {
      endangle = a;
   }
   void setRadius(int a)
   {
      radius = a;
   }
   void draw()
   {
     setcolor(color);
     setfillstyle(1,bcolor);
     pieslice(returnX(),returnY(),stangle,endangle,radius);
     floodfill(returnX(),returnY(),color);

   }

};
class Rectangle : public Object
{
   float length, breadth;
   public:
   void setPoints()
   {
       lm = returnX() - length/2;
       rm = lm + length;
       tm = returnY() - breadth/2;
       bm = tm + breadth;
   }
   void setRect(float len, float br)
   {
      length = len;
      breadth = br;
      setPoints();
   }
   void draw()
   {
      setcolor(color);
      setfillstyle(1,bcolor);
      rectangle(lm,tm,rm,bm);
      floodfill(returnX(),returnY(), color);
   }
};
class Bird: public Object
{

   Ellipse body;
   Circle eye;
   PieSlice wing;
   int EOffset;
   int WOffset;
   public:
   int numBird;
   float xVelocity, yVelocity;
   void setYVel(float vel)
   {
      yVelocity = vel;
   }
   void setXVel(float vel)
   {
      xVelocity = vel;
   }
   void setPoints()
   {
       body.setPoints();
       lm = body.returnL();
       rm = body.returnR();
       tm = body.returnT();
       bm = body.returnB();
   }
   void setOffset(int eoff, int woff)
   {
      EOffset = eoff;
      WOffset = woff;
   }
   void setBody(int col , int bcol, int st, int end,int xr,int yr)
   {
      body.setColors(col,bcol);
      body.setStangle(st);
      body.setEndangle(end);
      body.setXRadius(xr);
      body.setYRadius(yr);
   }
   void setEye(int col, int bcol, int rad)
   {
      eye.setColors(col,bcol);
      eye.setRadius(rad);
   }
   void setWing(int col , int bcol, int st, int end,int r)
   {
      wing.setColors(col,bcol);
      wing.setStangle(st);
      wing.setEndangle(end);
      wing.setRadius(r);
   }
   void draw()
   {
      setCoords();
      body.draw();
      eye.draw();
      wing.draw();
   }
   void setCoords()
   {
      body.setXY(returnX(),returnY());
      eye.setXY(returnX()+EOffset,returnY());
      wing.setXY(returnX()-WOffset,returnY());
      setPoints();
   }
   void setBird()
   {
      setXY(X,Y);
      xVelocity = yVelocity = 0;
      setBody(BODYCOLOR,BODYBCOLOR,0,360,XR,YR);
      setEye(EYECOLOR,EYEBCOLOR,EYERAD);
      setWing(WINGCOLOR,WINGBCOLOR,180,360,WINGRADIUS);
      setOffset(EOFFSET,WOFFSET);
      setPoints();
   }
   void accelerateY(float amt)
   {
     yVelocity = yVelocity - amt;
   }
   void accelerateX(float amt)
   {
     xVelocity = yVelocity - amt;
   }
   Bird()
   {
      setXY(X,Y);
      xVelocity = 0;
      yVelocity = 0;
      setBird();
   }
   

};
class Bullet: public Object
{
    Rectangle body;

    int length, breadth;
    public:
    int numBullet;

    float xVelocity, yVelocity;
    void setPoints()
    {
       body.setPoints();
       lm = body.returnL();
       rm = body.returnR();
       tm = body.returnT();
       bm = body.returnB();
    }
    void setBody(int col, int bcol)
    {
       body.setColors(col,bcol);
       body.setXY(returnX(),returnY());
       body.setRect(length,breadth);
    }
    void setBullet()
    {
       setBody(BULLETCOLOR, BULLETBCOLOR);
       setPoints();
    }
    void draw()
    {
       setCoords();
       body.draw();
    }
    void setCoords()
    {
       body.setXY(returnX(),returnY());
       setPoints();
    }

    void initBullet(float x, float y)
    {

       setXY(x,y);
       yVelocity = 0;
       xVelocity = BULLETX;
       length = BULLETLENGTH;
       breadth = BULLETBREADTH;
       setBullet();
    }
};


// Struct that deals with user data
struct player
{
	long int score;		// Current score
	char userId[50];	// User ID number
    char name[50];		// Name of the user
	int flag;			//Indicates whether a record for the current player has been created or not
};

void splash();
void createUser(player*);
void userId(player*);
void setPlayer(player*);
void move(Bird*, Bullet**, Bird**);
void updateScore(player*);
void gameOver(char*);
void runGame(Bird*,player*);
void help();
void leaderboard(player*);
void highscores(player*);
void credits();


void main()
{
   int gd = DETECT, gm;
   Bird flappy;				// Creates bird object for player to play with
   Bird* fpoint;			// Pointer to above mentioned bird object
   player p;				// Current player
   player* pp = &p;			// Address to above player data storage
   fpoint = &flappy;
   int ch;					// User choice holder
   fstream x("scores.dat",ios::in|ios::binary);		// File to store all relevant data
   x.close();
   
   splash();
   
   do{
	   clrscr();
       gotoxy(30,6);
       cout<<"1.Create a new User ID";
       gotoxy(30,8);
       cout<<"2. Use existing User ID";
       gotoxy(30,10);
	   cout<<"3. Exit";
       gotoxy(30,12);
	   cout<<"Enter your choice\t";
	   cin>>ch;
	   switch(ch)
	   {
		   case 1:
			  createUser(pp);
			  break;
		   case 2:
		      userId(pp);
			  break;
		   case 3:
		      clrscr();
			  credits();
			  exit(0);
			  break;
		   
	   }
   }while(ch!=1 && ch!=2 && ch!=3);

   fpoint->setBird();
   
   /*
   Displaying Menu until user decides to quit
   */
   do
   {
      clrscr();

      gotoxy(30,6);
      cout<<"Bird Jump";
      gotoxy(30,8);
      cout<<"1. Play";
      gotoxy(30,10);
      cout<<"2. Help";
      gotoxy(30,12);
      cout<<"3. Leaderboard";
      gotoxy(30,14);
      cout<<"4. Your Highscores";
      gotoxy(30,16);
      cout<<"5. Switch to different User ID";
      gotoxy(30,18);
      cout<<"6. Exit";
      gotoxy(30,20);
      cout<<"Enter your choice: \t";

      cin>>ch;
      switch(ch)
      {
	 case 1:
	    initgraph(&gd,&gm,GPATH);
	    pp->score = 0;
	    runGame(fpoint,pp);
	    closegraph();
	    break;
	 case 3:
	    clrscr();
	    leaderboard(pp);
	    break;
	 case 2:
	    help();
	    break;
	 case 4:
	    highscores(pp);
	    break;	    
	 case 5:
	    userId(pp);
	    break;
     case 6:           
	    credits();	                
	    exit(0);
      }
   }while(ch!=6);

   
   getch();

   free(fpoint);

}

/* Displays the initial splash/intro screen */
void splash()
{
   int gd = DETECT, gm;
   clrscr();
   initgraph(&gd,&gm,GPATH);
   setcolor(WHITE);
   settextstyle(DEFAULT_FONT,0,4);
   outtextxy(150,60,"Bird Jump");
   Bird fl;
   fl.setBird();
   fl.setXY(100,250);
   fl.draw();
   Bullet b1,b2;
   b1.initBullet(300,200);
   b2.initBullet(400,300);
   b1.draw();
   b2.draw();
   getch();
   cleardevice();
   closegraph();
}

/*Creates a new user with a new User ID*/
void createUser(player* pp)
{
   int i, flag = 0;
   player p;   
   fstream x("scores.dat",ios::in | ios::binary);   
   do
   {  
      flag = 0;
	  clrscr();   
      gotoxy(30,6);
	  cout<<"Enter your name:\t";
      cin>>pp->name;
	  clrscr();
	  gotoxy(30,8);
      cout<<"\n\nEnter your userid:\t";
      cin>>pp->userId;
	  x.close();
      fstream x("scores.dat",ios::in | ios::binary);
      while(x.read((char*)&p,sizeof(player)))
      {
         if(strcmp(p.userId,pp->userId) == 0)
         {
            clrscr();
			gotoxy(20,4);
		    cout<<"User ID Already Exists";
		    flag = 1;
			getch();
		    break;
         }
      }
   }while(flag == 1);      
   pp->score = 0;
   pp->flag = 1;
   setPlayer(pp);
   getch();
   x.close();
}

/*Displays information about how to play the game */
void help()
{
   int gd = DETECT, gm;
   initgraph(&gd,&gm,GPATH);
   outtextxy(150,150,"Press any button to make the bird pulse up.");
   outtextxy(150,170,"Avoid the red bullets. You lose if you get hit.");
   outtextxy(150,190,"Do not go above a certain limit.");
   outtextxy(150,210,"Do not go below a certain limit.");
   outtextxy(150,230,"Horizontal lines mark the boundary.");
   outtextxy(150,250,"Get the highest score possible.");
   outtextxy(150,290,"Press any button to go back to main menu.");
   getch();
   cleardevice();
   closegraph();
}

/*Used to switch to a different user ID*/
void userId(player* pp)
{
   clrscr();
   player p;
   fstream x("scores.dat",ios::in | ios::binary);
   int flag = 0;   
   do{
   clrscr();
   gotoxy(20,10);
   cout<<"Enter a valid userid:\t";
   cin>>pp->userId;
   x.close();
   fstream x("scores.dat",ios::in | ios::binary);
   
   while(x.read((char*)&p,sizeof(player)))
   {
	  if(strcmp(p.userId,pp->userId) == 0)
	  {		 
		 flag = 1;
		 break;
	  }
   }
   }while(flag == 0);
   pp->score = 0;
   x.close();
}
/*
Creates a record for the user
at the end of the file
It creates the file if the file is not already created
*/
void setPlayer(player* pp)
{
   pp->score = 0;
   fstream x("scores.dat",ios::out|ios::binary|ios::app);
   x.write((char*)pp,sizeof(player));
   x.close();   
}

/*
Makes all the objects on the screen move
*/
void move(Bird* fp, Bullet** bullets)
{

   fp->moveVert(-1*fp->yVelocity*TIME*.001);
   fp->accelerateY(GRAV*TIME*.001);
   for(int i =0; i<MAXBULLETS ;i++)
   {
      if(bullets[i] != NULL)
      {
	 bullets[i]->moveHor(-1*bullets[i]->xVelocity * TIME * .001);
      }
   }

}

/*
Displays message on screen when game is over
*/
void gameOver(char* scpr)
{
   settextstyle(DEFAULT_FONT,0,2);
   outtextxy(100,100,"GAME OVER!!!");
   outtextxy(100,125,scpr);
   outtextxy(100,150,"Press any key to go to menu.");
}

/*
Function that makes the game run
Controls the parameters associated with that
session of the game
*/
void runGame(Bird* fp, player* pp)
{
   if(pp->flag == 1)
	   pp->flag = 0;
   else
      setPlayer(pp);
   fp->setBird();
   int num = 0;
   int count = JUMPTIME;
   int bulletCount = 0;
   int bulletTime = 0;
   int bulletFlag = 1;
   int birdNum = 0;
   int i;
   long int score = 0;
   char sc[5];
   char scpr[15];
   scpr[0] = '\0';


   Bullet* bullets[MAXBULLETS];

   for(i=0;i<MAXBULLETS;i++)
      bullets[i] = NULL;
   srand(time(NULL));

   while(fp->returnY() <= LOWERLIMIT && fp->returnY()>=UPPERLIMIT)
   {

	 /*
	 Checking if the bird is in conttact with
	 anything else, i.e, if game is over
	 */
	 for(int j=0;j<MAXBULLETS;j++)
	 {
	    if(bullets[j]!=NULL)
	    {
	       if(fp->inContact(bullets[j]))
	       {

		  pp->score = score;
		  updateScore(pp);
		  gameOver(scpr);
		  getch();
		  return;
	       }
	    }
	 }
	 /*
	   Randomly setting bulletTime for the
	   next bullet
	   */
	 if(bulletFlag == 1)
	 {
	    bulletFlag = 0;
	    bulletTime = rand() % BIRDTIME + MINBIRDTIME;

	    bulletCount = bulletTime;
	 }
	 /*
	 Updating score by checking if
	 bullet has crossed
	 */
	 for(int i=0; i<MAXBULLETS;i++)
	 {

	    if(bullets[i] != NULL && bullets[i]->returnX() <= LEFTLIMIT)
	    {
	       free(bullets[i]);
	       bullets[i] = NULL;
	       score++;
	       strcpy(scpr,"Score:");
	       strcat(scpr,ltoa(score,sc,10));

	    }

	 }

	 /* When something is pressed

	 */
	 if(kbhit() && count <= 0)
	 {
	    fp->setYVel(BSPEED);

	    /*
	       Ensuring minimum jump time
	       is taken to jump again
	    */

	    while(kbhit())
	    getch();
	    count = JUMPTIME;
	 }
	 count--;
	 /*    Creating the bullet
	       after bulletTime has ellapsed
	    */
	 if(bulletCount <=0)
	 {

	    bulletFlag = 1;
	    float x = getmaxx();
	    float y = rand()%LOWERLIMIT + UPPERLIMIT;

	    Bullet* bu = (Bullet*)malloc(sizeof(Bullet));
	    bu->initBullet(x,y);
	    i=0;
	    while(i<MAXBULLETS && bullets[i]!=NULL)
	       i++;
	    bu->numBullet = i;
	    bullets[i] = bu;
	    num++;
	 }
	 bulletCount--;

	 /*
	 Moving the objects on the screen
	 */
	 move(fp,bullets);

	 /*
	 Drawing the objects
	 */
	 cleardevice();
	 fp->draw();
	 for(i=0;i<MAXBULLETS;i++)
	    if(bullets[i]!=NULL)
	    bullets[i]->draw();
	 setcolor(LANDSCAPECOLOR);

	 line(LEFTLIMIT,LINELO,getmaxx(),LINELO);
	 line(LEFTLIMIT,LINEUP,getmaxx(),LINEUP);
	 outtextxy(100,50,scpr);
	 delay(TIME);

   }
   pp->score = score;
   fp->setBird();
   gameOver(scpr);
   updateScore(pp);
   getch();
   cleardevice();

}

/*
Displays the top 10 scores gotten if available.
Displays all the scores if the total
number of scores is less than 10
*/
void leaderboard(player* pl)
{
	clrscr();
	int flag = 0;
	player p;
	fstream x;

	x.open("scores.dat",ios::in|ios::binary);
	cout<<"\t\t\t\tLeaderboard\n";
	cout<<"\t\tUser Id\t\t\t\tScore\n\n";
	int i =0;

	while(x.read((char*)&p,sizeof(player)) && i<10)
	{

	   cout<<"\t\t"<<p.userId<<"\t\t\t\t"<<p.score<<"\n\n";
	   i++;
	}
	x.close();
	getch();
	return;

}

/*
Displays the top 10 scores gotten by the current player if available.
Displays all the scores if the total
number of scores is less than 10
*/
void highscores(player* pl)
{
	clrscr();
	int flag = 0;
	player p;
	fstream x;

	x.open("scores.dat",ios::in|ios::binary);
	cout<<"\t\t\t\tYour Highscores\n";
	cout<<"\t\tUser Id\t\t\t\tScore\n\n";
	int i =0;

	while(x.read((char*)&p,sizeof(player)) && i<10)
	{

	   if(strcmp(p.userId,pl->userId) == 0)
           {   
              cout<<"\t\t"<<p.userId<<"\t\t\t\t"<<p.score<<"\n\n";
	      i++;
           }
	}
	x.close();
	getch();
	return;

}
/*
Inserts the record with userId and score
into the list of scores, keeping the
order based on score intact
*/
void updateScore(player* pp)
{
   int i=0;
   player p;
   player t = *pp;
   int flag = 0;
   fstream x("scores.dat",ios::in|ios::out|ios::binary);
   while(x.read((char*)&p,sizeof(player)))
   {
      if(p.score <= pp->score)
      {
	 flag = 1;
	 x.seekp(sizeof(player)*i,ios::beg);
	 x.seekg(sizeof(player)*i,ios::beg);
	 break;
      }
      i++;
   }

   x.write((char*)&t,sizeof(player));
   t=p;
   i++;
   x.seekg(sizeof(player)*i,ios::beg);
   x.seekp(sizeof(player)*i,ios::beg);
   while(x.read((char*)&p,sizeof(player)))
   {
      x.seekp(sizeof(player)*i,ios::beg);
      x.write((char*)&t,sizeof(player));
      t=p;
      i++;
      x.seekg(sizeof(player)*i,ios::beg);
   }
   x.seekp(sizeof(player)*i,ios::beg);
   x.write((char*)&t,sizeof(player));
   x.close();
}

/*Displays the screen with the names of the 
students wwho made this project, along with
their class and section */
void credits()
{
   int gd = DETECT , gm;
   initgraph(&gd,&gm,GPATH);
   cleardevice();
   settextstyle(DEFAULT_FONT,0,2);
   outtextxy(100,60,"Thanks for playing!");
   getch();
   cleardevice();
   closegraph();
}
/* End of Code*/