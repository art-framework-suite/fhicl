/*******************
 * intermTable.cpp
 *
 *
*******************/
#include <string>
#include <any>
#include <map>
#include "intermTable.h"
#include "extendedvalue.h"

bool intermTable::is_empty(){ 
  return container.empty(); 
}

std::string intermTable::get_id() {
  //get sha1 or md5 hash of container
  return "lol";
}

void intermTable::add(std::string key, extendedvalue value){
  container[key] = value;
}

void intermTable::merge(intermTable const& other){
  container.merge(other.container);
}

bool intermTable::erase(std::string const& key, std::string const& loc){
  if(container[key]){
    if(container[key].clear(loc)){
      container.erase(key);
      return true;
    } else {
      return false;
    }
  }
}

std::map<std::string, std::any> getConfig(bool as_string = true) const{
  std::map<std::string, std::any> out;
  auto iterator = container.begin();
  std::any curr_val;
  while(iterator != container.end(){
    if(as_string){
      curr_val = iterator->second.getValue();
    } else {
      curr_val = iterator->second.getValue();
    }
    out[iterator->first] = curr_val;
    iterator++;
  }
  return out;
}

std::map<std::string, std::string> getComments(bool strip = true) const{
  std::map<str::string, std::string> out;
  
  return out;
}
