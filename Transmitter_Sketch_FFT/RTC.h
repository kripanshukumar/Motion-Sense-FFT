//=======================================================================================//

time_t cvt_date(char const *date, char const *time)
{
  char s_month[5];
  int year;
  tmElements_t t;
  static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

  sscanf(date, "%s %hhd %d", s_month, &t.Day, &year);
  sscanf(time, "%2hhd %*c %2hhd %*c %2hhd", &t.Hour, &t.Minute, &t.Second);

  // Find where is s_month in month_names. Deduce month value.
  t.Month = (strstr(month_names, s_month) - month_names) / 3 + 1;

  // year can be given as '2010' or '10'. It is converted to years since 1970
  if (year > 99) t.Year = year - 1970;
  else t.Year = year + 30;

  //week = tm.Wday;

  return makeTime(t);
}

//=======================================================================================//

void initRTC() {
  rtc.begin();
  rtc.clearAll();
  setTime(cvt_date(__DATE__, __TIME__));
  //dateTime = {2016, 6, 3, 1, 15, 30, 40};
  dateTime = {year(), weekday(), month(), day(), hour(), minute(), second()};
  rtc.setDateTime(dateTime);
}

//=======================================================================================//
