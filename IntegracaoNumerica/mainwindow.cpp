#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScriptContext>

#include "metodos/rectanglemethod.h"
#include "integrationmethod.h"

/* Registro de métodos para serem usados pela aplicação */

QRegularExpression jsMath = QRegularExpression("([^\\s]|^)(abs|acos|asin|atan|atan2|ceil|exp|floor|log|max|min|pow|random|round|sqrt|tan|cos|sin)\\(");

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

  QObject::connect(ui->method_comboBox,SIGNAL(currentIndexChanged(int)),ui->method_stackedWidget,SLOT(setCurrentIndex(int)));
  QObject::connect(ui->integrate_pushButton,SIGNAL(clicked(bool)),this,SLOT(CalculateIntegral()));

  QObject::connect(ui->cos_pushButton,SIGNAL(clicked(bool)),this,SLOT(SetFunction()));
  QObject::connect(ui->exp_pushButton,SIGNAL(clicked(bool)),this,SLOT(SetFunction()));
  QObject::connect(ui->pow_pushButton,SIGNAL(clicked(bool)),this,SLOT(SetFunction()));
  QObject::connect(ui->abs_pushButton,SIGNAL(clicked(bool)),this,SLOT(SetFunction()));

  /* Inicializa o gráfico com a função default */
  UpdateFunction();
}

MainWindow::~MainWindow()
{
  delete ui;
}

QString MainWindow::PrepareProgram(const QString &program)
{
  QString out = program;
  qDebug() << "in" << out;
  out.replace(jsMath,"\\1Math.\\2(");
  qDebug() << "out" << out;
  return out;
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
  program = PrepareProgram(ui->function_lineEdit->text());
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
  }else{
    currentMethod = nullptr;
  }
  ui->plot_widget->RecalculateFunction();
}

void MainWindow::SetFunction()
{
  QWidget *w = qobject_cast<QWidget*>(sender());
  if(w==ui->abs_pushButton){
    ui->function_lineEdit->setText("abs(x)");
  }else if(w==ui->pow_pushButton){
    ui->function_lineEdit->setText("ceil(x)");
  }else if(w==ui->cos_pushButton){
    ui->function_lineEdit->setText("cos(x)");
  }else if(w==ui->exp_pushButton){
    ui->function_lineEdit->setText("exp(x)");
  }
  UpdateFunction();
}
