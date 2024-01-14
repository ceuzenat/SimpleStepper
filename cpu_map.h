#ifndef cpu_map_h
#define cpu_map_h

#ifdef CPU_MAP_ATMEGA328P // (Arduino Uno)

  // Define serial port pins and interrupt vectors.
  #define SERIAL_RX     USART_RX_vect
  #define SERIAL_UDRE   USART_UDRE_vect

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
  #define STEPPER_PORT    DDRD
  #define STEPPER_CONTROL PORTD
  #define X_STEP          ( 1 << 2 )  // Uno Digital Pin 2
  #define X_DIR           ( 1 << 3 )  // Uno Digital Pin 3
  #define STEPPER_MASK    ( 1 << 2 ) | ( 1 << 3 ) // All step bits

  // Define stepper driver enable/disable output pin.
/*  #define ENABLE_PORT     DDRB
  #define ENABLE_CONTROL  PORTB
  #define ENABLE          0  // Uno Digital Pin 8
  #define ENABLE_MASK     (1<<ENABLE)*/

#endif

#endif