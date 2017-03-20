#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QTransform>

class MainWindow;
class IntegrationMethod;

const int kDrawDiv = 50;

class PlotWidget : public QWidget
{
  Q_OBJECT
public:
  explicit PlotWidget(QWidget *parent = 0);

  MainWindow *mainWindow;

  void RecalculateFunction();

  float a;
  float b;

  float max_y;
  float min_y;
private:
  /* Called when the widget must be redrawn */
  void paintEvent(QPaintEvent *e);

  /* Called when the widget is scaled */
  void resizeEvent(QResizeEvent *e);

  /* Saves the coordinate transform */
  QTransform transform;
  QTransform functionTransform;
  QTransform windowTransform;

  float intervalX[kDrawDiv];

  QPolygonF polygon;

  QString formula;

signals:

public slots:
};

#endif // PLOTWIDGET_H
