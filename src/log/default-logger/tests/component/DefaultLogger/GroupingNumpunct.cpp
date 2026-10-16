#include "GroupingNumpunct.h"

#include <string>

char GroupingNumpunct::do_thousands_sep() const { return ','; }

std::string GroupingNumpunct::do_grouping() const { return "\3"; }
