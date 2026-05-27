#include "src/qtdbus/SystemInformation.h"

#include <QObject>

namespace qtdbusi
{

SystemInformation::SystemInformation(QObject* parent) : QObject{parent} {}

SystemInformation::~SystemInformation() = default;

void SystemInformation::notifyChanged() { emit changed(); }

}  // namespace qtdbusi
