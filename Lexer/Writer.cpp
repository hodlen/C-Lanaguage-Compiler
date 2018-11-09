#include "Writer.h"

bool Writer::openOutputFile (char *output) {
  if (strcmp (&output[strlen (output) - 4], ".csv") != 0 ||
    (outfile = fopen (output, "w")) == NULL) { // check whether it's not a .csv file || cannot open
    ErrorNotifier::showError (GlobalError::NO_OUTPUT);
    outfile = stdout;
    return false;
  } else {
    return true;
  }
}


Writer::Writer (char *output) {
  openOutputFile (output);
  symbolList.clear ();
}


Writer::~Writer () {
  for each (PID p in symbolList) {
    switch (p->token) {
    case 401: case 402: //Numbers
      delete p;
      break;
    default: //Others, uses std::string for value
      delete p->unionValue.strValue; // is a std::string*
      delete p;
      break;
    }
  }

  if(outfile != stdout) fclose (outfile);
}

void Writer::addItem (PID newID) {
  symbolList.push_back(newID);
}

void Writer::writeFile () {
  if (outfile != stdout) {
    fprintf (outfile, "%s%s", "**-----This file is generated by Lexer-----**,\n\n", "Token,Value,Line,Offset,\n");
    for each (PID p in symbolList) {
      fprintf (outfile, "%3d,", p->token);
      switch (p->token) {
      case 401: //Integers
        fprintf (outfile, "%d,", (int)p->unionValue.numValue);
        break;
      case 402: //Decimals
        fprintf (outfile, "%f,", p->unionValue.numValue);
        break;
      default: // Others, uses std::string
        if (p->token / 100 == 1) {// this is a symbol
          fprintf (outfile, "'%s',", p->unionValue.strValue->c_str ());
        } else {
          fprintf (outfile, "%s,", p->unionValue.strValue->c_str ());
        }
        break;
      }
      fprintf (outfile, "%d,%d,\n", p->line, p->offset);
    }
  } else {//display on the screen
    fprintf (outfile, "**-----Generated by Lexer-----**\n\nSample: <Token,  Value,  (Line, Offset)>\n");
    for each (PID p in symbolList) {
      fprintf (outfile, "<%3d  ", p->token);
      switch (p->token) {
      case 401: //Integers
        fprintf (outfile, "%d  ", (int)p->unionValue.numValue);
        break;
      case 402: //Decimals
        fprintf (outfile, "%f  ", p->unionValue.numValue);
      default: // Others, uses std::string
        fprintf (outfile, "%s  ", p->unionValue.strValue->c_str ());
        break;
      }
      fprintf (outfile, "(%d,%d)>\n", p->line, p->offset);
    }
  }
}

