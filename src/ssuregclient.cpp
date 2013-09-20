/**
 * @file ssuregclient.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Juha Kallioinen <juha.kallioinen@jollamobile.com>
 * @date 2013
 */

#include <QCoreApplication>
#include "ssuregclient.h"

SsuRegClient::SsuRegClient(): QObject(),
                              _state(Idle),
                              _option(OP_Register)
{
  connect(this, SIGNAL(done()), QCoreApplication::instance(),
          SLOT(quit()), Qt::DirectConnection);
  connect(&_ssu, SIGNAL(done()), this, SLOT(handleResponse()));
}

QString SsuRegClient::printOption(Option op)
{
  switch (op) {
  case OP_Register:
    return "Register";
    break;
  default:
    return "Unknown";
    break;
  }
}

void SsuRegClient::handleResponse()
{
  QTextStream qout(stdout);

  if (_ssu.error()) {
    qout << printOption(_option) << " failed: " << _ssu.lastError() << endl;
    QCoreApplication::exit(1);
  } else {
    qout << printOption(_option) << " successful" << endl;
    QCoreApplication::exit(0);
  }
}

void SsuRegClient::optRegister(const QString& username, const QString& password)
{
  _ssu.sendRegistration(username, password);

  // set state to wait for the response
  _state = Busy;
}

void SsuRegClient::run()
{
  QTextStream qout(stdout);

  QString username, password;
  QStringList arguments = QCoreApplication::arguments();

  for (int i=0; i < arguments.size(); ++i) {
    if (arguments.at(i) == "-u") {
      if ((++i) < arguments.size()) {
        username = arguments.at(i);
      }
    }
    else if (arguments.at(i) == "-p") {
      if ((++i)  < arguments.size()) {
        password = arguments.at(i);
      }
    }
    else if (arguments.at(i) == "-s") {
      _option = OP_Status;
    }
    else if (arguments.at(i) == "-d") {
      _option = OP_Domain;
    }
  }

  switch (_option) {
  case OP_Register:
    if (username.isEmpty() || password.isEmpty()) {
      usage();
      return;
    }
    optRegister(username, password);
    break;

  case OP_Status:
    if (_ssu.isRegistered())
      qout << "registered" << endl;
    else
      qout << "not-registered" << endl;
    break;

  case OP_Domain:
    qout << _ssu.domain() << endl;
    break;

  default:
    usage();
    return;
  }

  // functions that need to wait for a response from ssu should set a flag so
  // we can do default exit catchall here
  if (_state == Idle) {
    QCoreApplication::exit(0);
  }
  else if (_state == UserError) {
    usage();
  }
}

void SsuRegClient::usage()
{
  QTextStream qout(stderr);
  qout << "Usage: sdk-register [-u <username> -p <password>] [-s] [-d]" << endl
       << "       -u <uname> -p <password>   register this device" << endl
       << "       -s                         print out ssu registration status" << endl
       << "       -d                         print out ssu domain" << endl;
  qout.flush();
  QCoreApplication::exit(1);
}
