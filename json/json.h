#pragma once

#include <string>
using std::string;

#include <vector>
#include <map>

using namespace std;

namespace Talex
{

  namespace Json
  {

    class Json
    {

    public:
      enum Type
      {
        json_null = 0,
        json_object,
        json_array,
        json_string,
        json_double,
        json_int,
        json_bool
      };

      Json();
      Json(bool value);
      Json(int value);
      Json(double value);
      Json(const char *value);
      Json(const std::string &value);
      Json(const std::vector<Json> &value);
      Json(const std::map<std::string, Json> &value);
      Json(Type type);
      Json(const Json &other);
      ~Json();

      Type type() const;

      operator bool();
      operator int();
      operator double();
      operator string();
      operator string() const;

      Json &operator[](int index);
      const Json &operator[](int index) const;

      Json &operator[](const char *key);
      const Json &operator[](const char *key) const;

      Json &operator[](const string &key);
      const Json &operator[](const string &key) const;

      Json operator=(const Json &other);
      Json &operator=(bool value);
      Json &operator=(int value);
      Json &operator=(double value);
      Json &operator=(const string &value);
      Json &operator=(const char *value);

      bool operator==(const Json &other);
      bool operator==(bool value);
      bool operator==(int value);
      bool operator==(double value);
      bool operator==(const string &value);
      bool operator==(const char *value);

      bool operator!=(const Json &other);
      bool operator!=(bool value);
      bool operator!=(int value);
      bool operator!=(double value);
      bool operator!=(const string &value);
      bool operator!=(const char *value);

      string str() const;

      void copy(const Json &other);
      void clear();

      int size() const;

      bool empty() const;

      void append(const Json &value);

      typedef std::vector<Json>::iterator iterator;
      typedef std::vector<Json>::const_iterator const_iterator;
      // typedef std::map<string, Json>::iterator iterator;
      // typedef std::map<string, Json>::const_iterator const_iterator;

      // iterator begin();

      // iterator end();

      // const_iterator begin() const;

      // const_iterator end() const;

      iterator begin()
      {
        return m_value.m_array->begin();
      }

      iterator end()
      {
        return m_value.m_array->end();
      }

      const_iterator begin() const
      {
        return m_value.m_array->begin();
      }

      const_iterator end() const
      {
        return m_value.m_array->end();
      }

      bool isNull() const
      {
        return m_type == json_null;
      }

      bool isBool() const
      {
        return m_type == json_bool;
      }

      bool isInt() const
      {
        return m_type == json_int;
      }

      bool isDouble() const
      {
        return m_type == json_double;
      }

      bool isString() const
      {
        return m_type == json_string;
      }

      bool isArray() const
      {
        return m_type == json_array;
      }

      bool isObject() const
      {
        return m_type == json_object;
      }

      bool asBool() const;
      int asInt() const;
      double asDouble() const;
      string asString() const;

      bool has(int index);
      bool has(const char *key);
      bool has(const string &key);

      void remove(int index);
      void remove(const char *key);
      void remove(const string &key);

      const Json &get(int index) const;
      const Json &get(const char *key) const;
      const Json &get(const string &key) const;

      void set(const Json &other);
      void set(bool value);
      void set(int value);
      void set(double value);
      void set(const char *value);
      void set(const string &value);

      static Json const &null();

      void parse(const string &str);
      string toString() const;

    private:
      union Value
      {
        bool m_bool;
        int m_int;
        double m_double;
        std::string *m_string;
        std::vector<Json> *m_array;
        std::map<string, Json> *m_object;
      };

      Type m_type;
      Value m_value;
    };
  }
}
