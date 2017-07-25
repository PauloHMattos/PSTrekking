#include "RoboClaw.h"
#include "Position.h"
#include "Trekking.h"
#include "MotorController.h"
#include "PID.h"
#include "Pins.h"
#include "Ultrasonic.h"

SoftwareSerial roboClawSerial(8, 9);
RoboClaw roboClaw(&roboClawSerial, 1000);
MotorController motorController(0x80, roboClaw, 0.05, 0.1, 1/70, 64, 12000);
Trekking trekking(motorController, Position(3, 3, 0));
PID pid(1, 1, 1);

float sensorWeights[] = {-15, 0, 15};
Ultrasonic ultrasonicSensors[] = { Ultrasonic(2, 3, 10000), Ultrasonic(4, 5, 10000), Ultrasonic(6, 7, 10000) };

unsigned char waypointIndex = 0;
Position waypoints[] = {Position(40, 20), Position(30, 2), Position(6, 18)};
bool isRunning;

void setup()
{
}

void loop()
{
  if(!isRunning)
    return;
    
  trekking.update();
  auto currentTarget = waypoints[waypointIndex];
  auto currentPosition = trekking.getCurrentPosition();

  // Se a distância pro waypoint for maior que 1m, ajusta com o encoder
  if(currentPosition.distance(currentTarget) > 1)
  {
    float heading = currentPosition.getHeading();
    float desiredHeading = atan((currentTarget.getY() - currentPosition.getY()) / (currentTarget.getX() - currentPosition.getX()));
    
    float error = desiredHeading - heading;
    // Como estamos lidando com angulos, usa esse truque pra garantir que os valores sempre estejam entre -PI e PI
    error = atan2(sin(error), cos(error));
  
    float angularVelocity = pid.run(error);
    motorController.move(1, angularVelocity);
  }
  // Se a distância pro waypoint for entre 1m e 5cm, busca com o ultrassom e liga a arma
  else if(currentPosition.distance(currentTarget) > 0.05)
  {
    digitalWrite(WEAPON, HIGH);
    float error = 0;
    int cnt;
    for(int i = 0; i < 3; i++)
    {
      if(ultrasonicSensors[i].Ranging(1) < 150)
      {
        error += sensorWeights[i];
        cnt++;
      }
    }
    error /= cnt;
    float angularVelocity = pid.run(error);
    motorController.move(0.5, angularVelocity);
  }
  else
  {
    // Se tá a menos que 5 cm, a arma já deve ter acertado, porque ela tá mais a frente do ponto de origem do robô
    digitalWrite(WEAPON, LOW);
    motorController.stop();
    
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
    
    if(++waypointIndex > 2)
    {
      waypointIndex = 0;
      isRunning = false;
    }
  }
}
