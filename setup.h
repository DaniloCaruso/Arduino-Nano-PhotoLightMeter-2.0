
void initFromEPROM() {
    
    ISOIndex      = EEPROM.read(ISOIndexAddr);
    apertureIndex = EEPROM.read(apertureIndexAddr);
    T_expIndex    = EEPROM.read(T_expIndexAddr);
    modeIndex     = EEPROM.read(modeIndexAddr);
    meteringMode  = EEPROM.read(meteringModeAddr);
    ndIndex       = EEPROM.read(ndIndexAddr);
}

void setupButtonPin(){

    pinMode(PlusButtonPin,         INPUT_PULLUP);
    pinMode(MinusButtonPin,        INPUT_PULLUP);
    pinMode(MeteringButtonPin,     INPUT_PULLUP);
    pinMode(ModeButtonPin,         INPUT_PULLUP);
    pinMode(MenuButtonPin,         INPUT_PULLUP);
    pinMode(MeteringModeButtonPin, INPUT_PULLUP);
}

void readButtonsState() {

    PlusButtonState         = digitalRead(PlusButtonPin);
    MinusButtonState        = digitalRead(MinusButtonPin);
    MeteringButtonState     = digitalRead(MeteringButtonPin);
    ModeButtonState         = digitalRead(ModeButtonPin);
    MenuButtonState         = digitalRead(MenuButtonPin);
    MeteringModeButtonState = digitalRead(MeteringModeButtonPin);
}

Adafruit_ST7735 getDisplay() {

    return Adafruit_ST7735(TFT_CS_CS, TFT_DC_RS, TFT_MOSI_SDA, TFT_SCLK_SCK, TFT_RST_RES);
}

void initializeDisplay(Adafruit_ST7735 d) {

    
    d.initR(INITR_BLACKTAB);
    d.fillScreen(ST77XX_BLACK);
}

void initializeSensor() {


}

void initializeDefaults() {

    apertureIndex   = (apertureIndex > MaxApertureIndex) ? defaultApertureIndex : apertureIndex;
    ISOIndex        = (ISOIndex > MaxISOIndex)           ? defaultISOIndex      : ISOIndex;
    T_expIndex      = (T_expIndex > MaxTimeIndex)        ? defaultT_expIndex    : T_expIndex;
    modeIndex       = (modeIndex < 0 || modeIndex > 1)   ? 0                    : modeIndex;
    meteringMode    = (meteringMode > 1)                 ? 0                    : meteringMode;
    ndIndex         = (ndIndex > MaxNDIndex)             ? 0                    : ndIndex;
}

int getBandgap(void) {

    #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
        const long InternalReferenceVoltage = 1115L;
        ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (0 << MUX5) | (1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);
    #else
        const long InternalReferenceVoltage = 1056L;
        ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);
    #endif

    delay(50); // Let mux settle a little to get a more stable A/D conversion
    // Start a conversion
    ADCSRA |= _BV(ADSC);
    // Wait for it to complete
    while (((ADCSRA & (1 << ADSC)) != 0));
    // Scale the value
    int result = (((InternalReferenceVoltage * 1024L) / ADC) + 5L) / 10L; // calculates for straight line value
    return result;
}

void evaluateBattVolts() {
    
    battVolts = getBandgap();
}

void manageBattVolts() {

    if (millis() >= lastBatteryTime + batteryInterval) {
        lastBatteryTime = millis();
        evaluateBattVolts();
    }
}

