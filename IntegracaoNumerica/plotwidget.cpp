#include "plotwidget.h"

#include <QPainter>
#include <QVector2D>

const int kBorder = 30;

PlotWidget::PlotWidget(QWidget *parent)
    : QWidget(parent),
      a(0),
      b(1) {
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

  painter.drawRect(QRect((QPoint(0, 0) * transform), (QPoint(1, 1) * transform)));

  // Draw text limits

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
