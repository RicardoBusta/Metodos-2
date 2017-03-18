#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QTransform>

class MainWindow;

class PlotWidget : public QWidget
{
  Q_OBJECT
public:
  explicit PlotWidget(QWidget *parent = 0);

  MainWindow *mainWindow;

  void RecalculateFunction();
private:
  /* Called when the widget must be redrawn */
  void paintEvent(QPaintEvent *e);

  /* Called when the widget is scaled */
  void resizeEvent(QResizeEvent *e);

  /* Saves the coordinate transform */
  QTransform transform;

  float a;
  float b;

  float intervalX[30];

  QPolygonF polygon;

signals:

public slots:
};

#endif // PLOTWIDGET_H
