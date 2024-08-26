#include "interFace.hpp"
#include <qdebug.h>

interFace::interFace(QWidget *parent)
    : QMainWindow(parent)
{
  m_font.setPixelSize(18);

  QMenu *mainMenu = new QMenu("菜单(&M)");
  QMenu *toolMenu = new QMenu("工具(&T)");
  mainMenu->setFont(m_font);
  toolMenu->setFont(m_font);

  mainMenuBar.addMenu(mainMenu);
  mainMenuBar.addMenu(toolMenu);

  mainMenuBar.setFont(m_font);

  QAction *connect_action = new QAction("登陆");
  QAction *quit_action = new QAction("退出");

  chooseDataTable_action = new QMenu("选择表");
  QAction *insertData_action = new QAction("插入数据");
  QAction *refreshData_action = new QAction("刷新数据");

  mainMenu->addAction(connect_action);
  mainMenu->addSeparator();
  mainMenu->addAction(quit_action);

  mainMenu->setFont(m_font);

  toolMenu->addMenu(chooseDataTable_action);
  toolMenu->addSeparator();
  toolMenu->addAction(insertData_action);
  toolMenu->addSeparator();
  toolMenu->addAction(refreshData_action);
  toolMenu->setFont(m_font);

  this->setMenuBar(&mainMenuBar);

  connect(quit_action, &QAction::triggered, this, [=]()
        { 
            
          QMessageBox myBox;
          myBox.setWindowTitle("提示");
          myBox.setText("退出程序？");
          myBox.setFont(m_font);
          myBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
          auto re=myBox.exec();  
          if(re=QMessageBox::Yes)
          {
            exit(0);
          } 
        }
  );
  connect(connect_action, SIGNAL(triggered()), this, SLOT(connect_to_database()));
  connect(insertData_action, SIGNAL(triggered()), this, SLOT(insert_data()));

  b1.setText("<");
  b2.setText(">");
  b11.setText("1");
  b22.setText("5");
  b1.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
  b2.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
  b11.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
  b22.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  b1.setStyleSheet(QString("background-color: rgba(255, 255, 255,50)"));
  b2.setStyleSheet(QString("background-color: rgba(255, 255, 255,50)"));
  b1.setObjectName("left_bt");
  b2.setObjectName("right_bt");

  QSpacerItem *switche_spacer = new QSpacerItem(400, 10, QSizePolicy::Expanding);

  b11.setObjectName("maxleft");
  b22.setObjectName("maxright");

  vblt2.addWidget(&m_bt2);

  hblt2.addLayout(&vblt2);
  hblt2.addSpacerItem(switche_spacer);

  hblt2.addWidget(&b11);
  hblt2.addWidget(&b1);
  for (int i = 0; i < 5; i++)
  {
    myPushButton *b1 = new myPushButton();
    switch_labels.push_back({b1, i});
    b1->setText(QString::number(i + 1));
    b1->setObjectName(QString("switch_bt_" + QString::number(i)));
    b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    b1->setStyleSheet(QString("background-color: rgba(255, 255, 255,50)"));
    b1->setFont(m_font);
    hblt2.addWidget(b1);

    connect(b1, SIGNAL(clicked()), this, SLOT(switch_button_clicked()));
 
    connect(b1,SIGNAL(myPushButtonWheelUpDown(int)), this, SLOT(switch_button_mouseWheelRolled(int)));
  }


  switch_labels[m_current_switch_index].first->setStyleSheet(QString("background-color: rgba(200, 200, 200,50)"));
  hblt2.addWidget(&b2);
  hblt2.addWidget(&b22);
  hblt2.setSpacing(0);
  switch_frame.setLayout(&hblt2);

  connect(&b1, SIGNAL(clicked()), this, SLOT(switch_button_clicked()));
  connect(&b2, SIGNAL(clicked()), this, SLOT(switch_button_clicked()));

  connect(&b11, SIGNAL(myPushButtonEnter()), this, SLOT(maxButtonEnter()));
  connect(&b11, SIGNAL(myPushButtonLeave()), this, SLOT(maxButtonLeave()));
  connect(&b11, SIGNAL(clicked()), this, SLOT(maxButtonClicked()));

  connect(&b22, SIGNAL(myPushButtonEnter()), this, SLOT(maxButtonEnter()));
  connect(&b22, SIGNAL(myPushButtonLeave()), this, SLOT(maxButtonLeave()));
  connect(&b22, SIGNAL(clicked()), this, SLOT(maxButtonClicked()));

  // vblt1.addWidget(&m_lable1);
  vblt1.addWidget(&m_bt1);

  // vblt2.addWidget(&m_lable2);

  vblt4.addWidget(&m_combbx_lable);
  vblt4.addWidget(&m_comboBx);

  vblt5.addWidget(&m_refrashLb);
  vblt5.addWidget(&m_refrashBt);

  hblt1.addLayout(&vblt1);

  hblt1.addLayout(&vblt4);
  hblt1.addLayout(&vblt5);

  m_frame1.setLayout(&hblt1);

  QSpacerItem *maxItemsOnePageSpacer = new QSpacerItem(400, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
  maxItemsOnePagelt.addSpacerItem(maxItemsOnePageSpacer);
  maxItemsOnePagelt.addWidget(&maxItemsOnePageLable);
  maxItemsOnePagelt.addWidget(&maxItemsOnePageLineEdit);
  maxItemsOnePageLable.setText("每页显示的内容");
  maxItemsOnePageLineEdit.setText(QString::number(maxShowOnePage));
  maxItemsOnePageLable.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  maxItemsOnePageLineEdit.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  maxItemsOnePagelt.setStretch(0, 8);
  maxItemsOnePagelt.setStretch(1, 1);
  maxItemsOnePagelt.setStretch(2, 1);

  vblt3.addWidget(&switch_frame);
  vblt3.addWidget(&m_table);
  vblt3.addLayout(&maxItemsOnePagelt);
  vblt3.addWidget(&m_frame1);

  m_bt1.setText("插入");
  m_bt2.setText("连接数据库");

  m_bt2.setStyleSheet(QString("background-color: rgba(180, 0, 0,150)"));

  // m_lable1.setText("xxxxxxx");
  // m_lable2.setText("ssssss");
  m_combbx_lable.setText("选择表");
  // m_refrashLb.setText("刷新数据");
  m_refrashBt.setText("刷新数据");
  m_frame.setLayout(&vblt3);

  this->setCentralWidget(&m_frame);

  connect(&m_bt1, SIGNAL(clicked()), this, SLOT(insert_data()));
  connect(&m_bt2, SIGNAL(clicked()), this, SLOT(connect_to_database()));
  connect(&m_refrashBt, SIGNAL(clicked()), this, SLOT(refresh_data()));
  connect(&maxItemsOnePageLineEdit, &QLineEdit::returnPressed, this, [&]()
          { refresh_data(); });

  m_model.setHorizontalHeaderLabels({"id", "name", "password", "email"});

  m_table.setModel(&m_model);
  m_table.setFont(m_font);
  m_table.resizeColumnsToContents();
  // m_table.resizeRowsToContents();
  m_table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_table.setShowGrid(true); // 显示网格线

  connect(&m_table, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(show_hidden_data(const QModelIndex &)));

  //
  b11.setFont(m_font);
  b22.setFont(m_font);
  b1.setFont(m_font);
  b2.setFont(m_font);
  maxItemsOnePageLable.setFont(m_font);
  maxItemsOnePageLineEdit.setFont(m_font);
  m_bt1.setFont(m_font);
  m_bt2.setFont(m_font);
  // m_lable1.setFont(m_font);
  // m_lable2.setFont(m_font);
  m_combbx_lable.setFont(m_font);
  m_refrashBt.setFont(m_font);
#if DEBUG_H
  QObject::dumpObjectTree();
#endif
}

interFace::~interFace()
{
  for (int i = 0; i < switch_labels.size(); i++)
  {
    if (switch_labels[i].first == nullptr)
    {
      delete switch_labels[i].first;
      switch_labels[i].first = nullptr;
    }
  }
}

void interFace::connect_to_database()
{
  if (m_db.checkState())
  {
    QMessageBox myBox;
    myBox.setWindowTitle("警告");
    myBox.setText("已有打开的数据库");
    myBox.setFont(m_font);
    myBox.setStandardButtons(QMessageBox::Yes);
    myBox.exec();
    return;
  }
  QDialog dlg;
  dlg.setWindowTitle("登陆");

  QFormLayout form(&dlg);

  dlg.setLayout(&form);

  QLabel lb1, lb2, lb3, lb4, lb5;
  QLineEdit ld1, ld2, ld3, ld4, ld5;

  lb1.setText("ip");
  lb2.setText("name");
  lb3.setText("password");
  lb4.setText("databaseName");
  lb5.setText("port");

  ld1.setText("localhost");
  ld2.setText("hansolo");
  ld3.setText("********");
  ld4.setText("rrys_data"); // database_hansolo
  ld5.setText("3306");

  ld3.setEchoMode(QLineEdit::Password);

  lb1.setFont(m_font);
  lb2.setFont(m_font);
  lb3.setFont(m_font);
  lb4.setFont(m_font);
  lb5.setFont(m_font);

  ld1.setFont(m_font);
  ld2.setFont(m_font);
  ld3.setFont(m_font);
  ld4.setFont(m_font);
  ld5.setFont(m_font);

  form.addRow(&lb1, &ld1);
  form.addRow(&lb2, &ld2);
  form.addRow(&lb3, &ld3);
  form.addRow(&lb4, &ld4);
  form.addRow(&lb5, &ld5);

  QDialogButtonBox qdgbx(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dlg);

  form.addRow(&qdgbx);

  connect(&qdgbx, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);

  connect(&qdgbx, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

  dlg.adjustSize();
  dlg.setMinimumSize(200, 100);

  while (dlg.exec() == QDialog::Accepted)
  {
    if (!m_db.connect(ld1.text().toStdString(), ld2.text().toStdString(), ld3.text().toStdString(), ld4.text().toStdString(), ld4.text().toInt()))
    {
      QMessageBox myBox;
      myBox.setWindowTitle("警告");
      myBox.setText("填写错误");
      myBox.setFont(m_font);
      myBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
      myBox.exec();

    }
    else
    {
      QMessageBox myBox(&dlg);
      myBox.setWindowTitle("提示");
      myBox.setText("登陆成功");
      myBox.setFont(m_font);
      myBox.setStandardButtons(QMessageBox::Yes);
      myBox.exec();

      m_bt2.setStyleSheet(QString("background-color: rgba(0, 180, 0,150)"));
      refresh_data();
      return;
    }
  }
  return;
}

void interFace::refresh_data()
{

  if (m_first_init)
  {

    auto table_names = m_db.getTablesStrings();
    if (table_names.size() <= 0)
    {
      return;
    }
    m_first_init = false;
    m_comboBx.clear();
    for (int i = 0; i < table_names.size(); i++)
    {
      m_comboBx.addItem(QString::fromStdString(table_names[i]));
      QAction *tb_action = new QAction(QString::fromStdString(table_names[i]));
      chooseDataTable_action->addAction(tb_action);
      chooseDataTable_action->setFont(m_font);

      connect(tb_action, &QAction::triggered, this, [&]()
              {
                auto tb_act = qobject_cast<QAction *>(this->sender());
                m_table_name = tb_act->text();
                qDebug() << m_table_name;
                m_comboBx.setCurrentText(m_table_name);
              });
    }
    m_comboBx.setFont(m_font);
    if (m_comboBx.currentIndex() < 0)
    {
      return;
    }
  }

  int range_index = switch_labels[m_current_switch_index].second;
  //
  m_model.clear();

  if (m_comboBx.currentText() != m_table_name || maxItemsOnePageLineEdit.text().toInt() != maxShowOnePage)
  {
    m_table_name = m_comboBx.currentText();
    qDebug() << m_table_name;
    m_db.getDataSize(m_table_name.toStdString(), data_rows, data_cols);

    maxShowOnePage = maxItemsOnePageLineEdit.text().toInt();
    if (maxShowOnePage <= 0)
    {
      maxShowOnePage = 100;
      maxItemsOnePageLineEdit.setText(QString::number(maxShowOnePage));
    }
    maxPages = data_rows % maxShowOnePage == 0 ? data_rows / maxShowOnePage : data_rows / maxShowOnePage + 1;

    b22.setText(QString::number(maxPages));

    m_headerLables.clear();
    auto stringlabels = m_db.getTableFieldStrings(m_table_name.toStdString());
    for (int i = 0; i < stringlabels.size(); i++)
    {
      m_headerLables.append(QString::fromStdString(stringlabels[i]));
    }
  }
  m_model.setHorizontalHeaderLabels(m_headerLables);
  // 法一
  //  m_db.query(m_table_name.toStdString(), range_index*100,(range_index+1)*100,m_model);
  //  法二
  auto re = m_db.query(m_table_name.toStdString(), range_index * maxShowOnePage, (range_index + 1) * maxShowOnePage);
  for (int i = 0; i < re.size(); i++)
  {
    QList<QStandardItem *> lst;
    for (int j = 0; j < re[i].size(); j++)
    {
      if (re[i][j].length() > 200)
      {
        QStandardItem *item = new QStandardItem(QString("click to view more"));
        QFont font = item->font();
        font.setPointSize(12);
        item->setFont(font);
        lst.push_back(item);
      }
      else
      {
        QStandardItem *item = new QStandardItem(QString::fromStdString(re[i][j]));
        QFont font = item->font();
        font.setPointSize(12);
        item->setFont(font);
        lst.push_back(item);
      }
    }
    m_model.appendRow(lst);
  }
  m_table.setModel(&m_model);
}

void interFace::insert_data()
{
  if (!m_db.checkState())
  {
    QMessageBox myBox;
    myBox.setWindowTitle("警告");
    myBox.setText("请先登陆");
    myBox.setStandardButtons(QMessageBox::Yes);
    myBox.setFont(m_font);
    myBox.exec();
    return;
  }

  QDialog dlg;
  dlg.setWindowTitle("插入数据");
  QFormLayout form(&dlg);

  dlg.setLayout(&form);

  QLabel lb1, lb2, lb3, lb4, lb1_check, lb2_check, lb3_check, lb4_check;

  lb1_check.setStyleSheet(QString("background-color: rgba(0, 244, 0);"));
  lb2_check.setStyleSheet(QString("background-color: rgba(0, 244, 0);"));
  lb3_check.setStyleSheet(QString("background-color: rgba(0, 244, 0);"));
  lb4_check.setStyleSheet(QString("background-color: rgba(0, 244, 0);"));

  QLineEdit ld1, ld2, ld3, ld4;
  QHBoxLayout h1, h2, h3, h4;

  lb1.setText("id");
  lb2.setText("name");
  lb3.setText("password");
  lb4.setText("email");

  h1.addWidget(&lb1);
  h1.addWidget(&ld1);
  h1.addWidget(&lb1_check);

  h2.addWidget(&lb2);
  h2.addWidget(&ld2);
  h2.addWidget(&lb2_check);

  h3.addWidget(&lb3);
  h3.addWidget(&ld3);
  h3.addWidget(&lb3_check);

  h4.addWidget(&lb4);
  h4.addWidget(&ld4);
  h4.addWidget(&lb4_check);

  form.addRow(&h1);
  form.addRow(&h2);
  form.addRow(&h3);
  form.addRow(&h4);

  ld1.setFont(m_font);
  ld2.setFont(m_font);
  ld3.setFont(m_font);
  ld4.setFont(m_font);
  lb1.setFont(m_font);
  lb2.setFont(m_font);
  lb3.setFont(m_font);
  lb4.setFont(m_font);

  const char *id_esp = "^[0-9]*$";
  const char *name_esp = "^[a-zA-Z][a-zA-Z0-9]*$";
  const char *name_chs_esp = "^[\u4e00-\u9fa5]*$";
  const char *email_esp = "[a-zA-Z0-9._%+-]+@[a-zA-Z0-9]+\\.[a-zA-Z]{2,}";
  const char *passwd_esp = "^[a-zA-Z0-9][a-zA-Z0-9._!@#$%&]*$";

  std::regex id_rgx(id_esp);
  std::regex name_rgx(name_esp);
  std::regex name_rgx_chs(name_chs_esp);
  std::regex email_rgx(email_esp);
  std::regex passwd_rgx(passwd_esp);

  bool ld1_state = true;
  bool ld2_state = true;
  bool ld3_state = true;
  bool ld4_state = true;

  connect(&ld1, &QLineEdit::textChanged, this,
          [&]()
          {
            if (!std::regex_search(ld1.text().toStdString(), id_rgx))
            {
              // qDebug() << "wrong passwd syntex";
              ld1_state = false;
              lb1_check.setStyleSheet(QString("background-color: rgb(255, 0, 0);"));
            }
            else
            {
              ld1_state = true;
              lb1_check.setStyleSheet(QString("background-color: rgb(0, 255, 0);"));
            }
          });
  connect(&ld2, &QLineEdit::textChanged, this,
          [&]()
          {
            if (!std::regex_search(ld2.text().toStdString(), name_rgx) && !std::regex_search(ld2.text().toStdString(), name_rgx_chs))
            {
              //  qDebug() << "wrong passwd syntex";
              ld2_state = false;
              lb2_check.setStyleSheet(QString("background-color: rgb(255, 0, 0);"));
            }
            else
            {
              ld2_state = true;
              lb2_check.setStyleSheet(QString("background-color: rgb(0, 255, 0);"));
            }
          });

  connect(&ld3, &QLineEdit::textChanged, this,
          [&]()
          {
            if (!std::regex_search(ld3.text().toStdString(), passwd_rgx))
            {
              ld3_state = false;
              //  qDebug() << "wrong passwd syntex";
              lb3_check.setStyleSheet(QString("background-color: rgb(255, 0, 0);"));
            }
            else
            {
              ld3_state = true;
              lb3_check.setStyleSheet(QString("background-color: rgb(0, 255, 0);"));
            }
          });
  connect(&ld4, &QLineEdit::textChanged, this,
          [&]()
          {
            if (!std::regex_search(ld4.text().toStdString(), email_rgx))
            {
              ld4_state = false;
              //  qDebug() << "wrong email syntex";
              lb4_check.setStyleSheet(QString("background-color: rgb(255, 0, 0);"));
            }
            else
            {
              ld4_state = true;
              lb4_check.setStyleSheet(QString("background-color: rgb(0, 255, 0);"));
            }
          });

  QDialogButtonBox qdgbx(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dlg);

  form.addRow(&qdgbx);

  connect(&qdgbx, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);

  connect(&qdgbx, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

  while (dlg.exec() == QDialog::Accepted)
  {
    int id = ld1.text().toInt();
    std::string user_name = ld2.text().toStdString();
    std::string passwd = ld3.text().toStdString();
    std::string email = ld4.text().toStdString();

    if (!(ld1_state && ld2_state && ld3_state && ld4_state))
    {
      QMessageBox::warning(nullptr, "警告", "输入有误");
      continue;
    }
    else
    {
      std::string order = "INSERT INTO user VALUES (" + std::to_string(id) + ",'" + user_name + "', '" + passwd + "' , '" + email + "')";

      qDebug() << QString::fromStdString(order);
      if (!m_db.implement(order))
      {
        QMessageBox::warning(nullptr, "警告", "保存时发生错误");
      }
      else
      {
        refresh_data();
      }
      return;
    }
  }
}

void interFace::switch_button_clicked()
{
  //处理左右两个快速返回的点击事件
  QPushButton *button = qobject_cast<QPushButton *>(this->sender());
  if (button->objectName() == "left_bt")
  {
    qDebug() << "left cliked";
    m_current_switch_index--;
  }
  else if (button->objectName() == "right_bt")
  {
    qDebug() << "right cliked";
    if (m_current_switch_index >= 0)
    {
      m_current_switch_index++;
    }
  }

  if (m_current_switch_index + 1 > switch_labels.size())
  { // 索引超出 刷新switch table
    m_current_switch_index = m_current_switch_index - 1;
    if (switch_labels[m_current_switch_index].second + 1 < maxPages)
    {
      for (int i = 0; i < switch_labels.size(); i++)
      {
        switch_labels[i].second++;
        switch_labels[i].first->setObjectName(QString("switch_bt_" + QString::number(switch_labels[i].second)));
        switch_labels[i].first->setText(QString::number(switch_labels[i].second + 1));
      }
    }
  }
  else if (m_current_switch_index < 0)
  {
    m_current_switch_index = 0;
    if (switch_labels[0].second > 0)
    {
      for (int i = 0; i < switch_labels.size(); i++)
      {
        switch_labels[i].second--;
        switch_labels[i].first->setObjectName(QString("switch_bt_" + QString::number(switch_labels[i].second)));
        switch_labels[i].first->setText(QString::number(switch_labels[i].second + 1));
      }
    }
  }
  //处理中间 索引按钮的点击事件
  for (int i = 0; i < switch_labels.size(); i++)
  {
    if (switch_labels[i].first == button)
    {
      m_current_switch_index = i;
    }
  }
  qDebug() << m_current_switch_index;
  qDebug() << switch_labels[m_current_switch_index].second;

  //改变按钮样式
  for (int i = 0; i < switch_labels.size(); i++)
  {
    if (i == m_current_switch_index)
    {
      switch_labels[i].first->setStyleSheet(QString("background-color: rgba(200, 200, 200,50)"));
    }
    else
    {
      switch_labels[i].first->setStyleSheet(QString("background-color: rgba(255, 255, 255,50)"));
    }
  }
  refresh_data();
}


void interFace::switch_button_mouseWheelRolled(int delta)
{
  if(delta<0){
    m_current_switch_index++;
  }
  else{
    m_current_switch_index--;
  }

  if (m_current_switch_index + 1 > switch_labels.size())
  { // 索引超出 刷新switch table
    m_current_switch_index = m_current_switch_index - 1;
    if (switch_labels[m_current_switch_index].second + 1 < maxPages)
    {
      for (int i = 0; i < switch_labels.size(); i++)
      {
        switch_labels[i].second++;
        switch_labels[i].first->setObjectName(QString("switch_bt_" + QString::number(switch_labels[i].second)));
        switch_labels[i].first->setText(QString::number(switch_labels[i].second + 1));
      }
    }
  }
  else if (m_current_switch_index < 0)
  {
    m_current_switch_index = 0;
    if (switch_labels[0].second > 0)
    {
      for (int i = 0; i < switch_labels.size(); i++)
      {
        switch_labels[i].second--;
        switch_labels[i].first->setObjectName(QString("switch_bt_" + QString::number(switch_labels[i].second)));
        switch_labels[i].first->setText(QString::number(switch_labels[i].second + 1));
      }
    }
  }


  //改变按钮样式
  for (int i = 0; i < switch_labels.size(); i++)
  {
    if (i == m_current_switch_index)
    {
      switch_labels[i].first->setStyleSheet(QString("background-color: rgba(200, 200, 200,50)"));
    }
    else
    {
      switch_labels[i].first->setStyleSheet(QString("background-color: rgba(255, 255, 255,50)"));
    }
  }
  refresh_data();
}

void interFace::show_hidden_data(const QModelIndex &index)
{

  QDialog big_data_frame;
  QTreeWidget treeWiget;

  QTextBrowser data_browser;
  
  QVBoxLayout vlb;

  big_data_frame.resize(1200, 600);
  big_data_frame.setLayout(&vlb);
  auto re = m_db.getSpecificData(m_table_name.toStdString(), index.row() + switch_labels[m_current_switch_index].second * maxShowOnePage, index.column());

  if (getJsonData(re, treeWiget))
  { // 如果是json的字符串 就解析
    vlb.addWidget(&treeWiget);
  }
  else
  {
    QString text = QString::fromStdString(re);
    if (checkUrl(text))
    {

    }
    vlb.addWidget(&data_browser);
    data_browser.setText(text);
    data_browser.setFont(m_font);
    data_browser.setOpenExternalLinks(true);
  }

  big_data_frame.setWindowTitle(m_headerLables[index.column()]);

  big_data_frame.exec();
}

void interFace::maxButtonEnter()
{
  QPushButton *button = qobject_cast<QPushButton *>(this->sender());
  if (button->objectName() == "maxleft")
  {
    button->setText("<<");
  }
  else if (button->objectName() == "maxright")
  {
    button->setText(">>");
  }
}

void interFace::maxButtonLeave()
{
  QPushButton *button = qobject_cast<QPushButton *>(this->sender());
  if (button->objectName() == "maxleft")
  {
    button->setText("1");
  }
  else if (button->objectName() == "maxright")
  {
    if (data_rows <= -1)
    {
      button->setText("1");
    }
    else
    {
      button->setText(QString::number(maxPages));
    }
  }
}

void interFace::maxButtonClicked()
{
  QPushButton *button = qobject_cast<QPushButton *>(this->sender());

  int maxleft_index = 0;
  if (button->objectName() == "maxleft")
  {
    m_current_switch_index = 0;
  }
  else if (button->objectName() == "maxright")
  {
    m_current_switch_index = 4;
    maxleft_index = maxPages - 5;
    if (maxleft_index <= 0)
    {
      maxleft_index = 0;
    }
  }

  for (int i = 0; i < switch_labels.size(); i++)
  {
    if (i == m_current_switch_index)
    {
      switch_labels[i].first->setStyleSheet(QString("background-color: rgba(200, 200, 200,50)"));
    }
    else
    {
      switch_labels[i].first->setStyleSheet(QString("background-color: rgba(255, 255, 255,50)"));
    }
    switch_labels[i].second = maxleft_index;
    switch_labels[i].first->setObjectName(QString("switch_bt_" + QString::number(switch_labels[i].second)));
    switch_labels[i].first->setText(QString::number(switch_labels[i].second + 1));
    maxleft_index++;
  }

  refresh_data();
}

bool interFace::getJsonData(std::string &str, QTreeWidget &treeWiget)
{
  Json::Reader data_reader;
  Json::Value js_value;

  if (!data_reader.parse(str, js_value))
  {
    qDebug() << "error";
    return false;
  }

  std::function<void(QTreeWidgetItem *, const Json::Value &)> iter_func = [&](QTreeWidgetItem *parent, const Json::Value &value)
  {
    for (auto it = value.begin(); it != value.end(); ++it)
    {
      QTreeWidgetItem *item = new QTreeWidgetItem();
    
      item->setText(0, QString::fromStdString(it.key().asString()));
      QFont font = item->font(0);
      font.setPointSize(12);
      item->setFont(0, font);
      if (it->isObject() || it->isArray())
      {
        iter_func(item, *it);
      }
      else
      {
        QString text = QString::fromStdString(it->asString());
        item->setText(1, text);
        QFont font = item->font(1);
        font.setPointSize(12);
        item->setFont(1, font);
        
      }
      item->setFlags(item->flags() | Qt::ItemIsEditable);
      parent->insertChild(0, item);
    }
  };

  treeWiget.setColumnCount(2);
  treeWiget.setColumnWidth(0, 300);
  treeWiget.setColumnWidth(1, 800);

  connect(&treeWiget, &QTreeWidget::itemDoubleClicked, this, [&](QTreeWidgetItem *item, int column)
          {
            QString label = item->text(0);
            if (column == 0)
            {
              return;
            }
            QString text = item->text(column);
            if (checkUrl(text))
            {

            }
            QDialog data_frame;
            data_frame.setWindowTitle(label);
            QTextBrowser browser;
            QVBoxLayout vl;
            vl.addWidget(&browser);
            data_frame.setLayout(&vl);

            browser.setText(text);
            data_frame.exec();
          });

  QTreeWidgetItem *rootItem = new QTreeWidgetItem(&treeWiget);


  rootItem->setText(0, "root");
  QFont font = rootItem->font(0);
  font.setPointSize(16);
  rootItem->setFont(0, font);

  iter_func(rootItem, js_value);

  // 方法二
  //  treeWiget.setColumnCount(2);
  //  treeWiget.setColumnWidth(0, 300);
  //  treeWiget.setColumnWidth(1, 800);
  //  QTreeWidgetItem *rootItem = new QTreeWidgetItem(&treeWiget);
  //  rootItem->setText(0, "root");

  // QTreeWidgetItem *current_root = rootItem;
  // QTreeWidgetItem *last_obj_root = rootItem;
  // QStack<QTreeWidgetItem *> rootStacks;
  // rootStacks.push(rootItem);
  // bool isTouchEnd = false;
  // int last_obj_or_arr_size = 0;

  // QStack<Json::Value::iterator> json_value_stk;
  // for (auto it = js_value.begin(); it != js_value.end(); ++it)
  // {
  //   json_value_stk.push(it);
  // }
  // while (!json_value_stk.empty())
  // {
  //   auto it = json_value_stk.top();
  //   json_value_stk.pop();
  //   qDebug() << "it size: " << it->size();

  //   if (it->type() >= 0 && it->type() <= 5) // 是null int uint float string bool 类型
  //   {
  //     qDebug() << "================";
  //     qDebug() << "Key : " << QString::fromStdString(it.key().asString()) << " Value: " << QString::fromStdString(it->asString());
  //     QTreeWidgetItem *childItem = new QTreeWidgetItem(rootStacks.top());
  //     childItem->setText(0, QString::fromStdString(it.key().asString()));
  //     childItem->setText(1, QString::fromStdString(it->asString()));
  //   }
  //   else
  //   { // 是array object类型
  //     qDebug() << "++++++++++++++++++++++++++++++++++++++++++++++";
  //     qDebug() << "last_obj_or_arr_size: " << last_obj_or_arr_size;
  //     if (last_obj_or_arr_size > 0)
  //     {
  //       last_obj_or_arr_size--;
  //     }

  //     QStack<Json::Value::iterator> temp_stk;

  //     QTreeWidgetItem *root_new = new QTreeWidgetItem(rootStacks.top());
  //     root_new->setText(0, QString::fromStdString(it.key().asString()));

  //     rootStacks.push(root_new);

  //     last_obj_root = root_new;
  //     qDebug() << "isObject or Array"; //{  }
  //     if (it->isString())
  //     {
  //       qDebug() << "Key : " << QString::fromStdString(it.key().asString()) << " Value: " << QString::fromStdString(it->asString());
  //     }
  //     else
  //     {
  //       qDebug() << "Key : " << QString::fromStdString(it.key().asString());
  //     }

  //     int inner_size = it->size();

  //     int obj_or_arr_size = 0;
  //     for (auto inner_it = it->begin(); inner_it != it->end(); ++inner_it)
  //     {
  //       qDebug() << "------------------------------";
  //       if (inner_it->type() >= 0 && inner_it->type() <= 5)
  //       {
  //         qDebug() << "Key : " << QString::fromStdString(inner_it.key().asString()) << " Value: " << QString::fromStdString(inner_it->asString());
  //         QTreeWidgetItem *childItem = new QTreeWidgetItem(rootStacks.top());
  //         childItem->setText(0, QString::fromStdString(inner_it.key().asString()));
  //         childItem->setText(1, QString::fromStdString(inner_it->asString()));
  //         --inner_size;
  //       }
  //       else
  //       {
  //         qDebug() << "is object or Array";
  //         obj_or_arr_size++;
  //         temp_stk.push(inner_it);
  //       }
  //     }
  //     last_obj_or_arr_size = obj_or_arr_size == 0 ? last_obj_or_arr_size : obj_or_arr_size;
  //     if (inner_size <= 0)
  //     {
  //       isTouchEnd = true;
  //     }

  //     if (isTouchEnd)
  //     {
  //       qDebug() << "到底 ";
  //       rootStacks.pop();
  //       if(last_obj_or_arr_size<=0){
  //         rootStacks.pop();
  //         rootStacks.pop();
  //       }
  //       isTouchEnd = false;
  //     }

  //     while (!temp_stk.empty())
  //     {
  //       json_value_stk.push(temp_stk.top());
  //       temp_stk.pop();
  //     }
  //   }
  // }

  return true;
}


bool interFace::checkUrl(QString &str)
{
  QRegExp urlRegExp("(http(s)?://\\S+)");
  if(urlRegExp.indexIn(str)!=-1)
  {
    qDebug() << "url";
    str = "<a href=\"" + str + "\">" + str + "</a>";
    return true;
  }
  return false;
}