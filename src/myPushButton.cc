#include"myPushButton.hpp"

myPushButton::myPushButton(QWidget *parent)
 :QPushButton(parent)
{

}

void myPushButton::enterEvent(QEvent *event)
{
  QPushButton::enterEvent(event);
  emit(myPushButtonEnter());
}
void myPushButton::leaveEvent(QEvent *event)
{
  QPushButton::leaveEvent(event);
  emit(myPushButtonLeave());
} 

void myPushButton::wheelEvent(QWheelEvent *event) 
{

  emit myPushButtonWheelUpDown(event->delta());
}
