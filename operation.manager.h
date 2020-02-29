float getISORatio( int iso ) {

    return (float) iso / ISO_K;
}

uint16_t luxToEvConversion(float lux) {

    float ev = log2f(lux / EV_LUX_K);
    return (uint16_t) ev;
}

uint16_t evaluateISOEv(int iso, uint16_t baseEv) {

    uint16_t evIso = baseEv + log2f( getISORatio(iso) );
    return evIso;
}

float evaluateExpTime(float aperture , uint16_t isoEv) {

    double expTime = powf(aperture, 2.0) / (pow(2.0, isoEv));
    return 1 / expTime;
}

float evaluateAperture(double expTime, uint16_t isoEv ) {

    float aperture = sqrtf(powf(2.0, isoEv) * expTime);
    return aperture;
}

float evaluateISO(float aperture, float expTime, float lux) {
    
    float iso = (powf(aperture, 2.0) * expTime) * (250 / lux);
    return iso;
}

