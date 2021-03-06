//
// Created by Tianyun Zhang on 2020/3/20.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_INLINE_HYPERLINK_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_INLINE_HYPERLINK_H_

#include "parsers/abstract.h"

class InlineHyperlinkParser : public AbstractParser {
public:
  InlineHyperlinkParser() = delete;
  explicit InlineHyperlinkParser(AbstractParser *master) {
    this->master = master;
    this->rule = regex(R"(^\[(.*)\]\((.*)\))", regex::optimize);
  }
  size_t parseInline(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (!regex_search(input, match, rule)) return 0;

    auto hyperlink = new DOM::Node(DOM::ANCHOR, map<string, string> {
        {"href", match[2].str()}
    });
    master->parseInline(hyperlink, match[1].str().c_str(), match[1].length());
    parent->addChild(hyperlink);
    return match.length();
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_INLINE_HYPERLINK_H_
