/**
 * @file main.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Juha Kallioinen <juha.kallioinen@jollamobile.com>
 * @date 2013
 */

#include <QCoreApplication>
#include <QTimer>
#include <ssu.h>
#include "ssuregclient.h"

int main(int argc, char** argv) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setOrganizationName("Jolla");
  QCoreApplication::setOrganizationDomain("http://www.jollamobile.com");
  QCoreApplication::setApplicationName("sdk-register");

  SsuRegClient rc;
  QTimer::singleShot(0, &rc, SLOT(run()));

  return app.exec();
}
