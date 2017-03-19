#include "plotwidget.h"

#include <QPainter>
#include <QVector2D>
#include <QDebug>
#include <limits>

#include "mainwindow.h"

// Pixels de largura da borda ao redor do gráfico
const int kBorder = 40;

PlotWidget::PlotWidget(QWidget *parent)
  : QWidget(parent),
    a(0),
    b(1) {
  for(int i=0;i<kDrawDiv;i++){
    intervalX[i] = float(i)/float(kDrawDiv-1);
  }
}

void PlotWidget::paintEvent(QPaintEvent *e) {
  QPainter painter(this);

  // Calcular eixos do zero na transformação
  QPointF fzero = QPointF(0,0)*transform;
  QPointF wzero = QPointF(a,min_y)*transform;
  QPointF wone = QPointF(b,max_y)*transform;

  // Desenhar área da função
  painter.setBrush(Qt::white);
  painter.setPen(Qt::NoPen);
  painter.drawRect(QRectF(wzero,wone));

  // Desenhar função
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::gray);
  qDebug() << "drawing polygon" << polygon.size();
  painter.drawPolygon(polygon*transform);

  painter.setPen(Qt::black);
  painter.setBrush(Qt::NoBrush);

  // Desenhar eixos do zero
  painter.drawLine(QPointF(fzero.x(),wzero.y()),QPointF(fzero.x(),wone.y()));
  painter.drawLine(QPointF(wzero.x(),fzero.y()),QPointF(wone.x(),fzero.y()));

  // Desenhar labels com números
  painter.drawText((QPointF(0, 0) * windowTransform)+QPointF(0,12),QString::number(a));
  painter.drawText((QPointF(1, 0) * windowTransform)+QPointF(0,12),QString::number(b));
  painter.drawText((QPointF(0, 1) * windowTransform)+QPointF(0,-12),formula);
  painter.drawText((QPointF(1, 0) * windowTransform)+QPointF(12,0),QString::number(min_y));
  painter.drawText((QPointF(1, 1) * windowTransform)+QPointF(12,0),QString::number(max_y));
  painter.drawText((QPointF(wone.x(), fzero.y()))+QPointF(12,0),"0");
  painter.drawText((QPointF(fzero.x(), wzero.y()))+QPointF(0,12),"0");
}

void PlotWidget::resizeEvent(QResizeEvent *e) {
  int w = (width() - 1) - 2 * kBorder;
  int h = (height() - 1) - 2 * kBorder;

  windowTransform.reset();
  windowTransform.translate(kBorder, h + kBorder);
  windowTransform.scale(w, -h);
  transform = functionTransform*windowTransform;
}

void PlotWidget::RecalculateFunction()
{
  polygon.clear();
  max_y = 0;
  min_y = 0;

  float l = b-a;

  formula = "f(x) = "+mainWindow->Function();

  for(int i=0;i<kDrawDiv;i++){
    float x = a + l*intervalX[i];
    float y = mainWindow->EvaluateFunction(x);
    max_y = qMax(y,max_y);
    min_y = qMin(y,min_y);
    qDebug() << x << y;
    polygon.append(QPointF(x,y));
    ;
  }

  polygon.append(QPointF(b,0));
  polygon.append(QPointF(a,0));

  functionTransform.reset();
  qDebug() << "print l" << l;
  functionTransform.scale(1/l,1/(max_y-min_y));
  if(min_y < 0){
    functionTransform.translate(0,-min_y);
  }
  functionTransform.translate(-a,0);
      //functionTransform.translate(-a,-min_y);
  transform = functionTransform*windowTransform;
  repaint();
}
