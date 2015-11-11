#ifndef QTGPIO_H
#define QTGPIO_H

#include <QObject>

class IoController : public QObject
{
  Q_OBJECT

  public:
    explicit IoController(QObject *parent = 0);

    //! Export Port for using
    bool exportGPIO( int pinNumber );
    //! Unexport Port
    bool unexportGPIO( int pinNumber );
    //! Set the direction (read/write) of the specified port
    bool setDirection( int pinNumber, bool read );
    //! Write to the specified port
    bool setValue( int pinNumber, bool value );
    //! Read from the specified port
    bool value( int pinNumber, bool &value );

  signals:

  public slots:

  private:
    static QString baseGPIOPath_;
    static QString gpioExport_;
    static QString gpioUnexport_;
    static QString gpioDirection_;
    static QString gpioValue_;

    //! Helper function for writing to the GPIO directory
    bool writeToGPIOFile(const QString file, QString outputData);
    //! Helper function for reading from the GPIO directory
    bool readFromGPIOFile(const QString file, QString &inputData);
};

#endif // QTGPIO_H
