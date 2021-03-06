#define LED_MAX 4095
#define LED_LOW_PULSE 2000
#define LED_HIGH 2000
#define LED_OFF 0
#define LED_INTERVAL 200 // LED_HIGH ÷ 10 (segments

#define LED_STATE_READY 0
#define LED_STATE_PULSING 1

int led_state = LED_STATE_READY;
unsigned long led_timer = 0;
int led_current_brightness = 0;
int led_target_brightness = 0;
float easing = 0.2;


int brightness = 0;

int fade_amount = 100;    // how many points to fade the LED by
unsigned long last_led_timout = 0;

void led_setup() {
  Tlc.init();
}

void led_loop() {

  //////////////////////////////////////////////
  /*if (millis() - last_led_timout > 50) {
    // change the brightness for next time through the loop
    brightness += fade_amount;

    // reverse the direction of the fading at the ends of the fade
    if (brightness <= 0 || brightness >= (LED_MAX - fade_amount)) {
      fade_amount = -fade_amount ; 
    } 

    last_led_timout = millis();
    
    // Send the brightness values to the LED driver
    for (int i = 0; i <= 8; i++) {
      Tlc.set(i, int(brightness));
    }
  }*/
  
  //////////////////////////////////////////////
  if (led_state == LED_STATE_PULSING) {
    // we're going DOWN from current_brightness to target_brightness
    if (millis() - led_timer > 42){
      float dx = led_target_brightness - led_current_brightness;

      if(abs(dx) > 5) {
        led_current_brightness += dx * easing;
      }
      else {
        led_current_brightness = led_target_brightness;
        led_state = LED_STATE_READY;
      }

      led_timer = millis();
    }

    // Send the brightness values to the LED driver
    for (int i = 0; i <= 8; i++) {
      Tlc.set(i, int(led_current_brightness));
    }
  }

  // Apply the new brightness values
  Tlc.update();
}

void led_pulse_to(int n) {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.print("': led_pulse_to ");
  Serial.println(n);

  // set the initial animation brightness
  led_current_brightness = LED_MAX;
  led_target_brightness = LED_INTERVAL * n;
  led_state = LED_STATE_PULSING;
}

void led_low_pulse_to(int n) {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.print("': led_low_pulse_to ");
  Serial.println(n);

  // set the initial animation brightness
  led_current_brightness = LED_LOW_PULSE;
  led_target_brightness = LED_INTERVAL * n;
  led_state = LED_STATE_PULSING;
}




