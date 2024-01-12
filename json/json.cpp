#include "json.h"
#include "Parser.h"

#include <sstream>
#include <stdexcept>

using std::istringstream;
using std::ostringstream;

using namespace Talex::Json;

Json::Json() : m_type(json_null)
{
}

Json::Json(bool value) : m_type(json_bool)
{
  m_value.m_bool = value;
}

Json::Json(int value) : m_type(json_int)
{
  m_value.m_int = value;
}

Json::Json(double value) : m_type(json_double)
{
  m_value.m_double = value;
}

Json::Json(const char *value) : m_type(json_string)
{
  m_value.m_string = new string(value);
}

Json::Json(const std::string &value) : m_type(json_string)
{
  m_value.m_string = new string(value);
}

Json::Json(Type type) : m_type(type)
{
  switch (m_type)
  {
  case json_null:
    break;
  case json_bool:
    m_value.m_bool = false;
    break;
  case json_int:
    m_value.m_int = 0;
    break;
  case json_double:
    m_value.m_double = 0.0;
    break;
  case json_string:
    m_value.m_string = new string();
    break;
  case json_array:
    m_value.m_array = new std::vector<Json>();
    break;
  case json_object:
    m_value.m_object = new std::map<std::string, Json>();
    break;
  default:
    break;
  }
}

Json::Json(const Json &other)
{
  copy(other);
}

Json::~Json()
{
  clear();
}

Json::Type Json::type() const
{
  return m_type;
}

Json::operator bool()
{
  switch (m_type)
  {
  case json_null:
    return false;
  case json_bool:
    return m_value.m_bool;
  case json_int:
    return m_value.m_int != 0;
  case json_double:
    return m_value.m_double != 0.0;
  case json_string:
    return m_value.m_string->length() != 0;
  case json_array:
    return m_value.m_array->size() != 0;
  case json_object:
    return m_value.m_object->size() != 0;
  default:
    return false;
  }
}

Json::operator int()
{
  switch (m_type)
  {
  case json_null:
    return 0;
  case json_bool:
    return m_value.m_bool;
  case json_int:
    return m_value.m_int;
  case json_double:
    return m_value.m_double;
  case json_string:
    return atoi(m_value.m_string->c_str());
  case json_array:
    return m_value.m_array->size();
  case json_object:
    return m_value.m_object->size();
  default:
    return 0;
  }
}

Json::operator double()
{
  switch (m_type)
  {
  case json_null:
    return 0.0;
  case json_bool:
    return m_value.m_bool;
  case json_int:
    return m_value.m_int;
  case json_double:
    return m_value.m_double;
  case json_string:
    return atof(m_value.m_string->c_str());
  case json_array:
    return m_value.m_array->size();
  case json_object:
    return m_value.m_object->size();
  default:
    return 0.0;
  }
}

Json::operator string()
{
  switch (m_type)
  {
  case json_null:
    return "";
  case json_bool:
    return m_value.m_bool ? "true" : "false";
  case json_int:
    return std::to_string(m_value.m_int);
  case json_double:
    return std::to_string(m_value.m_double);
  case json_string:
    return *(m_value.m_string);
  case json_array:
    return std::to_string(m_value.m_array->size());
  case json_object:
    return std::to_string(m_value.m_object->size());
  default:
    return "";
  }
}

Json::operator string() const
{
  return string();
}

Json &Json::operator[](int index)
{
  if (type() == json_null)
  {
    m_type = json_array;
  }

  if (type() != json_array)
  {
    throw std::logic_error("TypeMismatch | Action needs `array` type.");
  }

  if (index < 0)
  {
    throw std::logic_error("IndexOutOfBounds | Index out of range.");
  }

  int size = (*m_value.m_array).size();
  if (index >= size)
  {
    for (int i = size; i <= index; i++)
    {
      (m_value.m_array)
          ->push_back(Json());
    }
  }

  return (*m_value.m_array)[index];
}

const Json &Json::operator[](int index) const
{
  return get(index);
}

const Json &Json::operator[](const char *key) const
{
  return get(key);
}

const Json &Json::operator[](const string &key) const
{
  return get(key);
}

void Json::append(const Json &value)
{
  if (m_type != json_array)
  {
    clear();
    m_type = json_array;
    m_value.m_array = new std::vector<Json>();
  }

  (m_value.m_array)
      ->push_back(value);
}

string Json::str() const
{
  stringstream ss;
  switch (m_type)
  {
  case json_null:
    ss << "null";
    break;
  case json_bool:
    ss << (m_value.m_bool ? "true" : "false");
    break;
  case json_int:
    ss << m_value.m_int;
    break;
  case json_double:
    ss << m_value.m_double;
    break;
  case json_string:
    ss << '\"' << *m_value.m_string << '\"';
    break;
  case json_array:
  {
    ss << "[";
    for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
    {
      if (it != (m_value.m_array)->begin())
      {
        ss << ",";
      }
      ss << it->str();
    }
    ss << "]";
    break;
  }
  case json_object:
  {
    ss << "{";
    for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
    {
      if (it != (m_value.m_object)->begin())
      {
        ss << ",";
      }
      ss << '\"' << it->first << "\":" << it->second.str();
    }
    ss << "}";
    break;
  }
  default:
    break;
  }

  return ss.str();
}

Json &Json::operator[](const char *key)
{
  return (*(this))[string(key)];
}

Json &Json::operator[](const string &key)
{
  if (type() == json_null)
  {
    m_type = json_object;
  }

  if (type() != json_object)
  {
    throw std::logic_error("TypeMismatch | Action needs `object` type.");
  }

  return (*(m_value.m_object))[key];
}

Json Json::operator=(const Json &other)
{
  clear();
  copy(other);

  return *this;
}

Json &Json::operator=(bool value)
{
  Json other(value);
  copy(other);

  return *this;
}

Json &Json::operator=(int value)
{
  Json other(value);
  copy(other);

  return *this;
}

Json &Json::operator=(double value)
{
  Json other(value);
  copy(other);

  return *this;
}

Json &Json::operator=(const string &value)
{
  Json other(value);
  copy(other);

  return *this;
}

Json &Json::operator=(const char *value)
{
  Json other(value);
  copy(other);

  return *this;
}

bool Json::operator==(const Json &other)
{
  if (type() != other.type())
    return false;

  switch (type())
  {
  case json_null:
    return true;
  case json_bool:
    return m_value.m_bool == other.m_value.m_bool;
  case json_int:
    return m_value.m_int == other.m_value.m_int;
  case json_double:
    return m_value.m_double == other.m_value.m_double;
  case json_string:
    return *(m_value.m_string) == *(other.m_value.m_string);
  case json_array:
    // Efficiently compare two vectors
    return m_value.m_array == other.m_value.m_array;
  case json_object:
    // Efficiently compare two vectors
    return m_value.m_object == other.m_value.m_object;
  default:
    return false;
  }
}

bool Json::operator==(bool value)
{
  Json other = value;
  return (*this == other);
}

bool Json::operator==(int value)
{
  Json other = value;
  return (*this == other);
}

bool Json::operator==(double value)
{
  Json other = value;
  return (*this == other);
}

bool Json::operator==(const string &value)
{
  Json other = value;
  return (*this == other);
}

bool Json::operator==(const char *value)
{
  Json other = value;
  return (*this == other);
}

bool Json::operator!=(const Json &other)
{
  return !(*this == other);
}

bool Json::operator!=(bool value)
{
  Json other = value;
  return (*this != other);
}

bool Json::operator!=(int value)
{
  Json other = value;
  return (*this != other);
}

bool Json::operator!=(double value)
{
  Json other = value;
  return (*this != other);
}

bool Json::operator!=(const string &value)
{
  Json other = value;
  return (*this != other);
}

bool Json::operator!=(const char *value)
{
  Json other = string(value);
  return (*this != other);
}

void Json::copy(const Json &other)
{
  switch (other.m_type)
  {
  case json_null:
    m_type = json_null;
    break;
  case json_bool:
    m_type = json_bool;
    m_value.m_bool = other.m_value.m_bool;
    break;
  case json_int:
    m_type = json_int;
    m_value.m_int = other.m_value.m_int;
    break;
  case json_double:
    m_type = json_double;
    m_value.m_double = other.m_value.m_double;
    break;
  case json_string:
    m_type = json_string;
    // Frequently deep copy is needed
    // m_value.m_string = other.m_value.m_string;
    // Avoid frequently deep copy (By reference)
    // Allocate memory and copy string
    m_value.m_string = new string(*other.m_value.m_string);
    break;
  case json_array:
    m_type = json_array;
    m_value.m_array = other.m_value.m_array;
    break;
  case json_object:
    m_type = json_object;
    m_value.m_object = other.m_value.m_object;
    break;
  default:
    break;
  }
}

void Json::clear()
{
  switch (m_type)
  {
  case json_null:
    break;
  case json_bool:
    m_value.m_bool = false;
    break;
  case json_int:
    m_value.m_int = 0;
    break;
  case json_double:
    m_value.m_double = 0.0;
    break;
  case json_string:
    delete m_value.m_string;
    break;
  case json_array:
  {
    for (auto it = m_value.m_array->begin(); it != m_value.m_array->end(); it++)
    {
      it->clear();
    }
    delete m_value.m_array;
    break;
  }
  case json_object:
  {
    for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
    {
      (it->second).clear();
    }
    delete m_value.m_object;
    break;
  }
  default:
    break;
  }

  m_type = json_null;
}

bool Json::asBool() const
{
  if (m_type == json_bool)
  {
    return m_value.m_bool;
  }
  else
    throw new std::logic_error("TypeCastException | type error, target value do not match `bool` type.");
}
int Json::asInt() const
{
  if (m_type == json_int)
  {
    return m_value.m_int;
  }
  else
    throw new std::logic_error("TypeCastException | type error, target value do not match `int` type.");
}

double Json::asDouble() const
{
  if (m_type == json_double)
  {
    return m_value.m_double;
  }
  else
    throw new std::logic_error("TypeCastException | type error, target value do not match `double` type.");
}

string Json::asString() const
{
  if (m_type == json_string)
  {
    return *m_value.m_string;
  }
  else
    throw new std::logic_error("TypeCastException | type error, target value do not match `string` type.");
}

bool Json::has(int index)
{
  switch (m_type)
  {
  case json_array:
    return (m_value.m_array->size() > index);
  default:
    return false;
  }
}

bool Json::has(const char *key)
{
  return has(string(key));
}

bool Json::has(const string &key)
{
  switch (m_type)
  {
  case json_object:
    return (m_value.m_object->find(key) != m_value.m_object->end());
  default:
    return false;
  }
}

void Json::remove(int index)
{
  if (m_type != json_array)
    return;

  if (!has(index))
    return;

  (m_value.m_array)->at(index).clear();
  m_value.m_array->erase(m_value.m_array->begin() + index);
}

void Json::remove(const char *key)
{
  remove(string(key));
}

void Json::remove(const string &key)
{
  if (m_type != json_object)
    return;

  if (!has(key))
    return;

  (*(m_value.m_object))[key].clear();
  (m_value.m_object)->erase(key);
}

int Json::size() const
{
  switch (type())
  {
  case json_array:
    return m_value.m_array->size();
  case json_object:
    return m_value.m_object->size();
  default:
    break;
  }
  throw std::logic_error("TypeMismatch | Action needs `array` or `object` type.");
}

bool Json::empty() const
{
  switch (type())
  {
  case json_null:
    return true;
  case json_array:
    return m_value.m_array->empty();
  case json_object:
    return m_value.m_object->empty();
  default:
    break;
  }
  throw std::logic_error("TypeMismatch | Action needs `array`, `object` or `null` type.");
}

void Json::set(const Json &other)
{
  copy(other);
}

void Json::set(bool value)
{
  clear();

  m_type = json_bool;
  m_value.m_bool = value;
}

void Json::set(int value)
{
  clear();

  m_type = json_int;
  m_value.m_int = value;
}

void Json::set(double value)
{
  clear();

  m_type = json_double;
  m_value.m_double = value;
}

void Json::set(const string &value)
{
  clear();

  m_type = json_string;
  m_value.m_string = new string(value);
}

void Json::set(const char *value)
{
  clear();

  m_type = json_string;
  m_value.m_string = new string(value);
}

Json const &Json::null()
{
  static const Json null;

  return null;
}

void Json::parse(const string &str)
{
  Parser parser;

  parser.load(str);

  *this = parser.parse();
}

string Json::toString() const
{
  ostringstream os;
  switch (type())
  {
  case json_null:
    os << "null";
    break;
  case json_bool:
    if (m_value.m_bool)
    {
      os << "true";
    }
    else
    {
      os << "false";
    }
    break;
  case json_int:
    os << m_value.m_int;
    break;
  case json_double:
    os << m_value.m_double;
    break;
  case json_string:
    os << "\"" << m_value.m_string << "\"";
    break;
  case json_array:
  {
    os << "[";
    for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
    {
      if (it != m_value.m_array->begin())
      {
        os << ",";
      }
      os << (*it).toString();
    }
    os << "]";
  }
  break;
  case json_object:
  {
    os << "{";
    for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
    {
      if (it != m_value.m_object->begin())
      {
        os << ",";
      }
      os << "\"" << it->first << "\":" << it->second.toString();
    }
    os << "}";
    return os.str();
  }
  break;
  default:
    break;
  }

  return os.str();
}

// iterator Json::begin()
// {
//   switch (type())
//   {
//   case json_array:
//     return (m_value.m_array)->begin();
//   case json_object:
//     return (m_value.m_object)->begin();
//   default:
//     throw std::logic_error("TypeMismatch | Action needs `array` or `object` type.");
//   }
// }

// iterator Json::end()
// {
//   switch (type())
//   {
//   case json_array:
//     return m_value.m_array->end();
//   case json_object:
//     return m_value.m_object->end();
//   default:
//     throw std::logic_error("TypeMismatch | Action needs `array` or `object` type.");
//   }
// }

// const_iterator Json::begin() const
// {
//   return const_iterator(m_value.m_array->begin());
// }

// const_iterator Json::end() const
// {
//   return const_iterator(m_value.m_array->end());
// }