// Standard includes
#include "ball.h"
#include "constants.h"
  
int pos_x, pos_y, delta_x, delta_y, old_x, old_y;
  
void init_ball() 
{
  srand(time(NULL));
    
  pos_x = 68 + rand() % BALL_SIZE;
  pos_y = 80 + rand() % BALL_SIZE;
    
  delta_x = VELOCITY;
  delta_y = VELOCITY;
    
  old_x = 0;
  old_y = 0;
}

 void pulse_on_collision(bool pulse)
{
  if(pulse)
    vibes_short_pulse();
} 
  
void draw_ball(GContext* ctx)
{
  // Wipe old circle
    
    GPoint point = GPoint(old_x, old_y);
    graphics_context_set_fill_color(ctx, COLOR_BACKGROUND);
    graphics_fill_circle(ctx, point, BALL_SIZE>>1);
    
    // Draw new circle
    
    point = GPoint(pos_x, pos_y);
    graphics_context_set_fill_color(ctx, COLOR_FOREGROUND);
    graphics_fill_circle(ctx, point, BALL_SIZE);
}
  
void tick_ball ()
{
  bool usePulse = false;
  
    old_x = pos_x;
    old_y = pos_y;
    
    pos_x = pos_x + delta_x;
    pos_y = pos_y + delta_y;
    
    if (pos_x > MAX_X)
    {
        pos_x = MAX_X -BALL_SIZE;
        delta_x = -VELOCITY;
        pulse_on_collision(usePulse);
    }
    
    if (pos_x < MIN_X)
    {
        pos_x = MIN_X + BALL_SIZE;
        delta_x = VELOCITY;
        pulse_on_collision(usePulse);
    }
    
    if (pos_y > MAX_Y)
    {
        pos_y = MAX_Y - BALL_SIZE;
        delta_y = -VELOCITY;
        pulse_on_collision(usePulse);
    }
    
    if (pos_y < MIN_Y)
    {
        pos_y = MIN_Y + BALL_SIZE;
        delta_y = VELOCITY;
        pulse_on_collision(usePulse);
    }
} 



void check_for_ball_collision (PLAYER player, bool headingRight)
{
  bool usePulse = true;
  
  int playerHeight = player.y + player.h;
    
  if((pos_y > player.y && pos_y - BALL_SIZE < playerHeight))
  {
    if (headingRight)
    {
      if ((pos_x + BALL_SIZE) > player.x) 
      {
          APP_LOG	(APP_LOG_LEVEL_DEBUG, "COLLSION WITH PLAYER 2");
          APP_LOG	(APP_LOG_LEVEL_DEBUG, "checking for collision: %d, %d - player position:%d, %d ", pos_x, pos_y, player.y, playerHeight );
          pos_x = player.x -BALL_SIZE;
          delta_x = -VELOCITY;
          pulse_on_collision(usePulse);
      }
    }
    else
    {
      if (pos_x < player.x + player.w)
      {
          APP_LOG	(APP_LOG_LEVEL_DEBUG, "COLLSION WITH PLAYER 1");
          APP_LOG	(APP_LOG_LEVEL_DEBUG, "checking for collision: %d, %d - player position:%d, %d ", pos_x, pos_y, player.y, playerHeight );
          pos_x = player.x + player.w;
          delta_x = VELOCITY;
          pulse_on_collision(usePulse);
      }
    }
  }
} 


