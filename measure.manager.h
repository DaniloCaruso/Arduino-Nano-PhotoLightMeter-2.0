
uint16_t getLuxFromSensor() {

    
   uint16_t lux = lightSensor.readLightLevel();

    if (lux >= 65534) {
      Overflow = 1;
      lux = 65535;
    } else {
      Overflow = 0;
    }
 

    return (uint16_t) (lux * DOME_K);            
}

