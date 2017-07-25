#ifndef POSITION_H
#define POSITION_H

#include <Arduino.h>

class Position
{
public:
  Position(float x, float y) : Position(x, y, 0) {}
  Position(float x, float y, float heading);
  
  float getX() const { return m_X; }
  float getY() const { return m_Y; }
  float getHeading() const { return m_Heading; }

  void setX(float value) { m_X = value; }
  void setY(float value) { m_Y = value; }
  void setHeading(float value) { m_Heading = value; }

  float distance(const Position pos)
  {
    return sqrt(pow(m_X - pos.m_X, 2) + pow(m_Y - pos.m_Y, 2));
  }
private:
  float m_X, m_Y, m_Heading;
};

#endif //POSITION_H


