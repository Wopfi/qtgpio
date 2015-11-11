// ==========================================================================
// Qt 5.5 Raspberry Pi GPIO Library
// --------------------------------------------------------------------------
//
// by Thomas Wopfner in 2015
//
// Class for accessing the GPIO on a Raspberry Pi
//
// ==========================================================================

#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>

#include "qtgpio.h"

//! Port directory and file constants
QString IoController::baseGPIOPath_ = "/sys/class/gpio/";
QString IoController::gpioExport_ = "export";
QString IoController::gpioUnexport_ = "unexport";
QString IoController::gpioDirection_ = "direction";
QString IoController::gpioValue_ = "value";


IoController::IoController(QObject *parent) : QObject(parent)
{

}

bool IoController::writeToGPIOFile( const QString file, QString outputData )
{
  QFile exportFile( file );

  if ( exportFile.open( QIODevice::WriteOnly ) )
  {
    QTextStream exportStream( &exportFile );

    exportStream << outputData;

    exportFile.close();

    return true;
   }

  //qDebug() << "Error writing " << file;

  return false;
}

bool IoController::readFromGPIOFile( const QString file, QString &inputData )
{
  QFile inputFile( file );

  if ( inputFile.open( QIODevice::ReadOnly ) )
  {
    QTextStream inputStream( &inputFile );

    inputStream >> inputData;

    inputFile.close();

    return true;
   }

  //qDebug() << "Error reading " << file;

  return false;
}

bool IoController::exportGPIO( int pinNumber )
{
  return writeToGPIOFile( baseGPIOPath_ + gpioExport_, QString::number(pinNumber) );
}

bool IoController::unexportGPIO( int pinNumber )
{
  return writeToGPIOFile( baseGPIOPath_ + gpioUnexport_, QString::number(pinNumber) );
}

bool IoController::setDirection( int pinNumber, bool read )
{
  bool result = false;
  QString path = baseGPIOPath_ + "gpio" + QString::number(pinNumber) + "/" + gpioDirection_;

  if ( read )
    result = writeToGPIOFile( path, "in" );
  else
    result = writeToGPIOFile( path, "out" );

  return result;
}

bool IoController::setValue( int pinNumber, bool value )
{
  bool result = false;
  QString path = baseGPIOPath_ + "gpio" + QString::number(pinNumber) + "/" + gpioValue_;

  if ( value )
    result = writeToGPIOFile( path, "1" );
  else
    result = writeToGPIOFile( path, "0" );

  return result;
}

bool IoController::value( int pinNumber, bool &value )
{
  bool result = false;
  QString data = "";
  QString path = baseGPIOPath_ + "gpio" + QString::number(pinNumber) + "/" + gpioValue_;

  result = readFromGPIOFile( path, data );

  if ( result )
    value = (data == "1");

  return result;
}
