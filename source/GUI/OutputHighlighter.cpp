#include "OutputHighlighter.h"
#include <QRegularExpression>

// --------------------------------------------------------------------------------------------

OutputHighlighter::OutputHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
  HighlightingRule rule;

  rule.keywords << "Syntax error[^\n]*";
  rule.format.setFontWeight(QFont::Bold);
  rule.format.setForeground(Qt::red);
  highlightingRules.append(rule);
  rule.keywords.clear();

  rule.keywords << "Warning[^\n]*";
  rule.format.setFontWeight(QFont::Bold);
  rule.format.setForeground(QColor(170, 150, 30));
  highlightingRules.append(rule);
  rule.keywords.clear();
}

// --------------------------------------------------------------------------------------------

void OutputHighlighter::highlightBlock(const QString &text) {
  HighlightingRule rule;
  QString keyword;
  foreach (rule, highlightingRules) {
    foreach (keyword, rule.keywords) {
      QRegularExpression expression(keyword);
      // int index = text.indexOf(expression);
      QRegularExpressionMatchIterator i = expression.globalMatch(text);
      if (i.hasNext()) {
//      if (index >= 0) {
//        int length = expression.matchedLength();
        int index = text.indexOf(expression);
        QRegularExpressionMatch match = i.next();
        int length = match.capturedLength();
        setFormat(index, length, rule.format);
      }
    }
  }
}

// --------------------------------------------------------------------------------------------
