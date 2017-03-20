#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScriptContext>

#include "metodos/rectanglemethod.h"
#include "integrationmethod.h"

/* Registro de métodos para serem usados pela aplicação */
void MainWindow::AddMethods()
{
  methods.push_back(new RectangleMethod());
}

/* Construtor da janela principal */
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  currentMethod(nullptr)
{
  ui->setupUi(this);

  AddMethods();

  foreach(IntegrationMethod *i, methods){
    i->w = this;
    ui->method_comboBox->addItem(i->MethodName());
    ui->method_stackedWidget->addWidget(i->GenPage());
  }

  /* Ajusta a proporção das partes da janela */
  ui->splitter->setStretchFactor(0,1);
  ui->splitter->setStretchFactor(1,0);

  ui->plot_widget->mainWindow = this;

  ui->function_lineEdit->setText("x*x");

  QObject::connect(ui->update_graphic_pushButton,SIGNAL(clicked(bool)),this,SLOT(UpdateFunction()));
  QObject::connect(ui->method_comboBox,SIGNAL(currentIndexChanged(int)),ui->method_stackedWidget,SLOT(setCurrentIndex(int)));
  QObject::connect(ui->integrate_pushButton,SIGNAL(clicked(bool)),this,SLOT(CalculateIntegral()));
  /* Inicializa o gráfico com a função default */
  UpdateFunction();
}

MainWindow::~MainWindow()
{
  delete ui;
}

/* Calcula o valor da função usando o parâmetro x */
double MainWindow::EvaluateFunction(double x)
{
  engine.globalObject().setProperty("x",x);
  double y = engine.evaluate(program).toNumber();
  return y;
}

/* Retorna a string com a fórmula da função digitada pelo usuário */
QString MainWindow::Function()
{
  return program.sourceCode();
}

IntegrationMethod *MainWindow::CurrentMethod()
{
  return currentMethod;
}

/* Atualiza a função após algum parâmetro ser alterado */
void MainWindow::UpdateFunction()
{
  ReadFunctionValues();
  ui->plot_widget->RecalculateFunction();
}

void MainWindow::ReadFunctionValues()
{
  ui->plot_widget->a = ui->inter_a_doubleSpinBox->value();
  ui->plot_widget->b = ui->inter_b_doubleSpinBox->value();
  program = ui->function_lineEdit->text();
}

void MainWindow::CalculateIntegral()
{
  ReadFunctionValues();
  int index = ui->method_comboBox->currentIndex();
  if(index > 0){
    IntegrationMethod *m = methods[index-1];
    m->a = ui->inter_a_doubleSpinBox->value();
    m->b = ui->inter_b_doubleSpinBox->value();
    double res = m->Integrate();
    ui->result_label->setText(QString::number(res));
    currentMethod = m;
    ui->plot_widget->RecalculateFunction();
  }else{
    currentMethod = nullptr;
  }
}
