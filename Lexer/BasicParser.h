#pragma once
#include "Global.h"

class BasicParser {
protected:
  PID thisID;

public:
  virtual GPS feedChar (char feed) = 0;
  PID returnPID ();
  BasicParser (int lineNum, int lineOffset);
  BasicParser::BasicParser ();
  virtual ~BasicParser ();
};

BasicParser::BasicParser (int lineNum, int lineOffset) {
  thisID = new struct ID;
  thisID->line = lineNum;
  thisID->offset = lineOffset;
}

BasicParser::BasicParser () {}

BasicParser::~BasicParser () {}

PID BasicParser::returnPID () {
  return thisID;
}

