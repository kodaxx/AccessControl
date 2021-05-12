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
      handleCard(cardId);
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
  char startChar = '.';
  char endChar = '.';
  char cardBytes[10];
  char *endptr;
  uint32_t cardId;
  

  if (Serial.read() == startChar) {
    log("[AUTH] Card start byte found.");
    // STX Byte found, dump the rest out until ETX byte. Yes this is blocking but we need to dedicate to reading now.
    Serial.readBytesUntil(endChar, cardBytes, 11);
    flushSerial();
    String cardString = String(cardBytes);

    log("[AUTH] Card String:" + cardString);
    cardString = cardString.substring(4,10);
    cardId = strtol(cardString.c_str(), &endptr, 16);
    log("[AUTH] Card ID:" + String(cardId));
    handleCard(cardId);
  } else {
    flushSerial();
    log("[AUTH] incomplete or corrupted RFID read, sorry. ");
  }
}

#endif

#ifdef RC522
void readTag() {
  char startChar = '.';
  char endChar = '.';
  char cardBytes[10];
  char *endptr;
  uint32_t cardId;
  

  if (Serial.read() == startChar) {
    log("[AUTH] Card start byte found.");
    // STX Byte found, dump the rest out until ETX byte. Yes this is blocking but we need to dedicate to reading now.
    Serial.readBytesUntil(endChar, cardBytes, 11);
    flushSerial();
    String cardString = String(cardBytes);

    log("[AUTH] Card String:" + cardString);
    cardString = cardString.substring(4,10);
    cardId = strtol(cardString.c_str(), &endptr, 16);
    log("[AUTH] Card ID:" + String(cardId));
    handleCard(cardId);
  } else {
    flushSerial();
    log("[AUTH] incomplete or corrupted RFID read, sorry. ");
  }
}

#endif

// Serial clearing function.

void flushSerial () {
  int flushCount = 0;
  while (  Serial.available() ) {
    Serial.read();  // flush any remaining bytes.
    flushCount++;
    // Serial.println("flushed a byte");
  }
  if (flushCount > 0) {
    log("[DEBUG] Flushed " + String(flushCount) + " bytes.");
    flushCount = 0;
  }
}
