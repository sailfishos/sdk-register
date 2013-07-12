/**
 * @file
 * @copyright 2013 Jolla Ltd.
 * @author Juha Kallioinen <juha.kallioinen@jollamobile.com>
 * @date 2013
 */

#ifndef _SSU_REG_CLIENT_H
#define _SSU_REG_CLIENT_H

#include <QObject>
#include <QSettings>
#include <QStringList>
#include <QDebug>

#include <ssu.h>

class SsuRegClient: public QObject {
  Q_OBJECT

  public:
  SsuRegClient();

public slots:
  void run();

private:
  Ssu ssu;
  int state;
  void usage();
  void optRegister(const QString& username, const QString& password);

  enum State {
    Idle,
    Busy,
    UserError
  };

private slots:
  void handleResponse();

signals:
  void done();
};

#endif
