#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>

#include<mysql/mysql.h>

#include<QStandardItemModel>

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

    bool checkState()
    {
        return m_state;
    }
    
    bool disconnect();
    
    int getTableField(const std::string &tableName);

    std::vector<std::vector<std::string>> query(const std::string &tableName,int minIndex,int maxIndex);
    void query(const std::string &tableName, int minIndex, int maxIndex, QStandardItemModel &q_model);

    std::vector<std::string> getTableFieldStrings(const std::string &tableName);

    std::vector<std::string> getTablesStrings();

    std::string getSpecificData(const std::string &tableName,int row,int col);

    void getDataSize(const std::string &tableName,int &row,int &col);

    bool implement(const std::string &sentence);
};