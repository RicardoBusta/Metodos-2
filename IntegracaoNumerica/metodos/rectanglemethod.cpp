#include "rectanglemethod.h"

RectangleMethod::RectangleMethod()
{
  AddParameter("Divisões",10,1,999);
  AddParameter("Teste Bool",true);
  AddParameter("Teste Float",0.5f);
  AddParameter("Teste Double",0.35);
}

QString RectangleMethod::MethodName()
{
  return "Método do Retângulo";
}

double RectangleMethod::Integrate()
{
  int d = GetParameter("Divisões").toInt();
  double inc = (b-a)/double(d);
  double start = a + inc/2;
  double result = 0;
  y.resize(d);
  for(int i=0;i<d;i++){
    float x = start + i*inc;
    y[i] = F(x);
    result += y[i]*inc;
  }
  qDebug() << result;
  return result;
}

void RectangleMethod::Draw(QPainter *painter)
{
  int d = y.count();
  double inc = (b-a)/double(d);
  for(int i=0;i<d;i++){
    QRectF r(a+i*inc,0,inc,y[i]);
    painter->drawRect(r);
  }
}
