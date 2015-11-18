#ifndef GLWIDGET_HXX
#define GLWIDGET_HXX

#include <QOpenGLDebugMessage>
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

private:
  //void applicationMessage(QString &message);

private slots:
  void changeBackground();
  void onMessageLogged(const QOpenGLDebugMessage & debugMessage);
};

#endif // GLWIDGET_HXX
