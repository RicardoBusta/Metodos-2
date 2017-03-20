#include "integrationmethod.h"

#include <QWidget>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QDebug>

#include "mainwindow.h"

IntegrationMethod::IntegrationMethod(QObject *parent)
  :QObject(parent)
{

}

void IntegrationMethod::AddParameter(QString name, QVariant defaultValue)
{
  if(parameters.contains(name)){
    return;
  }
  IntegrationParameter *i = new IntegrationParameter;
  i->name = name;
  i->type = defaultValue.type();
  i->defaultValue = defaultValue;
  i->clamp = false;
  parameters.insert(name,i);
}

void IntegrationMethod::AddParameter(QString name, QVariant defaultValue, QVariant min, QVariant max)
{
  if(parameters.contains(name)){
    return;
  }
  IntegrationParameter *i = new IntegrationParameter;
  i->name = name;
  i->type = defaultValue.type();
  i->defaultValue = defaultValue;
  i->min = min;
  i->max = max;
  i->clamp = true;
  parameters.insert(name,i);
}

QWidget * IntegrationMethod::GenPage()
{
  QWidget *mainWidget = new QWidget();
  QFormLayout *layout = new QFormLayout();
  mainWidget->setLayout(layout);
  QWidget *w;
  foreach(IntegrationParameter * i, parameters){
    switch(i->type) {
    case QVariant::Int:
      w = new QSpinBox();
      ((QSpinBox*)w)->setValue(i->defaultValue.toInt());
      if(i->clamp){
        ((QSpinBox*)w)->setMinimum(i->min.toInt());
        ((QSpinBox*)w)->setMaximum(i->max.toInt());
      }else{
        ((QSpinBox*)w)->setMinimum(-9999999);
        ((QSpinBox*)w)->setMaximum(9999999);
      }
      break;
    case QVariant::Bool:
      w = new QCheckBox();
      ((QCheckBox*)w)->setChecked(i->defaultValue.toBool());
      break;
    case QVariant::Double:
      w = new QDoubleSpinBox();
      ((QDoubleSpinBox*)w)->setValue(i->defaultValue.toDouble());
      ((QDoubleSpinBox*)w)->setDecimals(8);
      if(i->clamp){
        ((QDoubleSpinBox*)w)->setMinimum(i->min.toDouble());
        ((QDoubleSpinBox*)w)->setMaximum(i->max.toDouble());
      }else{
        ((QDoubleSpinBox*)w)->setMinimum(-9999999);
        ((QDoubleSpinBox*)w)->setMaximum(9999999);
      }
      break;
    case QMetaType::Float:
      w = new QDoubleSpinBox();
      ((QDoubleSpinBox*)w)->setValue(i->defaultValue.toFloat());
      ((QDoubleSpinBox*)w)->setDecimals(4);
      ((QDoubleSpinBox*)w)->setMinimum(-9999999);
      ((QDoubleSpinBox*)w)->setMaximum(9999999);
      if(i->clamp){
        ((QDoubleSpinBox*)w)->setMinimum(i->min.toDouble());
        ((QDoubleSpinBox*)w)->setMaximum(i->max.toDouble());
      }else{
        ((QDoubleSpinBox*)w)->setMinimum(-9999999);
        ((QDoubleSpinBox*)w)->setMaximum(9999999);
      }
      break;
    default:
      continue;
    }
    i->widget = w;
    layout->addRow(new QLabel(i->name),w);
  }
  return mainWidget;
}

QVariant IntegrationMethod::GetParameter(QString name)
{
  if(parameters.contains(name)){
    QWidget *w = parameters.value(name)->widget;
    switch(parameters.value(name)->type){
    case QVariant::Int:
      return (qobject_cast<QSpinBox*>(w))->value();
    case QVariant::Bool:
      return ((QCheckBox*)w)->isChecked();
    case QVariant::Double:
      return ((QDoubleSpinBox*)w)->value();
    case QMetaType::Float:
      return (float)(((QDoubleSpinBox*)w)->value());
    default:
      return QVariant(false);
    }
  }
  return QVariant(false);
}

double IntegrationMethod::F(double x)
{
  return w->EvaluateFunction(x);
}
