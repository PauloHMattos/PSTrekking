#include "PID.h"
#include <Arduino.h>

PID::PID(float kp, float ki, float kd) : m_Kp(kp), m_Ki(ki), m_Kd(kd), m_IntegrativeSum(0)
{
  
}

float PID::run(float error)
{
  unsigned long deltaTime = millis() - m_LastRunTime;
  float dError = (error - m_LastError) / deltaTime;
  m_IntegrativeSum += error * m_Ki * deltaTime;

    
  m_LastError = error;
  m_LastRunTime = millis();

  return (error * m_Kp) + m_IntegrativeSum + (dError  * m_Kd);
}

