#include <stepam.h>

static char line[LINE_BUFFER_SIZE];
uint8_t char_counter = 0;

stepper_t stepper;
system_t sys;
float lpos = 0;

void resetLine()
{
  for(int i = 0; i<LINE_BUFFER_SIZE; i++)
  {
    line[i] = 0;
  }
}


void processIncomingChar(char c, char *line, uint8_t &counter)
{

  //Serial.println(c);

  if(c == '\n' or c == '\r')
  {
    Serial.println("end line");
  
    if(line[0] == 'G')
    {
        //Do something
    }
    if(line[0] == 'S')
    {
        sys.mode = SPEED;
        float x;
        for(int i = 0; i<counter; i++)
        {
            uint8_t i_counter = i+1;
            if(line[i] == 'S')
            {
                read_float(line, &i_counter, &x);
                stepper.target_speed = x;
                Serial.println(x);
            }
        }
    }
    if(line[0] == '!')
    {
        sys.mode = IDLE;
    }
    if(line[0] == '?')
    {
        Serial.println(lpos);
    }
    counter = 0;
    resetLine();
  } 
  else
  {
    line[counter] = c;
    counter++;
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println("Hello there general Kenobi");

  init_system_control_pins();
  init_system_timer();
  enable_system_timer();

  stepper.speed = 0;
  stepper.n_tick = 160000;

}

void loop() 
{

    while(Serial.available())
    {
      char c = Serial.read();
      processIncomingChar(c, line, char_counter);
    }
}
