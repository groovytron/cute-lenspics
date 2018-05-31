#ifndef LENS_H
#define LENS_H

#include <QString>

class Lens
{
public:
    Lens(QString serialNumber, QString diopter, QString expirationDate);
    Lens(const Lens &lens);
    QString getSerialNumber() const;
    QString getDiopter() const;
    QString getExpirationDate() const;
    bool operator==(const Lens &otherLens) const;
private:
    QString serialNumber;
    QString diopter;
    QString expirationDate;
};

#endif // LENS_H
