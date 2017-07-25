#include "Trekking.h"
#include <Arduino.h>

Trekking::Trekking(MotorController motorController, Position initialPosition) : m_MotorController(motorController), m_CurrentPosition(initialPosition)
{
}


void Trekking::update()
{
  float radius = m_MotorController.getWheelsRadius();
  float distanceFromAxis = m_MotorController.getWheelsDistanceFromRotationAxis();

  float deltaEncoderLeft = 2 * PI * radius * m_MotorController.getEncoderLeft() / m_MotorController.getPulsesPerRotation();
  float deltaEncoderRight = 2 * PI * radius *  m_MotorController.getEncoderRight() / m_MotorController.getPulsesPerRotation();
  float deltaEncoder = deltaEncoderLeft + deltaEncoderRight;

  float heading = m_CurrentPosition.getHeading();
  float newX = m_CurrentPosition.getX() + (deltaEncoder * cos(heading));
  float newY = m_CurrentPosition.getY() + (deltaEncoder * sin(heading));
  float newHeading = m_CurrentPosition.getHeading() + ((deltaEncoderRight - deltaEncoderLeft) / distanceFromAxis);

  m_CurrentPosition.setX(newX);
  m_CurrentPosition.setY(newY);
  m_CurrentPosition.setHeading(newHeading);
}

