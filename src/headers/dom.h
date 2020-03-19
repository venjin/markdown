//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_DOM_NODE_H_
#define MARKDOWN_SRC_HEADERS_DOM_NODE_H_

#include "common.h"

namespace DOM {
enum Tags {
  BODY,
  MAIN,
  H1,
  H2,
  H3,
  H4,
  H5,
  H6,
  UL,
  OL,
  LI,
  PRE,
  TABLE,
  THEAD,
  TBODY,
  TR,
  TH,
  TD,
  P,
  A,
  IMG,
  CODE,
  SPAN,
  STRONG,
  ITALIC,
  RAW,
};

extern const string HTMLHeader;
extern const string HTMLFooter;
extern const map<enum Tags, string> TagStrings;

class Node {
private:
  enum Tags tag;
  string content;
  map<string, string> attrs;
  vector<Node *> children;

public:
  explicit Node(string content);
  explicit Node(enum Tags tag);
  Node(enum Tags tag, map<string, string> attrs);
  ~Node();
  void addChild(Node *child);
  friend ostream &operator<<(ostream &os, Node &node);
};
} // namespace DOM

#endif // MARKDOWN_SRC_HEADERS_DOM_NODE_H_
