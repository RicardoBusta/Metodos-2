#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScriptEngine>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  double EvaluateFunction(double x);
  QString Function();
private:
  Ui::MainWindow *ui;

  QScriptEngine engine;
  QScriptProgram program;

  double fdrawvalues[30];
private slots:
  void UpdateFunction();
};

#endif // MAINWINDOW_H
