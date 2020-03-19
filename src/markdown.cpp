//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "markdown.h"
#include "parsers/code.h"
#include "parsers/divider.h"
#include "parsers/header.h"
#include "parsers/list.h"
#include "parsers/paragraph.h"
#include "parsers/table.h"

LineParser AbstractParser::lineParser = LineParser();

namespace Markdown {

DocumentParser::DocumentParser() {
  root = new DOM::Node(DOM::MAIN);
  parsers.emplace_back(new HeaderParser());
  parsers.emplace_back(new DividerParser());
  parsers.emplace_back(new ListParser());
  parsers.emplace_back(new CodeParser());
  parsers.emplace_back(new TableParser());
  parsers.emplace_back(new ParagraphParser());
}

DocumentParser::~DocumentParser() {
  for (auto &p : parsers) {
    delete p;
  }
  delete root;
}

void DocumentParser::parse(char *text) {
  int pos = 0, len = strlen(text);
  while (pos < len) {
    while (pos < len and iscntrl(text[pos])) {
      ++pos;
    }
    if (pos == len) {
      break;
    } else {
      bool flag = false;
      for (auto &p : parsers) {
        auto res = p->parse(text + pos);
        if (res.first != nullptr) {
          root->addChild(res.first);
          pos += res.second;
          flag = true;
          break;
        }
      }
      if (!flag) {
        cerr << "Parse failed at pos " << pos << "." << endl;
        break;
      }
    }
  }
}

} // namespace Markdown