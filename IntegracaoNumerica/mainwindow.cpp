#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScriptContext>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->plot_widget->mainWindow = this;

  QObject::connect(ui->update_graphic_pushButton,SIGNAL(clicked(bool)),this,SLOT(UpdateFunction()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

double MainWindow::EvaluateFunction(double x)
{
  engine.globalObject().setProperty("x",x);
  double y = engine.evaluate(program).toNumber();
  return y;
}

void MainWindow::UpdateFunction()
{
  program = ui->function_lineEdit->text();
  ui->plot_widget->RecalculateFunction();
}
