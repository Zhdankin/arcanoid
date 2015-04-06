#include <glut.h>
#include <windows.h>

#include "Ball.h"
#include "Brick.h"
#include "Deck.h"
#include "Game.h"

static DWORD last_idle_time;

Game myGame;

void animation()
{
    float dt;
    DWORD time_now;
    time_now = GetTickCount();
    dt = (time_now - last_idle_time) / 1000.f;

    // Animate
    myGame._myBall.move(dt);
    myGame._myDeck.move(dt);

    //check collision and change trajectory
    if(myGame.isCollision(myGame._myBall, myGame._myDeck))
    {
        myGame.changeTrajectory(myGame._myBall, myGame._myDeck, true);
    }

    std::list<Brick>::iterator id = myGame._bricks.begin();
    while (id != myGame._bricks.end())
    {
        Brick brick = *id;
        if(myGame.isCollision(myGame._myBall, brick))
        {
            myGame.changeTrajectory(myGame._myBall, brick, false);
            id = myGame._bricks.erase(id);
        }
        else{
            ++id;
        }
    }

    // Save time_now for next time
    last_idle_time = time_now;

    // Force redraw
    glutPostRedisplay();
}

static int oldPositionX;
static int oldPositionY;
void MouseMotion(int x, int y)
{
    myGame._myDeck.increaseSpeed(-(oldPositionX - x), 0.f, 0.f /*-(oldPositionY - y)*/);

    if (!myGame._myBall.isRunning())
    {
        myGame._myBall.setRunning(true);
        myGame._myBall.setSpeed(-(oldPositionX - x), 1.f, 0.f);
    }
    oldPositionX = x;
    oldPositionY = y;
}

void MouseButton(int button, int state, int x, int y)
{
    // Respond to mouse button presses.
    oldPositionX = x;
    oldPositionY = y;
}

// not using now
void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':

        exit (0);
        break;

    case 'a': // turn left
        printf("a button pressed \n");
        break;

    case 's': //turn down
        printf("s button pressed \n");
        break;

    case 'd': // turn right
        printf("d button pressed \n");
        break;

    case 'w': //turn up
        printf("w button pressed \n");
        break;
    default:
        printf("unprogrammed button \"%c\" pressed \n",key);
        break;
    }
}


void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_NORMALIZE); 
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); //0 lamp
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    const GLfloat arr[] = {4.0f, 2.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, arr);
    glShadeModel(GL_SMOOTH);

    //draw ball and deck
    myGame._myBall.draw();
    myGame._myDeck.draw();

    // draw myGame._bricks
    std::list<Brick>::iterator id = myGame._bricks.begin();
    while (id != myGame._bricks.end())
    {
        Brick brick = *id;
        brick.draw();
        ++id;
    }
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, w/h, 0.0005, 10.0);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
} 

int main(int argc, char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Arcanoid"); //window name
    glutDisplayFunc(render); // paint window
    glutReshapeFunc(reshape); // change window size

    glutKeyboardFunc (Keyboard); //press button
    glutMouseFunc (MouseButton); //pres mouse button
    glutMotionFunc (MouseMotion); // move mouse
    myGame.initScene();

    glutIdleFunc (animation); //idle animation

    last_idle_time = GetTickCount();
    glutMainLoop();
    return(0);
}
