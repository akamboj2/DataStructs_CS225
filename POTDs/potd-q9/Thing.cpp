// Your code here!
#include"Thing.h"
#include<cstring>
using std::string;
using namespace potd;
Thing::Thing(int x) : props_max_(x){
  properties_= new string[props_max_];
  values_=new string[props_max_];
  props_ct_=0; //properties count will include 0 (value of 3 means there are 4 things in list)
}

Thing::Thing(const Thing & s){
  props_max_=s.props_max_;
  props_ct_=s.props_ct_;
  properties_= new string[props_max_];
  values_=new string[props_max_];
  for (int i=0;i<props_ct_;i++){
    properties_[i]=s.properties_[i];
    values_[i]=s.values_[i];
  }
}

Thing & Thing::operator=(const Thing& s){
  props_max_=s.props_max_;
  props_ct_=s.props_ct_;
  properties_= new string[props_max_];
  values_=new string[props_max_];
  for (int i=0;i<props_ct_;i++){
    properties_[i]=s.properties_[i];
    values_[i]=s.values_[i];
  }
  return *this;
}

Thing::~Thing(){
  delete [] properties_;
  delete [] values_;
}

int Thing::set_property(string p,string v){
  for (int i=0;i<props_ct_;i++){
    if (properties_[i]==p){//if property already exists update its value
      values_[i]=v;
      return i;
    }
  }
  //otherwise add it to the the list
  //but need to check if space available in list
  if (props_ct_>=props_max_) return -1;

  properties_[props_ct_]=p;
  values_[props_ct_]=v;
  return props_ct_++;
}
string Thing::get_property(string name){
  for (int i =0;i<props_ct_;i++){
    if (properties_[i]==name){
      return values_[i];
    }
  }
  return "";
}
