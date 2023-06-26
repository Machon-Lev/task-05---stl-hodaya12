#pragma once
#ifndef FREQUENCIES_H
#define FREQUENCIES_H

#include <map>
#include <string>

void printTopWords(const std::multimap<int, std::string, std::greater<int>>& wordCountMap, int numWords);
int frequencies();

#endif  // FREQUENCIES_H

