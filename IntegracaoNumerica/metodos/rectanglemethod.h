#ifndef RECTANGLEMETHOD_H
#define RECTANGLEMETHOD_H

#include "integrationmethod.h"

class RectangleMethod: public IntegrationMethod
{
public:
  RectangleMethod();

  QString MethodName();
  void Draw(QPainter *painter);
  double Integrate();

  QVector<double> y;
};

#endif // RECTANGLEMETHOD_H
