#ifndef stepam_h
#define stepam_h

// Grbl versioning system
#define STEPAM_VERSION "0.1h"
#define STEPAM_VERSION_BUILD "20240109"

// Define standard libraries used
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>


// Internal files
#include "config.h"
#include "cpu_map.h"
#include "serial.h"

#endif
