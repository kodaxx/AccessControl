//What kind of RFID Reader do we have here?
#ifdef OLD
void readTag() {
  char tagBytes[6];

  //  while (!Serial.available()) { delay(10); }

  if (Serial.readBytes(tagBytes, 5) == 5)
  {
    uint8_t checksum = 0;
    uint32_t cardId = 0;

    tagBytes[6] = 0;

    //    log("Raw Tag:");
    for (int i = 0; i < 4; i++)
    {
      checksum ^= tagBytes[i];
      cardId = cardId << 8 | tagBytes[i];
      //     Serial.println(tagBytes[i], HEX);
    }

    if (checksum == tagBytes[4])
    {
      log("[AUTH] Tag Number:" + String(cardId));
      flushSerial();
      authCard(cardId);
      lastReadSuccess = millis();
    } else {
      flushSerial();
      log("[AUTH] incomplete or corrupted RFID read, sorry. ");
    }
  }
}
#endif

#ifdef RF125PS
void readTag() {
  char tagBytes[6];

  //  while (!Serial.available()) { delay(10); }

  if (Serial.readBytes(tagBytes, 5) == 5)
  {
    uint8_t checksum = 0;
    uint32_t cardId = 0;

    tagBytes[6] = 0;

    //    log("Raw Tag:");
    for (int i = 0; i < 4; i++)
    {
      checksum ^= tagBytes[i];
      cardId = cardId << 8 | tagBytes[i];
      //     Serial.println(tagBytes[i], HEX);
    }

    if (checksum == tagBytes[4])
    {
      log("[AUTH] Tag Number:" + String(cardId));
      flushSerial();
      authCard(cardId);
      lastReadSuccess = millis();
    } else {
      flushSerial();
      log("[AUTH] incomplete or corrupted RFID read, sorry. ");
    }
  }
}
#endif
