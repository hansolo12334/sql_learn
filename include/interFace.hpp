#ifndef INTERFACE_H
#define INTERFACE_H


#define DEBUG_H 0

#include<QtWidgets/QtWidgets>

#include<QPushButton>
#include<QLabel>
#include<QListView>
#include<QFrame>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QDialogButtonBox>
#include<QMessageBox>
#include<QSpacerItem>


#include<QComboBox>
#include<QTableView>
#include<QStandardItemModel>


#include<regex>

#include"mysqlDataBase.hpp"

#include"myPushButton.hpp"

#include<jsoncpp/json/json.h>


class interFace : public QMainWindow
{
Q_OBJECT
public:
  interFace(QWidget *parent=nullptr);
  ~interFace();

private:
  DataBase m_db;

  int data_rows = -1;
  int data_cols = -1;
  int maxShowOnePage = 100;
  int maxPages = 1;
  QFont m_font;

  QString m_table_name;
  int m_current_switch_index = 0;
  QStringList m_headerLables;

  

  QFrame m_frame;
  QFrame m_frame1;
  QFrame switch_frame;

  QTableView m_table;
  QStandardItemModel m_model;

  QLabel m_lable1;
  QLabel m_lable2;

  QPushButton m_bt1;
  QPushButton m_bt2;

  QComboBox m_comboBx;
  QLabel m_combbx_lable;

  QPushButton m_refrashBt;
  QLabel m_refrashLb;

  QListView m_listv1;
  QListView m_listv2;
  
  QHBoxLayout hblt1;
  QHBoxLayout hblt2;

  QVBoxLayout vblt1;
  QVBoxLayout vblt2;
  QVBoxLayout vblt3;
  QVBoxLayout vblt4;
  QVBoxLayout vblt5;

  myPushButton b11;
  myPushButton b22;

  QPushButton b1;
  QPushButton b2;

  QHBoxLayout maxItemsOnePagelt;
  QLabel maxItemsOnePageLable;
  QLineEdit maxItemsOnePageLineEdit;

  QMenuBar mainMenuBar;
  QMenu *chooseDataTable_action = nullptr;

  QVector<QPair<QPushButton *, int>> switch_labels;
  bool m_first_init = true;
  // private:
  // void refresh_data();

private:
  bool getJsonData(std::string &str,QTreeWidget &treeWiget);
  bool checkUrl(QString &str);

private slots:
  void refresh_data();
  void connect_to_database();
  void insert_data();

  void maxButtonEnter();
  void maxButtonLeave();
  void maxButtonClicked();

  void switch_button_clicked();
  void switch_button_mouseWheelRolled(int delta);

  void show_hidden_data(const QModelIndex &index);

protected:
  void closeEvent(QCloseEvent *event) override
  {
    QMessageBox myBox;
    myBox.setFont(m_font);
    myBox.setWindowTitle("提示");
    myBox.setText("退出程序?");
    myBox.setStandardButtons(QMessageBox::Button::Yes | QMessageBox::Button::No);
    auto re = myBox.exec();


    if(re==QMessageBox::Yes){
      event->accept();
      exit(0);
    }
    else{
      event->ignore();
      return;
    }
  }
};


#endif