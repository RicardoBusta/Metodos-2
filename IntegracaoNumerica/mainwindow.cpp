#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScriptContext>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->splitter->setStretchFactor(0,1);
  ui->splitter->setStretchFactor(1,0);

  ui->plot_widget->mainWindow = this;

  ui->function_lineEdit->setText("x*x");

  QObject::connect(ui->update_graphic_pushButton,SIGNAL(clicked(bool)),this,SLOT(UpdateFunction()));

  UpdateFunction();
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

QString MainWindow::Function()
{
  return program.sourceCode();
}

void MainWindow::UpdateFunction()
{
  ui->plot_widget->a = ui->inter_a_doubleSpinBox->value();
  ui->plot_widget->b = ui->inter_b_doubleSpinBox->value();
  ui->inter_b_doubleSpinBox->value();
  program = ui->function_lineEdit->text();
  ui->plot_widget->RecalculateFunction();
}
