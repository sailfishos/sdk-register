/**
 * @file ssuregclient.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Juha Kallioinen <juha.kallioinen@jollamobile.com>
 * @date 2013
 */

#include <QCoreApplication>
#include <QDebug>

#include "ssuregclient.h"

SsuRegClient::SsuRegClient(): QObject(),
                              state(Idle)
{
  connect(this, SIGNAL(done()), QCoreApplication::instance(),
          SLOT(quit()), Qt::DirectConnection);
  connect(&ssu, SIGNAL(done()), this, SLOT(handleResponse()));
}

void SsuRegClient::handleResponse()
{
  QTextStream qout(stdout);

  if (ssu.error()) {
    qout << "Last operation failed: \n" << ssu.lastError() << endl;
    QCoreApplication::exit(1);
  } else {
    qout << "Operation successful" << endl;
    QCoreApplication::exit(0);
  }
}

void SsuRegClient::optRegister(const QString& username, const QString& password)
{
  ssu.sendRegistration(username, password);

  // set state to wait for the response
  state = Busy;
}

void SsuRegClient::run()
{
  QTextStream qout(stdout);

  QStringList arguments = QCoreApplication::arguments();

  // make sure there's a first argument to parse
  if (arguments.count() < 3) {
    usage();
    return;
  }


  // functions that need to wait for a response from ssu should set a flag so
  // we can do default exit catchall here

  if (state == Idle)
    QCoreApplication::exit(0);

  else if (state == UserError)
    usage();
}

void SsuRegClient::usage()
{
  QTextStream qout(stderr);
  qout << "\nUsage: kala <command> [-command-options] [arguments]" << endl;
  qout.flush();
  QCoreApplication::exit(1);
}
