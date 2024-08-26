#include"interFace.hpp"


int main(int argc,char **argv)
{
  QApplication a{argc,argv};

  interFace iface;

  iface.resize(1800, 900);

  iface.show();

  return a.exec();
}