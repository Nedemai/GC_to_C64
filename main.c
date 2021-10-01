/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Nedemai
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */


 /* GC code provided by Nedemai October 2021 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "hardware/clocks.h"
#include "gamepads.h"

inline int8_t reverse(int8_t b)
{
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return b;
}


void Check_GC_Buttons(int gp_num);
int GC_Pin = 6;
int Commodore_pin_up = 10;
int Commodore_pin_down = 11;
int Commodore_pin_left = 12;
int Commodore_pin_right = 13;
int Commodore_pin_fire = 14;

GC_pad GC_Controller[1]; //we are only using 1 controller for this example
int GC_poll_speed = 5;         //1 - 1000 hz, 2 - 500 hz, 3 - 333hz 4 - 250hz, 5 - 200hz, 6 - 166.7hz, 7 - 142.9hz, 8 - 125hz, etc.

//this function should be 125 nops for a 1us pause, however given cycles introduced by C while loops, it is more like 113
void busywait125()
{
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
  __asm volatile("nop\n");
}

void busywait32(int wait) // this should delay a slight be longer than (32 * 8ns * (wait + x)) x being the amount of cycles the for loop structure takes.
{
  for (int i = 0; i < wait; i++) // for loops are expensive cycle wise, so limit how much it loops.
  {
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
  }
}

void busywait16(int wait) // this should delay a slight be longer than (32 * 8ns * (wait + x)) x being the amount of cycles the for loop structure takes.
{
  for (int i = 0; i < wait; i++)
  {
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
  }
}

void busywait8(int wait) // this should delay a slight be longer than (32 * 8ns * (wait + x)) x being the amount of cycles the for loop structure takes.
{
  for (int i = 0; i < wait; i++) //This for loop adds a significant delay of cycles.
  {
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
  }
}

bool GC_Controller_Reset(int pin)
{
  gpio_set_dir(pin, GPIO_OUT);
  int i = 8;
  while (i)
  {
    gpio_xor_mask(1ul << pin);
    busywait125();
    gpio_put(pin, 1);
    busywait125();
    busywait125();
    gpio_put(pin, 1);
    busywait125();
    i--;
  }

  // This is our stop bit
  gpio_xor_mask(1ul << pin);
  busywait125();
  busywait125();
  busywait125();
  gpio_xor_mask(1ul << pin);
  busywait32(1);
  // set the pin as an input
  gpio_set_dir(pin, GPIO_IN);

  return (true);
}



//A few things to mention
// for loops add a significant amount of cycles per loop.
// an educated guess as to the kind of timeframe this takes, I would predict somewhere around 8 cycles per loop.
//this code works because it was measured against an oscilloscope. Its sensitive.
//__asm volatile("nop\n"); takes EXACTLY 0.000000008 seconds to execute. If used right can allow for extremely accurate timing.
 /* GC code provided by Nedemai October 2021 */
//pin pin number, gp_num is the gamepad number 1-4 MAX, rumble well, you know, true or false.
void GC_poll_controller(int pin, int gp_num, bool rumble)
{
  unsigned int low_byte = 0;
  unsigned int high_byte = 0;
  int j = 0;

  if (GC_Controller[gp_num].rumble == true)
  {
    rumble = true;
  }
  else
  {
    rumble = false;
  }

  int command = (0x400300 + (rumble) + ((GC_Controller[gp_num].force_duration) << 2)); // brought is here so we only calculate once

  gpio_set_dir(pin, GPIO_OUT);
  int i = 24;
  while (i)
  {
    gpio_xor_mask(1ul << pin);
    busywait125();
     /* GC code provided by Nedemai October 2021 */
    // 1-6 seems to be some kind of speed or duration
    //3F or 63 places (64 levels)

    //       1-2-3-4-5-6  7 ---------- 8
    //rumb/e 1-1-1-1-1-1  1 - (on/off) 1 - rumble true/false
    gpio_put(pin, 0x01 & (command) >> (i - 1));
    busywait125();
    busywait125();
    gpio_put(pin, 1);
    busywait125();
    i--;
  }

  // This is our stop bit
  gpio_xor_mask(1ul << pin);
  busywait125();
  busywait125();
  busywait125();
  gpio_xor_mask(1ul << pin);
  busywait32(1);
  // set the pin as an input
  gpio_set_dir(pin, GPIO_IN);

  while (gpio_get(pin)) //Waiting for the line to be driven low by the controller ensures we exit at a sane place
  {                     //IMPORTANT FOR LOOPS ARE BAD HERE, AVOID!
    j++;
    if (j > 1024)
      break; //this still reads data allowing to detect unplug
  }

  busywait125();
  busywait125();

  for (int i = 31; i >= 0; i--)
  {
    low_byte += (gpio_get(pin) << i);
    // gpio_xor_mask(1ul << 10);
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    busywait32(12);
    busywait8(1);
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
  }
  for (int i = 31; i >= 0; i--)
  {
    high_byte += (gpio_get(pin) << i);
    // gpio_xor_mask(1ul << 10);
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    busywait32(12);
    busywait8(1);
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
    __asm volatile("nop\n");
  }

  //unplug detection
  if (low_byte == 0xFFFFFFFF || low_byte == 0xFFFFFFFE)
  { //Controller Unplugged}
    GC_Controller[gp_num].gp_hat = 0;
    GC_Controller[gp_num].gp_buttons = 0;
    GC_Controller[gp_num].y = 0;
    GC_Controller[gp_num].x = 0;
    GC_Controller[gp_num].cx = 0;
    GC_Controller[gp_num].cy = 0;
    GC_Controller[gp_num].L = 0;
    GC_Controller[gp_num].R = 0;
  }
  else
  {
    GC_Controller[gp_num].y = (0x7F - low_byte);
    GC_Controller[gp_num].x = -(0x7F - (low_byte >> 8));

    GC_Controller[gp_num].cy = (0x7F - (high_byte >> 16));
    GC_Controller[gp_num].cx = -(0x7F - (high_byte >> 24));

    GC_Controller[gp_num].x = GC_lookuptable[GC_Controller[gp_num].x & 0xFF];
    GC_Controller[gp_num].y = GC_lookuptable[GC_Controller[gp_num].y & 0xFF];
    GC_Controller[gp_num].cx = GC_lookuptable[GC_Controller[gp_num].cx & 0xFF];
    GC_Controller[gp_num].cy = GC_lookuptable[GC_Controller[gp_num].cy & 0xFF];

    GC_Controller[gp_num].L = (0x7F - high_byte);
    GC_Controller[gp_num].R = (0x7F - (high_byte >> 8));

    GC_Controller[gp_num].L = GC_lookuptable[GC_Controller[gp_num].L & 0xFF];
    GC_Controller[gp_num].R = GC_lookuptable[GC_Controller[gp_num].R & 0xFF];

    GC_Controller[gp_num].buttons = 0;

    GC_Controller[gp_num].buttons = (reverse(low_byte >> 16)) << 8;  //y
    GC_Controller[gp_num].buttons += reverse(low_byte >> 24) & 0xFF; //y

    Check_GC_Buttons(gp_num);
  }
  return;
}

bool updater(struct repeating_timer *t)
{

   //putting the polling code in a timer interrupt should allow the code to poll the controller without being interrupted, which would mess up timing
   GC_poll_controller(GC_Pin, 0, false);

  return true;
}

/*------------- MAIN -------------*/
int main(void)
{
   struct repeating_timer timer;
  add_repeating_timer_ms(GC_poll_speed, &updater, NULL, &timer); // 200hz timer for polling the GC controller

//for commodore 

  //UP
  gpio_init(Commodore_pin_up);
  gpio_set_dir(Commodore_pin_up , GPIO_OUT);
  gpio_put(Commodore_pin_up , 1);
  gpio_set_drive_strength(Commodore_pin_up , GPIO_DRIVE_STRENGTH_2MA);
  gpio_set_pulls(Commodore_pin_up , 1, 0); 

  //DOWN
  gpio_init(Commodore_pin_down);
  gpio_set_dir(Commodore_pin_down, GPIO_OUT);
  gpio_put(Commodore_pin_down, 1);
  gpio_set_drive_strength(Commodore_pin_down, GPIO_DRIVE_STRENGTH_2MA);
  gpio_set_pulls(Commodore_pin_down, 1, 0); 
  
  //LEFT
  gpio_init(Commodore_pin_left);
  gpio_set_dir(Commodore_pin_left, GPIO_OUT);
  gpio_put(Commodore_pin_left, 1);
  gpio_set_drive_strength(Commodore_pin_left, GPIO_DRIVE_STRENGTH_2MA);
  gpio_set_pulls(Commodore_pin_left, 1, 0);
  
  //RIGHT
  gpio_init(Commodore_pin_right);
  gpio_set_dir(Commodore_pin_right, GPIO_OUT);
  gpio_put(Commodore_pin_right, 1);
 gpio_set_drive_strength(Commodore_pin_right, GPIO_DRIVE_STRENGTH_2MA);
  gpio_set_pulls(Commodore_pin_right, 1, 0); 
  
  //FIRE
  gpio_init(Commodore_pin_fire);
  gpio_set_dir(Commodore_pin_fire, GPIO_OUT);
  gpio_put(Commodore_pin_fire, 1);
 gpio_set_drive_strength(Commodore_pin_fire, GPIO_DRIVE_STRENGTH_2MA);
  gpio_set_pulls(Commodore_pin_fire, 1, 0); 
  
//GC pin
  gpio_init(GC_Pin);
  gpio_set_dir(GC_Pin, GPIO_OUT);
  gpio_put(GC_Pin, 1);
 gpio_set_drive_strength(GC_Pin, GPIO_DRIVE_STRENGTH_2MA);
  gpio_set_pulls(GC_Pin, 1, 0);
  
  //board LED
   gpio_init(25);
  gpio_set_dir(25, GPIO_OUT);
  gpio_put(25, 1);


  //reset and rezero controllers on boot
  GC_Controller_Reset(GC_Pin);
  sleep_us(1);

  while (1)
  {
    sleep_ms(1); 
  }
  return 0;
}



void Check_GC_Buttons(int gp_num)
{
  GC_Controller[gp_num].gp_hat = 0;
  GC_Controller[gp_num].gp_buttons = 0;

  if (GC_Controller[gp_num].buttons & GC_BUTTON_Y)
  {
  }
  if (GC_Controller[gp_num].buttons & GC_BUTTON_B)
  {
  }
  if (GC_Controller[gp_num].buttons & GC_BUTTON_Z)
  {
  }
  if (GC_Controller[gp_num].buttons & GC_BUTTON_L)
  {
  }
  if (GC_Controller[gp_num].buttons & GC_BUTTON_R)
  {
  }
  if (GC_Controller[gp_num].buttons & GC_BUTTON_START)
  {
  }

  if (GC_Controller[gp_num].buttons & GC_BUTTON_A)
  {
     gpio_put(Commodore_pin_fire, 0);
  }
  else
  {
   gpio_put(Commodore_pin_fire, 1); 
  }


  if (GC_Controller[gp_num].y < -50)
   {
    gpio_put(Commodore_pin_up, 0);
   }
  else if (GC_Controller[gp_num].buttons & GC_BUTTON_UP)
  {
     gpio_put(Commodore_pin_up, 0);
  }
  else if (GC_Controller[gp_num].buttons & GC_BUTTON_X)
  {
    gpio_put(Commodore_pin_up, 0);
  }
 else
  {
   gpio_put(Commodore_pin_up, 1); 
  }

if (GC_Controller[gp_num].y > 50)
   {
    gpio_put(Commodore_pin_down, 0);
   }
  else if (GC_Controller[gp_num].buttons & GC_BUTTON_DOWN)
  {
    gpio_put(Commodore_pin_down, 0);
  }
  else
  {
   gpio_put(Commodore_pin_down, 1); 
  }


if (GC_Controller[gp_num].x < -50)
   {
    gpio_put(Commodore_pin_left, 0);
   }
  else if (GC_Controller[gp_num].buttons & GC_BUTTON_LEFT)
  {
    gpio_put(Commodore_pin_left, 0);
  }
  else
  {
   gpio_put(Commodore_pin_left, 1); 
  }

 if (GC_Controller[gp_num].x > 50)
   {
    gpio_put(Commodore_pin_right, 0);
   }
  else if (GC_Controller[gp_num].buttons & GC_BUTTON_RIGHT)
  {
    gpio_put(Commodore_pin_right, 0);
  }
  else
  {
   gpio_put(Commodore_pin_right, 1); 
  }

}



