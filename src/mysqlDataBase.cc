#include"mysqlDataBase.hpp"


DataBase::DataBase()
    : m_state(false)
    , m_res{nullptr}
    , m_column{nullptr}
{
    m_connect = new MYSQL();
}

DataBase::~DataBase()
{
    mysql_close(m_connect);
    delete m_connect;
    m_connect = nullptr;
}
bool DataBase::connect(const std::string &ip, const std::string &name, const std::string &password, const std::string &dataBaseName, int port)
{
    if(m_state)
    {
        return false;
    }

    mysql_init(m_connect);

    if (mysql_real_connect(m_connect, ip.c_str(), name.c_str(), password.c_str(), dataBaseName.c_str(), port, NULL, 0))
    {
        m_state = true;
        std::cout << "连接数据库成功\n";
        return true;
    }

    return false;
}

bool DataBase::disconnect()
{
    if(!m_state)
    {
        return false;
    }
    mysql_close(m_connect);
    return true;
}

int DataBase::getTableField(const std::string &tableName)
{
    if(!m_state)
    {
        return -1;
    }

    char query[150];
    //命令
    sprintf(query, "SHOW COLUMNS FROM %s", tableName.c_str());

    //执行查询
    if (mysql_query(m_connect, query))
    {
        return -1;
    }
    m_res = mysql_store_result(m_connect);
    if(m_res==nullptr)
    {
        return -1;
    }

    return mysql_affected_rows(m_connect);
}

//选择一定范围内的数据 -1 -1 是全部数据
std::vector<std::vector<std::string>> DataBase::query(const std::string &tableName,int minIndex,int maxIndex)
{
    if(!m_state)
    {
        return {{}};
    }

    int field = getTableField(tableName);

    char query[150];
    if(minIndex<0&&maxIndex<0){
        sprintf(query, "SELECT * FROM %s", tableName.c_str());
    }
    else if(minIndex>=0 && maxIndex>minIndex){
        sprintf(query, "SELECT * FROM %s LIMIT %d, %d", tableName.c_str(),minIndex,maxIndex-minIndex);
    }
    else{
        return {{}};
    }

    if(mysql_query(m_connect,query))
    {
        return {{}};
    }
    m_res = mysql_store_result(m_connect);
    if(!m_res)
    {
        return {{}};
    }
    // 将查询结果转化为字符串输出
    m_fd.reserve(field);

    m_fd.resize(field);

    for (int i = 0; i < field;i++)
    {
        m_fd[i] = mysql_fetch_field(m_res);
    }
    std::vector<std::vector<std::string>> res ;


    while(m_column=mysql_fetch_row(m_res))
    {
        std::vector<std::string> temp;
        for (int i = 0; i < field; i++)
        {
            temp.push_back(m_column[i]);
        }
        res.push_back(temp);
    }
    return res;
}

void DataBase::query(const std::string &tableName,int minIndex,int maxIndex,QStandardItemModel &q_model)
{
    if(!m_state)
    {
        return ;
    }

    int field = getTableField(tableName);

    char query[150];
    if(minIndex<0&&maxIndex<0){
        sprintf(query, "SELECT * FROM %s", tableName.c_str());
    }
    else if(minIndex>=0 && maxIndex>minIndex){
        sprintf(query, "SELECT * FROM %s LIMIT %d, %d", tableName.c_str(),minIndex,maxIndex-minIndex);
    }
    else{
        return;
    }

    if(mysql_query(m_connect,query))
    {
        return;
    }
    m_res = mysql_store_result(m_connect);
    if(!m_res)
    {
        return;
    }
    // 将查询结果转化为字符串输出
    m_fd.reserve(field);

    m_fd.resize(field);

    for (int i = 0; i < field;i++)
    {
        m_fd[i] = mysql_fetch_field(m_res);
    }
    
    while(m_column=mysql_fetch_row(m_res))
    {
        QList<QStandardItem *> lst;
        for (int i = 0; i < field; i++)
        {
            lst.push_back(new QStandardItem(QString::fromStdString(m_column[i])));
        }
        q_model.appendRow(lst);
    }
}

bool DataBase::implement(const std::string &sentence)
{
    if(!m_state)
    {
        return false;
    }

    char query[150];
    sprintf(query, "%s", sentence.c_str());

    if(mysql_query(m_connect,query))
    {
        return false;
    }
    return true;
}


std::vector<std::string> DataBase::getTableFieldStrings(const std::string &tableName)
{
  if(!m_state)
    {
        return {};
    }

    char query[150];
    //命令
    sprintf(query, "SHOW COLUMNS FROM %s", tableName.c_str());

    //执行查询
    if (mysql_query(m_connect, query))
    {
        return {};
    }
    m_res = mysql_store_result(m_connect);

    std::cout << m_res << '\n';
    auto field = mysql_affected_rows(m_connect); // 获取标头列数

    std::cout << field << '\n'; 

    sprintf(query, "SELECT * FROM %s", tableName.c_str());

    if(mysql_query(m_connect,query))
    {
        return {};
    }
    m_res = mysql_store_result(m_connect);
    if(!m_res)
    {
        return {};
    }
    // 将查询结果转化为字符串输出
    m_fd.reserve(field);
    m_field.reserve(field);
    m_fd.resize(field);
    m_field.resize(field);

    for (int i = 0; i < field;i++){
      m_fd[i] = mysql_fetch_field(m_res);
      m_field[i] = m_fd[i]->name;
    }

    return m_field;
}


std::vector<std::string> DataBase::getTablesStrings()
{
  if (!m_state)
  {
    return {};
  }

  char query[150];
  // 命令
  sprintf(query, "SHOW TABLES");

  if (mysql_query(m_connect, query))
  {
    return {};
  }
  m_res = mysql_store_result(m_connect);
  if (!m_res)
  {
    return {};
  }
  auto field = mysql_affected_rows(m_connect);

  std::cout << field << '\n';

  std::vector<std::string> re;
  for (int i = 0; i < field; i++)
  {     
      re.push_back(*mysql_fetch_row(m_res));
  }

  return re;
}

std::string DataBase::getSpecificData(const std::string &tableName,int row,int col)
{
    if (!m_state)
    {
        return "";
    }

    int field = getTableField(tableName);

    char query[150];
    // 命令
    sprintf(query, "SELECT * FROM %s LIMIT 1 OFFSET %d",tableName.c_str(),row);

    if (mysql_query(m_connect, query))
    {
        return "";
    }

    m_res = mysql_store_result(m_connect);
    if(!m_res)
    {
        return "";
    }

    
    std::string re;
    while (m_column = mysql_fetch_row(m_res))
    {
        QList<QStandardItem *> lst;
        for (int i = 0; i < field; i++)
        {
            
            if (i == col)
            {
                re = m_column[i];
                break;
            }
        }
    }
    return re;
}


void DataBase::getDataSize(const std::string &tableName,int &row,int &col)
{
    if(!m_state)
    {
        return;
    }

    col=getTableField(tableName);

    char query[150];
    // 命令
    sprintf(query, "SELECT COUNT(*) FROM %s",tableName.c_str());
    if (mysql_query(m_connect, query))
    {
        return;
    }

    m_res = mysql_store_result(m_connect);
    if(!m_res)
    {
        return;
    }
    MYSQL_ROW mysqlrow=mysql_fetch_row(m_res);
    if(mysqlrow){
        row = atoi(mysqlrow[0]);
    }
}
