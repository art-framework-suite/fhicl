/*******************
 * paramset.h
 *
 *
 *
*******************/

#include "extendedvalue.h"

#include <string>
#include <map>
#include <any>

class paramset{
public:
  
  // observers
  bool is_empty() const;
  std::string get_id() const;  

  // modifiers
  void add(std::string, extendedvalue);
  void merge(paramset const& other);

  // deleter
  bool erase(std::string const& key);

  // comparators
  bool operator==(paramset const& other) const;
  bool operator!=(paramset const& other) const;

  // converter
  std::map<std::string, std::any> getConfig(bool as_string = true) const;
  std::map<std::string, std::string> getComments(bool strip = true) const;


private:
  std::map<std::string, extendedvalue> container;
  
};    
