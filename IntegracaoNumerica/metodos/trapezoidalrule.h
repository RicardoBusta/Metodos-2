#ifndef TRAPEZOIDALRULE_H
#define TRAPEZOIDALRULE_H

#include "integrationmethod.h"

class TrapezoidalRule: public IntegrationMethod
{
public:
  TrapezoidalRule();

  QString MethodName();
  void Draw();
  int Integrate();
};

#endif // TRAPEZOIDALRULE_H
