#include "mainwindow.hxx"
#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <iostream>
#include <map>

extern Ui::MainWindow mainWindow;

int main(int argc, char *argv[])
{
  std::cerr << "starting" << std::endl;

  QApplication a(argc, argv);

  QSurfaceFormat fmt;
  fmt.setMajorVersion(4);
  fmt.setMinorVersion(3);
  fmt.setProfile(QSurfaceFormat::CoreProfile);
  fmt.setSamples(4);
  fmt.setDepthBufferSize(24);

  QSurfaceFormat::setDefaultFormat(fmt);

  MainWindow *w = new MainWindow;

  QOpenGLContext *m_context = new QOpenGLContext;
  m_context->setFormat(fmt);
  m_context->create();

  std::map<QSurfaceFormat::OpenGLContextProfile, std::string> profile_str = {
    { QSurfaceFormat::OpenGLContextProfile::NoProfile, "NO Profile"},
    { QSurfaceFormat::OpenGLContextProfile::CoreProfile, "Core Profile"},
    { QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile, "Compatibility Profile"}
  };

  fmt = m_context->format();

  qWarning("OpenGL %d.%d %s", fmt.version().first, fmt.version().second, profile_str[fmt.profile()].c_str());

  w->show();

  return a.exec();
}
