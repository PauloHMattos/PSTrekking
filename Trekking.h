#ifndef TREKKING_H
#define TREKKING_H

#include "MotorController.h"
#include "Position.h"

class Trekking
{
public:
  Trekking(const MotorController motorController, const Position initialPosition);
  void update();
  Position getCurrentPosition() const { return m_CurrentPosition; }

private:
  MotorController m_MotorController;
  Position m_CurrentPosition;
};

#endif //TREKKING_H
