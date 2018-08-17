// ===========================
//
// intermTable.h
//
// ===========================

#include "extendedvalue.h"

#include <string>
#include <map>
#include <any>

class intermTable{
public:
  
  // observers
  bool is_empty() const;
  std::string get_id() const;  

  // modifiers
  void add(std::string, extendedvalue);
  void merge(intermTable const& other);

  // deleter
  bool erase(std::string const& key);

  // comparators
  bool operator==(intermTable const& other) const;
  bool operator!=(intermTable const& other) const;

  // converter
  std::map<std::string, std::any> getConfig(bool as_string = true) const;
  std::map<std::string, std::string> getComments(bool strip = true) const;


private:
  std::map<std::string, extendedvalue> container;
  
};    
