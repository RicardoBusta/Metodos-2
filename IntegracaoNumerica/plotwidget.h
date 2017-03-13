#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QTransform>

class PlotWidget : public QWidget
{
  Q_OBJECT
public:
  explicit PlotWidget(QWidget *parent = 0);

private:
  /* Called when the widget must be redrawn */
  void paintEvent(QPaintEvent *e);

  /* Called when the widget is scaled */
  void resizeEvent(QResizeEvent *e);

  /* Saves the coordinate transform */
  QTransform transform;

  float a;
  float b;
signals:

public slots:
};

#endif // PLOTWIDGET_H
