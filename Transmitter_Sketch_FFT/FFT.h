void initFFT() {
  for (uint16_t i = 0; i < samples; i++) {
    vReal[i] = 0.0;
    vImag[i] = 0.0;
  }
}

void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
        break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
        break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
        break;
    }
    Serial.print(abscissa, 6);
    if (scaleType == SCL_FREQUENCY)
      Serial.print("Hz");
    Serial.print(" ");
    Serial.println(vData[i], 4);
  }
  Serial.println();
}

int findindex() {
  double maxY = 0;
  uint16_t IndexOfMaxY = 0;
  //If sampling_frequency = 2 * max_frequency in signal,
  //value would be stored at position samples/2
  for (uint16_t i = 1; i < (20 + 1); i++) {
    if ((vReal[i - 1] < vReal[i]) && (vReal[i] > vReal[i + 1])) {
      if (vReal[i] > maxY) {
        maxY = vReal[i];
        IndexOfMaxY = i;
      }
    }
  }
  return (IndexOfMaxY);
}

void computeFFT() {
  //Serial.println("Data:");
  //PrintVector(vReal, samples, SCL_TIME);
  FFT.DCRemoval(vReal, samples);
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
  //Serial.println("Weighed data:");
  //PrintVector(vReal, samples, SCL_TIME);
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  //Serial.println("Computed Real values:");
  //PrintVector(vReal, samples, SCL_INDEX);
  //Serial.println("Computed Imaginary values:");
  //PrintVector(vImag, samples, SCL_INDEX);
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
  //Serial.println("Computed magnitudes:");
  PrintVector(vReal, (samples >> 1), SCL_FREQUENCY);
  frequency = FFT.MajorPeak(vReal, samples, 32);
  int st = findindex();
  Serial.println();Serial.println(st);
  frequency = float(8 * (st))/32;
  payloadFrequency = frequency * 100;
  amplitude = vReal[st];
  payloadAmplitude = amplitude * 10000;
  lowerpayload[24] = payloadAmplitude%256;
  payloadAmplitude = payloadAmplitude/256;
  lowerpayload[25] = payloadAmplitude%256;
  payloadAmplitude = payloadAmplitude/256;
  lowerpayload[26] = payloadAmplitude%256;
  payloadAmplitude = payloadAmplitude/256;

  lowerpayload[27] = payloadFrequency%256;
  payloadFrequency = payloadFrequency/256;
  lowerpayload[28] = payloadFrequency%256;
  payloadFrequency = payloadFrequency/256;
  lowerpayload[29] = payloadFrequency%256;
  payloadFrequency = payloadFrequency/256;
  
  Serial.print("FFT result: ");
  Serial.print(frequency, 6);Serial.print(" Hz \t");
  Serial.println(amplitude,6);
}
