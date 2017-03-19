#include "plotwidget.h"

#include <QPainter>
#include <QVector2D>
#include <QDebug>
#include <limits>

#include "mainwindow.h"

const int kBorder = 30;

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

  // Draw widget border
  painter.setBrush(Qt::white);
  painter.setPen(palette().dark().color());
  painter.drawRect(this->rect().adjusted(0, 0, -1, -1));

  // Draw function
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::gray);

  //painter.drawRect(QRect((QPoint(0, 0) * transform), (QPoint(1, 1) * transform)));

  // Draw text limits
  qDebug() << "drawing polygon" << polygon.size();
  painter.drawPolygon(polygon*transform);

  QPointF fzero = QPointF(0,0)*transform;
  QPointF wzero = QPointF(a,min_y)*transform;
  QPointF wone = QPointF(b,max_y)*transform;

  painter.setPen(Qt::black);
  painter.setBrush(Qt::NoBrush);

  painter.drawLine(QPointF(fzero.x(),wzero.y()),QPointF(fzero.x(),wone.y()));
  painter.drawLine(QPointF(wzero.x(),fzero.y()),QPointF(wone.x(),fzero.y()));

  painter.drawText((QPointF(0, 0) * windowTransform)+QPointF(0,12),QString::number(a));
  painter.drawText((QPointF(1, 0) * windowTransform)+QPointF(0,12),QString::number(b));
  painter.drawText((QPointF(0, 1) * windowTransform)-QPointF(0,12),formula);
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
