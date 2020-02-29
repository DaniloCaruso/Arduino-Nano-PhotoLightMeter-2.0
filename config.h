

#define PlusButtonPin           2                      // Plus button pin
#define MinusButtonPin          3                      // Minus button pin
#define ModeButtonPin           4                      // Mode button pin

#define TFT_SCLK_SCK            5
#define TFT_MOSI_SDA            6  
#define TFT_RST_RES             7
#define TFT_DC_RS               8
#define TFT_CS_CS               9

#define MeteringModeButtonPin   10                     // Metering Mode (Ambient / Flash)
#define MenuButtonPin           11                     // ISO button pin
#define MeteringButtonPin       12                     // Metering button pin

//#define PowerButtonPin          13


#define MaxISOIndex             57
#define MaxApertureIndex        70
#define MaxTimeIndex            80
#define MaxNDIndex              13
#define MaxFlashMeteringTime    5000     

// EEPROM for memory recording
#define ISOIndexAddr            1
#define apertureIndexAddr       2
#define modeIndexAddr           3
#define T_expIndexAddr          4
#define meteringModeAddr        5
#define ndIndexAddr             6

#define defaultModeIndex        0
#define defaultISOIndex         11
#define defaultApertureIndex    12
#define defaultT_expIndex       19

#define batteryInterval         10000

#define DOME_K                  2.17 // Multiplier when using a white translucid Dome covering the lightmeter
#define EV_LUX_K                2.5
#define ISO_K                   100

// Application State Variables

uint8_t ISOIndex; 
uint8_t apertureIndex;
uint8_t T_expIndex;
uint8_t modeIndex;  
uint8_t meteringMode;
uint8_t ndIndex;

float   lux;
boolean Overflow = 0;                   // Sensor got Saturated and Display "Overflow"
float   ISOND;
boolean ISOmode = 0;
boolean NDmode = 0;

boolean PlusButtonState;                // "+" button state
boolean MinusButtonState;               // "-" button state
boolean MeteringButtonState;            // Metering button state
boolean ModeButtonState;                // Mode button state
boolean MenuButtonState;                // ISO button state
boolean MeteringModeButtonState;        // Metering mode button state (Ambient / Flash)

boolean ISOMenu = false;
boolean NDMenu = false;
boolean mainScreen = false;

int battVolts;
double lastBatteryTime = 0;

