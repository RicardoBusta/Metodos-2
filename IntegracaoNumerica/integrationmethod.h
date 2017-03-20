#ifndef INTEGRATIONMETHOD_H
#define INTEGRATIONMETHOD_H

#include <QString>

class IntegrationMethod
{
public:
  IntegrationMethod();

  virtual QString MethodName();
  virtual void Draw()=0;
  virtual int Integrate()=0;
};

#endif // INTEGRATIONMETHOD_H
