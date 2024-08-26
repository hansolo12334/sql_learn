#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include <mysql/mysql.h>
#include <regex>
#include <boost/regex.h>
using namespace std;

class DataBase
{
private:
  bool m_state;
  MYSQL *m_connect;
  std::vector<MYSQL_FIELD *> m_fd;
  std::vector<std::string> m_field;
  MYSQL_RES *m_res;
  MYSQL_ROW m_column;

public:
  DataBase();
  ~DataBase();

  bool connect(const std::string &ip, const std::string &name, const std::string &password, const std::string &dataBaseName, int port);

  int getTableField(const std::string &tableName);

  std::vector<std::string> getTableFieldStrings(const std::string &tableName);
  std::vector<string> getTablesStrings();

  std::string query(const std::string &tableName);

  bool implement(const std::string &sentence);
};

DataBase::DataBase()
    : m_state(false), m_res{nullptr}, m_column{nullptr}
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
  if (m_state)
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
}

int DataBase::getTableField(const std::string &tableName)
{
  if (!m_state)
  {
    return -1;
  }

  char query[150];
  // 命令
  sprintf(query, "SHOW COLUMNS FROM %s", tableName.c_str());

  // 执行查询
  if (mysql_query(m_connect, query))
  {
    return -1;
  }
  m_res = mysql_store_result(m_connect);
  if (m_res == nullptr)
  {
    return -1;
  }

  return mysql_affected_rows(m_connect);
}

std::string DataBase::query(const std::string &tableName)
{
  if (!m_state)
  {
    return "";
  }

  int field = getTableField(tableName);

  char query[150];
  sprintf(query, "SELECT * FROM %s", tableName.c_str());

  if (mysql_query(m_connect, query))
  {
    return "";
  }
  m_res = mysql_store_result(m_connect);
  if (!m_res)
  {
    return "";
  }
  // 将查询结果转化为字符串输出
  m_fd.reserve(field);

  m_fd.resize(field);

  for (int i = 0; i < field; i++)
  {
    m_fd[i] = mysql_fetch_field(m_res);
  }
  std::string res = "";
  while (m_column = mysql_fetch_row(m_res))
  {
    for (int i = 0; i < field; i++)
    {
      res += m_column[i];
      res += "\t";
      res += "\n";
    }
  }
  return res;
}

bool DataBase::implement(const std::string &sentence)
{
  if (!m_state)
  {
    return false;
  }

  char query[150];
  sprintf(query, "%s", sentence.c_str());

  if (mysql_query(m_connect, query))
  {
    return false;
  }
  return true;
}

std::vector<std::string> DataBase::getTableFieldStrings(const std::string &tableName)
{
  if (!m_state)
  {
    return {};
  }

  char query[150];
  // 命令
  sprintf(query, "SHOW COLUMNS FROM %s", tableName.c_str());

  // 执行查询
  if (mysql_query(m_connect, query))
  {
    return {};
  }
  m_res = mysql_store_result(m_connect);

  std::cout << m_res << '\n';
  auto field = mysql_affected_rows(m_connect); // 获取标头列数

  std::cout << field << '\n';

  sprintf(query, "SELECT * FROM %s", tableName.c_str());

  if (mysql_query(m_connect, query))
  {
    return {};
  }
  m_res = mysql_store_result(m_connect);
  if (!m_res)
  {
    return {};
  }
  // 将查询结果转化为字符串输出
  m_fd.reserve(field);
  m_field.reserve(field);
  m_fd.resize(field);
  m_field.resize(field);

  for (int i = 0; i < field; i++)
  {
    m_fd[i] = mysql_fetch_field(m_res);
    m_field[i] = m_fd[i]->name;
  }

  return m_field;
}

std::vector<string> DataBase::getTablesStrings()
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

int main()
{
  // func();
  DataBase myDataBase;

  myDataBase.connect("localhost", "hansolo", "dxy6964363", "database_hansolo", 3306);



  auto ree = myDataBase.getTablesStrings();

  for (auto str : ree)
  {
    std::cout << str << '\n';
  }

  // auto re=myDataBase.query("resource");
  // auto re = myDataBase.implement("SHOW COLUMNS FROM resource");
  auto re = myDataBase.getTableFieldStrings("user");
  for (auto str : re)
  {
    std::cout << str << '\n';
  }

  
  // re = myDataBase.implement("INSERT INTO user VALUES (4, 'mark', '122545', 'asdhasi@qq.com')");

  //  myDataBase.implement("insert into students values(" + idStr + ",'" + nameStr + "','" + sexStr + "'," + ageStr + ",'" + telStr + "')");

  // std::cout << re << '\n';

  return 0;
}
