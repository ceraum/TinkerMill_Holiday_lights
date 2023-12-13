void callback(char* topic, byte* message, unsigned int length) {

  // Releases hold at start
  start_animation = true;

  Serial.println("Callback");
  Serial.println(topic);
  //Serial.println(message);
  Serial.println(length);

    String messageTemp;
    for (int i = 0; i < length; i++) {
        messageTemp += (char)message[i];
    }

    Serial.println(messageTemp);

    // Assuming message is in format "R,G,B"
    int rIndex = messageTemp.indexOf(',');
    int gIndex = messageTemp.indexOf(',', rIndex + 1);

    int r = messageTemp.substring(0, rIndex).toInt();
    int g = messageTemp.substring(rIndex + 1, gIndex).toInt();
    int b = messageTemp.substring(gIndex + 1).toInt();

    if (String(topic) == winName + "/strip1") {
        for (int i = 0; i < NUM_LEDS_1; i++) {
            leds_1[i] = CRGB(r, g, b);
        }
        // FastLED.show();
    } else if (String(topic) == winName + "/strip2") {
        for (int i = 0; i < NUM_LEDS_2; i++) {
            leds_2[i] = CRGB(r, g, b);
        }
        // FastLED.show();
    }
}

void reconnect() {
  Serial.println("Reconnecting");
    while (!client.connected()) {
        if (client.connect(winName.c_str())) {
            client.subscribe((winName + "/strip1").c_str());
            client.subscribe((winName + "/strip2").c_str());
        }
        delay(5000);
    }
}

