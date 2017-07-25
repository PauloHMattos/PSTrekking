#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "RoboClaw.h"

class MotorController
{
public:
  MotorController(unsigned char address, RoboClaw roboClaw, float wheelsRadius, float wheelsDistanceFromRotationAxis, float gearRate, unsigned int pulsesPerRotation, unsigned int maxPPS);
  
  void stop();
  void move(float linearVelocity, float angularVelocity);

  float getWheelsRadius() const { return m_WheelsRadius; }
  float getWheelsDistanceFromRotationAxis() const { return m_WheelsDistanceFromRotationAxis; }
  
  unsigned int getEncoderLeft() const;
  unsigned int getEncoderRight() const;
  unsigned int getPulsesPerRotation() const { return m_PulsesPerRotation; }
  
private:
  // --------------[RoboClaw]--------------
  unsigned char m_Address;
  RoboClaw m_RoboClaw;

  // Variáveis de controle. Indica se foi possivel ler os valores no controlador, e se não, porque não.
  unsigned char m_Status;
  bool m_Valid;
  // --------------------------------------

  // Raio das rodas (em metros).
  float m_WheelsRadius;
  // Distância do eixo das rordas, até o eixo de rotação (em metros).
  float m_WheelsDistanceFromRotationAxis;
  // Redução do motor (1:70 => 1/70; 50:1 => 50/1; etc).
  float m_GearRate;
  // Quantidade de ticks por revolução do motor/encoder.
  unsigned int m_PulsesPerRotation;
  unsigned int m_MaxPPS;

  unsigned char mapPWM(float pps);
};

#endif //MOTOR_CONTROLLER_H
