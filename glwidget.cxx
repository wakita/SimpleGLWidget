#include "glwidget.hxx"
#include <QtDebug>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QPushButton>
#include <iostream>

std::map<QSurfaceFormat::OpenGLContextProfile, std::string> profile_str = {
  { QSurfaceFormat::OpenGLContextProfile::NoProfile, "NO Profile"},
  { QSurfaceFormat::OpenGLContextProfile::CoreProfile, "Core Profile"},
  { QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile, "Compatibility Profile"}
};

GLWidget::GLWidget(QWidget *parent)
  : QOpenGLWidget(parent) {
}

void GLWidget::onMessageLogged(const QOpenGLDebugMessage &debugMessage) {
  qDebug() << "GL Debug:" << debugMessage.message().toStdString().c_str();
}

QString m_text;
QOpenGLDebugLogger *logger;

void applicationMessage(QString &message) {
  logger->logMessage(QOpenGLDebugMessage::createApplicationMessage(message));
}

void GLWidget::keyPressEvent(QKeyEvent * event) {
  const int k = event->key();
  if (k == Qt::Key_Q || k == Qt::Key_Escape) exit(0);
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();

  QOpenGLContext *ctx = QOpenGLContext::currentContext();
  if (ctx->hasExtension(QByteArrayLiteral("GL_KHR_debug"))) {
    logger = new QOpenGLDebugLogger(this);
    connect(logger, SIGNAL(messageLogged(QOpenGLDebugMessage)),
            this, SLOT(onMessageLogged(QOpenGLDebugMessage)),
            Qt::DirectConnection);

    logger->initialize();
    logger->startLogging();
    applicationMessage(QStringLiteral("Message logging started for OpenGL diagnostics"));
  }

  QSurfaceFormat fmt = QOpenGLContext::currentContext()->format();

  m_text.sprintf("VERSION:  %d.%d (%s)",
                 fmt.version().first, fmt.version().second,
                 glGetString(GL_VERSION));
  applicationMessage(m_text);

  m_text.sprintf("PROFILE:  %s", profile_str[fmt.profile()].c_str());
  applicationMessage(m_text);

  m_text.sprintf("VENDOR:   %s", glGetString(GL_VENDOR));
  applicationMessage(m_text);

  m_text.sprintf("RENDERER: %s", glGetString(GL_RENDERER));
  applicationMessage(m_text);

  m_text.sprintf("GLSL:     %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
  applicationMessage(m_text);
}

QMatrix4x4 Projection;

void GLWidget::resizeGL(int h, int w) {
  m_text.sprintf("resizeGL(%d, %d)", h, w);
  applicationMessage(m_text);
  glViewport(0, 0, w, h);
  Projection.setToIdentity();
  Projection.perspective(70.f, (float)w/h, 0.3f, 100.f);
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
