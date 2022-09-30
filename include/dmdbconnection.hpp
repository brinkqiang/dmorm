#pragma once
#include <functional>
#include <memory>
#include <mutex>
#include "dmresultset.hpp"

namespace gdp
{
    namespace db
    {

        class DBConnection
        {
        public:
            DBConnection(const DBConnection&) = delete;
            DBConnection& operator=(const DBConnection&) = delete;
            DBConnection() {}

            ~DBConnection()
            {
                m_connected = false;
                mysql_close(&m_mysql);
                mysql_thread_end();
            }

            int init(const std::string& db = "", const std::string& user = "root",
                const std::string& passwd = "",
                const std::string& host = "localhost", int port = 3306,
                unsigned int timeout = 10)

            {
                static std::once_flag flag;
                std::call_once(flag, []()
                {
                    mysql_library_init(0, nullptr, nullptr);
                });

                mysql_init(&m_mysql);
                mysql_thread_init();

                //重连
                char reconnect = 1;
                mysql_options(&m_mysql, MYSQL_OPT_RECONNECT, &reconnect);
                //超时
                mysql_options(&m_mysql, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);
                mysql_options(&m_mysql, MYSQL_OPT_READ_TIMEOUT, &timeout);
                mysql_options(&m_mysql, MYSQL_OPT_WRITE_TIMEOUT, &timeout);
                //编码
                mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "utf8");

                MYSQL* res = mysql_real_connect(&m_mysql, host.c_str(), user.c_str(),
                    passwd.c_str(), db.c_str(), port, NULL, 0);

                if (res)
                {
                    m_connected = true;
                    dlog("connect to server %s:%s@%s:%d success", user.c_str(),
                        "******", host.c_str(), port);
                }
                else
                {
                    elog("failed to connect to database error: %s\n", mysql_error(&m_mysql));
                }

                return res != nullptr;
            }

            bool use(const std::string& db)
            {
                if (!this->is_connected())
                {
                    return false;
                }

                int ret = mysql_select_db(&m_mysql, db.c_str());

                if (ret != 0)
                {
                    elog("execute query  error %s\n", mysql_error(&m_mysql));
                }

                return ret == 0;
            }

            bool is_connected()
            {
                return m_connected;
            }

            // execute sql without result
            bool execute(const std::string& sql)
            {
                if (!this->is_connected())
                {
                    return false;
                }

                dlog("execute query :%s ", sql.c_str());
                int ret = mysql_real_query(&m_mysql, sql.c_str(), sql.size());

                if (ret != 0)
                {
                    elog("execute query error: %s\n", mysql_error(&m_mysql));
                }

                return ret == 0;
            }

            ResultSetPtr query(const std::string& sql)
            {
                if (!this->is_connected())
                {
                    return nullptr;
                }

                int ret = mysql_real_query(&m_mysql, sql.c_str(), sql.size());

                if (ret != 0)
                {
                    elog("execute query error: %s\n", mysql_error(&m_mysql));
                    return nullptr;
                }

                MYSQL_RES* res = mysql_store_result(&m_mysql);
                ResultSetPtr rset = std::make_shared<ResultSet>(res);
                return rset;
            }

            my_ulonglong get_insert_id()
            {
                if (!this->is_connected())
                {
                    return my_ulonglong(-1);
                }

                return mysql_insert_id(&m_mysql);
            }

        private:
            bool m_connected = false;
            MYSQL m_mysql;
        };

        typedef std::shared_ptr<DBConnection> DBConnectionPtr;

    }  // namespace db
}  // namespace gdp
