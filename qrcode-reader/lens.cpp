#include "lens.h"

Lens::Lens(QString serialNumber, QString diopter, QString expirationDate)
{
    this->serialNumber = serialNumber;
    this->diopter = diopter;
    this->expirationDate = expirationDate;
}

Lens::Lens(const Lens &lens)
{
    this->serialNumber = lens.serialNumber;
    this->diopter = lens.diopter;
    this->expirationDate = lens.expirationDate;
}

QString Lens::getSerialNumber() const
{
    return this->serialNumber;
}

QString Lens::getDiopter() const
{
    return this->diopter;
}

QString Lens::getExpirationDate() const
{
    return this->expirationDate;
}

bool Lens::operator==(const Lens &otherLens) const
{
    return otherLens.getSerialNumber() == this->serialNumber;
}
