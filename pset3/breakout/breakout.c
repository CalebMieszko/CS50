//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // ball's velocity on x-axis
    double x_vel = drand48();
    
    // ball's velocity on y-axis
    double y_vel = 5;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // make the ball move!
        move(ball, x_vel, y_vel);
        
        pause(10);
        
        // establish a scoreboard
        updateScoreboard(window, label, points);
        
        // listen for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // make sure event was legitimate
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                // make paddle follow position of cursor
                double x_pos = getX(event) - getWidth(paddle) /2;
                double y_pos = 550;
                setLocation(paddle, x_pos, y_pos);
            }
        }
        GObject object = detectCollision(window, ball);
        // affect ball based on object hit
        if (object != NULL)
        {
            if (object == paddle)
            // change direction of vel if ball hits paddle
            {
                y_vel = -(y_vel);
            }
            else if (strcmp(getType(object), "GRect") == 0)
            // progress game if ball hits block
            {
                y_vel = -(y_vel);
                removeGWindow(window, object);
                points++;
                bricks--;
                
            }
        }
        
        // check for normal wall collisions
        if (getX(ball) + getWidth(ball) > getWidth(window) -1)
        {
            x_vel = -(x_vel);
        }
        else if (getY(ball) <= 0)
        {
            y_vel = -(y_vel);
        }
        else if (getX(ball) <= 0)
        {
            x_vel = -(x_vel);
        }
        // check for deadly life losing bottom collision!
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives --;
            setLocation(paddle, 160, 550);
            setLocation(ball, 200, 200);
            waitForClick();
            pause(100);
        }
    }
  
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // design bricks!
    int bricky_num = 15;
    for (int i = 0; i < ROWS; i++)
    {
        int brickx_num = 2;
        for (int j = 0; j < COLS; j++) 
        {
             GRect brick = newGRect(brickx_num + 2, bricky_num, 35, 20);
            // set colors by row
            if (i == 0)
            {
                setColor(brick, "GREEN");
            }
            if (i == 1)
            {
                setColor(brick, "ORANGE");
            }
            if (i == 2)
            {   
                setColor(brick, "YELLOW");
            }
            if (i == 3)
            {
                setColor(brick, "BLUE");
            }
            if (i == 4)
            {
                setColor(brick, "RED"); 
            }
            // fill 'em up!
            setFilled(brick, true);
            add(window, brick);
            bricky_num = bricky_num + 5;
            brickx_num = brickx_num + 40;
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(190, 200, 20, 20);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(175, 550, 70, 10);
    setColor(paddle, "BLACK"); 
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel(" ");
    setFont(label, "Arial-60");
    setColor(label, "GREEN");
    add(window, label);
    setLocation(label, 190, 300);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
