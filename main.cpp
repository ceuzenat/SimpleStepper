#include <stepam.h>

static char line[LINE_BUFFER_SIZE];
uint8_t char_counter = 0;

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
}

void loop() 
{
    while(Serial.available())
    {
      char c = Serial.read();
      processIncomingChar(c, line, char_counter);
    }
}
