#pragma once

#include <string>

class BaseActor {
 public:
  virtual ~BaseActor() {}
  virtual std::string Operation() const = 0;
};