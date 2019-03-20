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

#define ARM_SERVO 0
#define ARM_DOWN 1500
#define ARM_MIDDLE 1000
#define ARM_UP 100

#define CLAW_SERVO 1
#define CLAW_OPEN 850
#define CLAW_CLOSE 0

#define NORMAL_SLOW_SERVO_SPEED  10 
#define NORMAL_SERVO_SPEED       50

void start();
void forward(float inches, int speed);
void backward(float inches, int speed);
void spin(float degrees, int speed);
void left(float degrees, int speed);
void right(float degrees, int speed);
void press_a();
void grab_and_dump();
void servo_slowly(int port, int desired_position, int speed);
void servo(int port, int desired_position);

// TODO:  Do the TODOs below.  Then talk with the team (including Johnny) to decide whether to
//        bring poms to the bin or to bring the bin to the poms.

int main(){
    
    start();
    right(23,80);
    msleep(1000);
    forward(31,80);
    msleep(1000);
    left(90,80);
    msleep(1000);
    
    servo(ARM_SERVO, ARM_DOWN);
    forward(15,80);
    msleep(1000);
    
    servo(CLAW_SERVO, CLAW_CLOSE);
    
     
    return 0;  
}

void start()
{
    //wait_for_light(0);
    shut_down_in(119);
    set_servo_position(ARM_SERVO, ARM_UP);
    set_servo_position(CLAW_SERVO, CLAW_OPEN);
    enable_servos();
}


void david_challenge() {
    // TODO: Remove this function.
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

//This function will move a servo SLOWLY to its desired position.
void servo(int port, int desired_position)
{
    servo_slowly(port, desired_position, NORMAL_SERVO_SPEED);
}

// Speed is servo units to move each time through the loop.
void servo_slowly(int port, int desired_position, int speed)
{
    int position;
    int step = speed;

    enable_servo(port);

    if (get_servo_position(port) > desired_position)
    {
        while (TRUE)
        {
            position = get_servo_position(port);
            if (position <= desired_position + step)
            {
                break;
            }
            set_servo_position(port, position - step);
            msleep (50);
        }

    } else
    {
        while (TRUE)
        {
            position = get_servo_position(port);
            if (position >= desired_position - step)
            {
                break;
            }
            set_servo_position(port, position + step);
            msleep (50);
        }
    }
    msleep(50);
    set_servo_position(port, desired_position);
    msleep(50);
}
