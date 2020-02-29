
float log2f(float i) {
    return logf(i) / log(2);
}

String formatStringForTFT(String str, int maxChar) {
    
    if( str.length() <  maxChar) {
        while(str.length() <= maxChar)
        str += " ";
    }

    return str;
}