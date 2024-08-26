#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H



#include<QPushButton>

#include<QDebug>
#include<QEvent>
#include<QWheelEvent>

class myPushButton : public QPushButton
{
Q_OBJECT
public:
  myPushButton(QWidget *parent = nullptr);

protected:
  void enterEvent(QEvent *event) override;
  void leaveEvent(QEvent *event) override;

  void wheelEvent(QWheelEvent *event) override;

signals:
  void myPushButtonEnter();
  void myPushButtonLeave();

  void myPushButtonWheelUpDown(int delta);
};

#endif