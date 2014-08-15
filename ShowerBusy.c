// Set this high so 1st loop will work
int showerBusy = HIGH;
int pinVal = LOW;
int pinNumber = D7;

void setup() {
    Spark.variable("showerbusy", &showerBusy, INT);
    pinMode(pinNumber, INPUT_PULLDOWN);
    RGB.control(true);
}

void reConnect() {
    // Check if not connected and re-connect
    if (!Spark.connected()){
        Spark.connect();
        while(!Spark.connected()){
            delay(300);
        }
    }
}

void loop() {
    delay(500);
    pinVal = digitalRead(pinNumber);
    if (pinVal == HIGH) {
        if (showerBusy == LOW) {
            showerBusy = HIGH;
            RGB.color(255, 0, 0);
            reConnect();
            Spark.publish("shower", "busy", 60, PRIVATE);
        }
    } else {
        if (showerBusy == HIGH) {
            showerBusy = LOW;
            RGB.color(0, 255, 0);
            reConnect();
            Spark.publish("shower", "free", 60, PRIVATE);
        }
    }
    reConnect();
}
