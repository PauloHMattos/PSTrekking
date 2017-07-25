#ifndef PID_H
#define PID_H

class PID
{
public:
 PID(float kp, float ki, float kd);
 float run(float error);

private:
  float m_Kp, m_Ki, m_Kd;
  float m_IntegrativeSum;

  float m_LastError;
  unsigned long m_LastRunTime;
};

#endif //PID_H
