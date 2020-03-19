//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "dom.h"
#include "common.h"

namespace DOM {

const string HTMLHeader = R"(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>Markdown HTML</title>
  <link href="https://cdn.bootcss.com/twitter-bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet">
  <link href="https://cdn.bootcss.com/highlight.js/9.15.10/styles/default.min.css" rel="stylesheet">
</head>
<body>
  <div class="container my-5">
)";

const string HTMLFooter = R"(
  </div>
  <script src="https://cdn.bootcss.com/twitter-bootstrap/4.4.1/js/bootstrap.bundle.min.js"></script>
  <script src="https://cdn.bootcss.com/highlight.js/9.18.1/highlight.min.js"></script>
  <script>hljs.initHighlightingOnLoad();</script>
</body>
</html>)";

const map<enum Tags, string> TagStrings{
    {BODY, "body"}, {MAIN, "main"}, {H1, "h1"},     {H2, "h2"},
    {H3, "h3"},     {H4, "h4"},     {H5, "h5"},     {H6, "h6"},
    {UL, "ul"},     {OL, "ol"},     {LI, "li"},     {PRE, "pre"},
    {P, "p"},       {A, "a"},       {CODE, "code"}, {STRONG, "strong"},
    {ITALIC, "i"},  {RAW, "raw"},
};

Node::Node(string content) : content(move(content)) {
  tag = RAW;
  attrs = map<string, string>();
  children = vector<Node *>();
}

Node::Node(enum Tags tag) : tag(tag) {
  attrs = map<string, string>();
  children = vector<Node *>();
}

Node::Node(enum Tags tag, map<string, string> attrs)
    : tag(tag), attrs(move(attrs)) {
  children = vector<Node *>();
}

void Node::addChild(Node *child) { children.emplace_back(child); }

ostream &operator<<(ostream &os, Node &node) {
  if (node.tag == RAW) {
    os << node.content;
    for (auto &child : node.children) {
      os << *child;
    }
  } else {
    os << "<" << TagStrings.at(node.tag);
    for (auto &attr : node.attrs) {
      os << " " << attr.first << "=\"" << attr.second << "\"";
    }
    os << ">";
    for (auto &child : node.children) {
      os << *child;
    }
    os << "</" << TagStrings.at(node.tag) << ">";
  }
  return os;
}

} // namespace DOM
