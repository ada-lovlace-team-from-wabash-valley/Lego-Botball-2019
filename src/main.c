#include <kipr/botball.h>

#define MILLISECONDS_PER_INCH 142.9
#define MILLISECONDS_PER_DEGREE 5.0

#define LEFT_MOTOR 3
#define RIGHT_MOTOR 0

#define TRUE 1
#define FALSE 0
#define DEBUG FALSE
#define PRESS_A_MILLISECONDS 200
#define PRESS_A_HANDS_OFF 500

void forward(float inches, int speed);
void backward(float inches, int speed);
void spin(float degrees, int speed);
void left(float degrees, int speed);
void right(float degrees, int speed);
void press_a();
void grab_and_dump();

int main()
{
    //set_servo_position(2, 605);
    //enable_servo(2);
    grab_and_dump();

    printf("Doggo\n");



    return 0;
}

void grab_and_dump() {
    //1/2 1 open grabber 2 go forward 3 close 4 go forward
    enable_servo(0);
    enable_servo(1);
    set_servo_position(0,1500);
    msleep(1000);
    set_servo_position(1,820);
    msleep(1000);
    forward(2,100);
    msleep(1000);
    set_servo_position(1,0);
    msleep(1000);
    set_servo_position(0,372);
    msleep(1000);
    forward(3,100);
    msleep(1000);
    set_servo_position(0,974);
    msleep(1000);
    set_servo_position(1,431);
    msleep(1000);
}

void david_challenge() {
    forward(33, 100);
    msleep(1000);
    set_servo_position(2, 0);
    msleep(1000);
    spin(80, -50);
    msleep(1000);
    forward(22, 100);
    spin(90, 50);
    msleep(1000);
    set_servo_position(2, 605);
}

void forward(float inches, int speed) {
    motor(LEFT_MOTOR, speed);
    motor(RIGHT_MOTOR, speed);
    msleep((int) fabs(inches * MILLISECONDS_PER_INCH * 100.0 / speed));
    ao();
    press_a();
}

void backward(float inches, int speed) {
    forward(inches, -speed);
}

void spin(float degrees, int speed) {
    motor(LEFT_MOTOR, speed);
    motor(RIGHT_MOTOR, -speed);
    msleep((int) fabs(degrees * MILLISECONDS_PER_DEGREE * 100.0 / speed));
    ao();
    press_a();
}

void right(float degrees, int speed) {
    spin(degrees, speed);
}

void left(float degrees, int speed) {
    spin(degrees, -speed);
}

void press_a() {
    if (! DEBUG) {
        msleep(PRESS_A_MILLISECONDS);
        return;
    }

    printf("Press A to continue:\n");
    while (TRUE) {
        if (a_button()) {
            break;
        }
    }
    printf("Pressed!  Remove your hand!\n");
    while (TRUE) {
        if (! a_button()) {
            break;
        }
    }
    msleep(PRESS_A_HANDS_OFF);
}
