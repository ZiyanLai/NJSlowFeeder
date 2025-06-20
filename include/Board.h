#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include <Button.h>
#include "LoadCell.h"
#include "Motor.h"

enum ButtonStatus {
    BUTTON_IDLE = 0,
    BUTTON_HOLD = 1,
    BUTTON_CLICK = 2,
    BUTTON_DOUBLE_CLICK = 3,
};

class Board {
public:
    Board(float calibrationFactor);
    void setup();
    void updateButtons();
    bool shouldSleep();  
    void enterDeepSleep();
    
    Motor& getMotor();
    LoadCell& getLoadCell();
    Button& getButtonUp();
    Button& getButtonDown();

    void handleButtonAction();
    void processFeedingCycle();

private:
    // GPIO Pins
    static const int IN1MotorPin = 44; //change to 44 if motor runs in reverse
    static const int IN2MotorPin = 7; //change to 7 if motor runs in reverse
    static const int buttonUpPin = 5; //labeled as D4 on the silkscreen for xiao
    static const int buttonDownPin = 6; //labeled as D5 on the slikscreen for xiao
    static const int HX_DOUT = 9; //hx711, labeled as D10 on the silkscreen for xiao
    static const int HX_CLK = 8; //hx711, labeled as D9 on the silkscreen for xiao
    static const gpio_num_t HX711CLK = GPIO_NUM_8;
    static const gpio_num_t WAKEUP_GPIO = GPIO_NUM_5;

    // Components
    Motor motor;
    LoadCell loadCell;
    Button buttonUp;
    Button buttonDown;

    // Timing tracking
    unsigned long lastMotorActiveTime;
    unsigned long delayStartTime;
	unsigned long lastClickTimeUp;
    unsigned long lastClickTimeDown; 
    const unsigned long doubleClickInterval = 500;
    const unsigned long delayAfterClick = 1000;
    bool waitingAfterClick;

    // Config
    const int sleepTimeoutTime = 30000;

    // Internal callbacks
    static void onRelease(Button& b);
    static void onHold(Button& b);

    void playStartupChime();
    void playDeepSleepChime();
    void printWakeupReason();
};

#endif // BOARD_H
