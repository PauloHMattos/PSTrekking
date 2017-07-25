#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(unsigned char address, RoboClaw roboClaw, float wheelsRadius, float wheelsDistanceFromRotationAxis, float gearRate, unsigned int pulsesPerRotation, unsigned int maxPPS) : 
  m_Address(address),
  m_RoboClaw(roboClaw),
  m_WheelsRadius(wheelsRadius),
  m_WheelsDistanceFromRotationAxis(wheelsDistanceFromRotationAxis),
  m_GearRate(gearRate),
  m_PulsesPerRotation(pulsesPerRotation),
  m_MaxPPS(maxPPS)
{
  
}

void MotorController::stop()
{
  move(0, 0);
}

void MotorController::move(float linearVelocity, float angularVelocity)
{
  float leftRPS = (linearVelocity + angularVelocity * m_WheelsDistanceFromRotationAxis) / (2 * PI * m_WheelsRadius);
  float rightRPS = (linearVelocity - angularVelocity * m_WheelsDistanceFromRotationAxis) / (2 * PI * m_WheelsRadius);

  leftRPS /= m_GearRate;
  rightRPS /= m_GearRate;
  
  float leftPps = leftRPS * m_PulsesPerRotation;
  float rightPps = rightRPS * m_PulsesPerRotation;

  m_RoboClaw.ForwardBackwardM1(m_Address, mapPWM(leftPps));
  m_RoboClaw.ForwardBackwardM2(m_Address, mapPWM(rightPps));
}

unsigned int MotorController::getEncoderLeft() const
{
  unsigned int enc = m_RoboClaw.ReadEncM1(m_Address, &m_Status, &m_Valid);
  m_RoboClaw.SetEncM1(m_Address, 0);
  return enc;
}

unsigned int MotorController::getEncoderRight() const
{
  unsigned int enc = m_RoboClaw.ReadEncM2(m_Address, &m_Status, &m_Valid);
  m_RoboClaw.SetEncM2(m_Address, 0);
  return enc;
}

unsigned char MotorController::mapPWM(float pps)
{
  unsigned char pwm = 0;
  float speed = pps / m_MaxPPS;
  pwm = 64 * (1 + speed);
  pwm = max(min(128, pwm), 0);
  return pwm;
}
