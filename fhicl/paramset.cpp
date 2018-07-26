/*******************
 * paramset.cpp
 *
 *
*******************/
#include <string>
#include <any>
#include <map>
#include "paramset.h"
#include "extendedvalue.h"

bool paramset::is_empty(){ 
  return container.empty(); 
}

std::string paramset::get_id() {
  //get sha1 or md5 hash of container
  return "lol";
}

void paramset::add(std::string key, extendedvalue value){
  container[key] = value;
}

void paramset::merge(paramset const& other){
  container.merge(other.container);
}

bool paramset::erase(std::string const& key, std::string const& loc){
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

}

std::map<std::string, std::string> getComments(bool strip = true) const{
  std::map<str::string, std::string> out;
  
}
