void writeLux( Adafruit_ST7735 d, int luxValue ) {
  String text = "LX: " + String(luxValue);
  d.setCursor(3, 3);
  d.setTextColor(ST77XX_WHITE);
  d.setTextSize(1);
  d.print(text);
}

void writeEV( Adafruit_ST7735 d, int ev ) {
  String text = "EV: " + String(ev);
  int positionX = (d.width() - 9 ) - (text.length() * 5);
  d.setCursor(positionX, 3);
  d.setTextColor(ST77XX_WHITE);
  d.setTextSize(1);
  d.print(text);
}

void drawHeader( Adafruit_ST7735 d , int luxValue, int ev) {
  writeLux(d, luxValue);
  writeEV(d, ev);
  int16_t height = 7+2+5;
  d.drawFastHLine(0, height, d.width(), ST77XX_WHITE);
}

void writeCalculatedInfo( Adafruit_ST7735 d ) {

  uint16_t luxValue = getLuxFromSensor();
  String luxStr = "LX: " + formatStringForTFT(String(luxValue), 10);

  d.setCursor(3, 3);
  d.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  d.setTextSize(1);
  d.print(luxStr);

  uint16_t baseEv = luxToEvConversion(luxValue);
  String evBaseStr = "Ev Base: " + formatStringForTFT(String(baseEv), 10);
  d.setCursor(3, 12);
  d.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  d.setTextSize(1);
  d.print(evBaseStr);

  String isoSetStr = formatStringForTFT("ISO Set: 200", 10);
  d.setCursor(3, 22);
  d.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  d.setTextSize(1);
  d.print(isoSetStr);

  uint16_t ISOEv = evaluateISOEv(300, baseEv);
  String evIsoStr = "Ev 300: " + formatStringForTFT(String(ISOEv), 10);
  d.setCursor(3, 33);
  d.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  d.setTextSize(1);
  d.print(evIsoStr);

  float aperture = evaluateAperture(0.00025, ISOEv);
  String apertureStr = "f (t->1/4000 ISO->300): " + formatStringForTFT(String(aperture), 10);
  d.setCursor(3, 44);
  d.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  d.setTextSize(1);
  d.print(apertureStr);

  float timeExp = evaluateExpTime(aperture, ISOEv);
  String expTimeStr = formatStringForTFT("t (f=" + String(aperture) + " ISO=300): 1/" + String(timeExp), 50);
  d.setCursor(3, 77);
  d.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  d.setTextSize(1);
  d.print(expTimeStr);

  float ISO = evaluateISO(aperture, timeExp, luxValue);
  String ISOStr = formatStringForTFT("ISO f ->" + String(aperture) + " t->" +String(timeExp)+ ": " + String(ISO), 50);
  d.setCursor(3, 110);
  d.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  d.setTextSize(1);
  d.print(ISOStr);

}