#ifndef GLWIDGET_HXX
#define GLWIDGET_HXX

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>

class GLWidget : public QOpenGLWidget,
    protected QOpenGLFunctions_4_3_Core
{
  Q_OBJECT
public:
  explicit GLWidget(QWidget *parent = 0);

  void initializeGL();
  void paintGL();

private slots:
  void changeBackground();
};

#endif // GLWIDGET_HXX
