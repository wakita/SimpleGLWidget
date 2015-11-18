#include "glwidget.hxx"
#include <QPushButton>

GLWidget::GLWidget(QWidget *parent)
  : QOpenGLWidget(parent),
    gl(0) {
}

void GLWidget::initializeGL() {
#if (defined(Q_OS_MAC))
  initializeOpenGLFunctions(); for Mac
#else
  if (gl == nullptr) {
    gl = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    if (!gl) {
      qFatal("Requires OpenGL >= 4.3");
      exit(1);
    }
    if (!gl->initializeOpenGLFunctions()) {
      qFatal("Failed to initialize Open GL 4.3 Core Profile functions");
      exit(1);
    }

    const GLubyte *vendor(gl->glGetString(GL_VENDOR));
    const GLubyte *renderer(gl->glGetString(GL_RENDERER));
    qWarning("Vendor: %s", vendor);
    qWarning("Renderer: %s", renderer);
  }
#endif
}

int clearColor = 0;
double clearColors[][4] = { { 0.5, 0.2, .2, 1 }, { 0.2, 0.5, 0.2, 1 }, { 0.2, 0.2, 0.5, 1 } };

void GLWidget::paintGL() {
  double *c = clearColors[clearColor];
  gl->glClearColor((float)c[0], (float)c[1], (float)c[2], (float)c[3]);
  gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::changeBackground() {
  QPushButton *button = (QPushButton *)sender();

  QString buttonText = button->text();
  if      (buttonText.compare("Red")   == 0) clearColor = 0;
  else if (buttonText.compare("Green") == 0) clearColor = 1;
  else if (buttonText.compare("Blue")  == 0) clearColor = 2;
  update();
}
