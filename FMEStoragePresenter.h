//
// Created by Копиенко Сергей on 30.11.2019.
//

#ifndef FME_FMESTORAGEPRESENTER_H
#define FME_FMESTORAGEPRESENTER_H

#include <iosfwd>
#include "FMEStorage.h"

class FMEStoragePresenter
{
public:

    FMEStoragePresenter(std::ostream& os);

    void show(const FMEStorage& disk);

private:

    void show(const EntryFolder& folder, const std::string& prefix);

private:

    std::ostream& m_os;
};


#endif //FME_FMESTORAGEPRESENTER_H
