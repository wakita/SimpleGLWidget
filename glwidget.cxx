#include "glwidget.hxx"
#include <QPushButton>

GLWidget::GLWidget(QWidget *parent)
  : QOpenGLWidget(parent) {
}

std::map<QSurfaceFormat::OpenGLContextProfile, std::string> profile_str = {
  { QSurfaceFormat::OpenGLContextProfile::NoProfile, "NO Profile"},
  { QSurfaceFormat::OpenGLContextProfile::CoreProfile, "Core Profile"},
  { QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile, "Compatibility Profile"}
};

void GLWidget::initializeGL() {
  QSurfaceFormat fmt = QOpenGLContext::currentContext()->format();
  qWarning("OpenGL %d.%d %s", fmt.version().first, fmt.version().second, profile_str[fmt.profile()].c_str());
  initializeOpenGLFunctions();
}

int clearColor = 0;
double clearColors[][4] = { { 0.5, 0.2, .2, 1 }, { 0.2, 0.5, 0.2, 1 }, { 0.2, 0.2, 0.5, 1 } };

void GLWidget::paintGL() {
  double *c = clearColors[clearColor];
  glClearColor((float)c[0], (float)c[1], (float)c[2], (float)c[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::changeBackground() {
  QPushButton *button = (QPushButton *)sender();

  QString buttonText = button->text();
  if      (buttonText.compare("Red")   == 0) clearColor = 0;
  else if (buttonText.compare("Green") == 0) clearColor = 1;
  else if (buttonText.compare("Blue")  == 0) clearColor = 2;
  update();
}
