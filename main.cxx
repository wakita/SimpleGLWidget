#include "mainwindow.hxx"
#include <QApplication>
#include <QSurfaceFormat>
#include <map>

extern Ui::MainWindow mainWindow;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QSurfaceFormat fmt;
  fmt.setMajorVersion(4); fmt.setMinorVersion(5);
  fmt.setProfile(QSurfaceFormat::CoreProfile);
  fmt.setSamples(4);
  fmt.setDepthBufferSize(24);
  fmt.setOption(QSurfaceFormat::DebugContext);
  QSurfaceFormat::setDefaultFormat(fmt);

  MainWindow *w = new MainWindow;

  w->show();

  return a.exec();
}
