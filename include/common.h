#pragma once

//
// [ room protocol (message format) ]
//
// DDDDD ==> 5 decimal-digits.
// IIIWW ==> id (3 decimal-digits) * 100 + word (2 decimal-digits)
// id ==> 100~ : objects
// id ==> 200~ : agents (controller)
// id ==> 900~ : groups
// words ==> 1 ~ 99 ==> see 'words.h' for the details

// member identity
// objects
#define ID_GAS           (10100)
#define ID_TRUNK         (10200)
#define ID_DRUM          (10300)
#define ID_REEL          (10400)
#define ID_FLOAT         (10500)
// speakers
#define ID_SPEAK_A       (10600)
#define ID_SPEAK_B       (10700)
#define ID_SPEAK_C       (10800)
#define ID_SPEAK_D       (10900)
#define ID_SPEAK_E       (11000)
#define ID_SPEAK_F       (11100)
// (special agent)
#define ID_MONITOR       (20100)
// (groups)
#define ID_EVERYONE      (90100)
#define ID_SPEAKERS      (90200)
// (choice)
#define IDENTITY         ID_MONITOR

#define NUM_OF_MEMBERS 12
int memberList[NUM_OF_MEMBERS] = {
  ID_GAS, // 1
  ID_TRUNK, // 2
  ID_DRUM, // 3
  ID_REEL, // 4
  ID_FLOAT, // 5
  ID_SPEAK_A, // 6
  ID_SPEAK_B, // 7
  ID_SPEAK_C, // 8
  ID_SPEAK_D, // 9
  ID_SPEAK_E, // 10
  ID_SPEAK_F, // 11
  ID_MONITOR // 12
};

//
#define LONELY_TO_DIE    (30000)

//
#include <Arduino.h>

//
#include <painlessMesh.h>
extern painlessMesh mesh;

// firmata connectivity
#define FIRMATA_ON          (0xF13A0001)
#define FIRMATA_OFF         (0xF13A0002)
#define FIRMATA_USE         FIRMATA_OFF
#if (IDENTITY == ID_KEYBED)
#undef FIRMATA_USE
#define FIRMATA_USE         FIRMATA_ON
#endif

//NOTE: disabling AP beacon for speaker accompanied devices!
#define NODE_TYPE_AP_STA    (0x40DE0001)
#define NODE_TYPE_STA_ONLY  (0x40DE0002)
//by-default : STA_ONLY
#define NODE_TYPE           NODE_TYPE_STA_ONLY
//guys w/o speakers : AP_STA
#if (IDENTITY == ID_GAS || IDENTITY == ID_DRUM || IDENTITY == ID_REEL || IDENTITY == ID_FLOAT || IDENTITY == ID_MONITOR)
#undef NODE_TYPE
#define NODE_TYPE           NODE_TYPE_AP_STA
#endif

// board
#define BOARD_NODEMCU_ESP12E (0xBD00 + 1)
#define BOARD_NODEMCU_ESP12N (0xBD00 + 2)
#define BOARD_NODEMCU_ESP32  (0xBD00 + 3)
//(choice)
#define BOARD_SELECT BOARD_NODEMCU_ESP12E

// mesh
#define MESH_SSID "li_li_li_li_li_li"
#define MESH_PASSWORD "11*1111/111"
#define MESH_PORT 5555
#define MESH_CHANNEL 5
// #define MESH_ANCHOR

//
// LED status indication
//   operation modes
//     0 - booted. and running. no connection. scanning.
//     1 - + connected.
//   notifying patterns
//     0 - steady on
//     1 - slow blinking (syncronized)
//
#if (BOARD_SELECT == BOARD_NODEMCU_ESP12E)
#define LED_PIN 2 // nodemcuv2
#elif (BOARD_SELECT == BOARD_NODEMCU_ESP32)
#define LED_PIN 13 // featheresp32
#endif
#define LED_PERIOD (1111)
#define LED_ONTIME (0) //(1)

// event handlers fo connection-related events
extern void gotMessageCallback(uint32_t from, String & msg); // REQUIRED
extern void gotChangedConnectionCallback();

// the system scheduler
extern Scheduler runner;

#include "words.h"
