#ifndef INTEGRATIONMETHOD_H
#define INTEGRATIONMETHOD_H

#include <QString>
#include <QVariant>
#include <QMap>
#include <QWidget>
#include <QDebug>
#include <QPainter>

class IntegrationParameter{
public:
  QString name;
  QVariant::Type type;
  QVariant defaultValue;
  QWidget *widget;
};

class MainWindow;

class IntegrationMethod: public QObject
{
  Q_OBJECT
public:
  IntegrationMethod(QObject *parent=nullptr);

  virtual QString MethodName()=0;
  virtual void Draw(QPainter *painter)=0;
  virtual double Integrate()=0;

  void AddParameter(QString name, QVariant defaultValue);

  QWidget *GenPage();

  QVariant GetParameter(QString name);

  MainWindow *w;

  double F(double x);

  double a;
  double b;
private:
  QMap<QString,IntegrationParameter*> parameters;

};

#endif // INTEGRATIONMETHOD_H
