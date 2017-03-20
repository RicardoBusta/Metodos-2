#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScriptEngine>
#include <QVector>

namespace Ui {
class MainWindow;
}

class IntegrationMethod;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  double EvaluateFunction(double x);
  QString Function();

  IntegrationMethod *CurrentMethod();
private:
  Ui::MainWindow *ui;

  QScriptEngine engine;
  QScriptProgram program;

  double fdrawvalues[30];

  QVector<IntegrationMethod*> methods;

  void AddMethods();

  IntegrationMethod *currentMethod;
private slots:
  void UpdateFunction();
  void ReadFunctionValues();
  void CalculateIntegral();
};

#endif // MAINWINDOW_H
