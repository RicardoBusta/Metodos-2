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
  for(int i=0;i<30;i++){
    intervalX[i] = float(i)/29.0f;
  }
}

void PlotWidget::paintEvent(QPaintEvent *e) {
  QPainter painter(this);

  // Draw widget border
  painter.setBrush(palette().alternateBase().color());
  painter.setPen(palette().dark().color());
  painter.drawRect(this->rect().adjusted(0, 0, -1, -1));

  // Draw function
  painter.setPen(Qt::black);
  painter.setBrush(Qt::red);

  //painter.drawRect(QRect((QPoint(0, 0) * transform), (QPoint(1, 1) * transform)));

  // Draw text limits
  qDebug() << "drawing polygon" << polygon.size();
  painter.drawPolygon(polygon*transform);

  painter.drawText((QPoint(0, 0) * transform)+QPoint(0,12),QString::number(a));
  painter.drawText((QPoint(1, 0) * transform)+QPoint(0,12),QString::number(b));
}

void PlotWidget::resizeEvent(QResizeEvent *e) {
  int w = (width() - 1) - 2 * kBorder;
  int h = (height() - 1) - 2 * kBorder;

  transform.reset();
  transform.translate(kBorder, h + kBorder);
  transform.scale(w, -h);
}

void PlotWidget::RecalculateFunction()
{
  polygon.clear();
  polygon.append(QPointF(1,0));
  polygon.append(QPointF(0,0));
  float max_y = std::numeric_limits<float>::min();
  float min_y = std::numeric_limits<float>::max();;
  for(int i=0;i<30;i++){
    float x = intervalX[i];
    float y = mainWindow->EvaluateFunction(intervalX[i]);
    max_y = qMax(y,max_y);
    min_y = qMin(y,min_y);
    qDebug() << x << y;
    polygon.append(QPointF(intervalX[i],mainWindow->EvaluateFunction(intervalX[i])));
    ;
  }
  float scale = 1.0f/(max_y-min_y);

  //transform.scale(1,scale);
  repaint();
}
