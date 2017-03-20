#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  qputenv("QT_MESSAGE_PATTERN","(%{file}:%{line}) %{message}");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
