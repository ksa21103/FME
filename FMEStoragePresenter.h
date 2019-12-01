//
// Created by Копиенко Сергей on 30.11.2019.
//

#ifndef FME_FMESTORAGEPRESENTER_H
#define FME_FMESTORAGEPRESENTER_H

#include <iosfwd>
#include "FMEStorage.h"

////////////////////////////////////////////////////////////////////////////////
/// class FMEStoragePresenter - implements FME storage visualisation
class FMEStoragePresenter
{
public:

    /// Constructor
    ///
    /// \param os - stream for visualisation output
    FMEStoragePresenter(std::ostream& os);

    /// Visualisation of FME disk storage
    ///
    /// \param disk - FME disk storage for visualise
    void show(const FMEStorage& disk);

private:

    /// Recursive level visualisation
    ///
    /// \param folder - folder for visualisation
    /// \param prefix - level prefix
    void show(const EntryFolder& folder, const std::string& prefix);

private:

    std::ostream& m_os;     //< Stream for visualisation output
};

#endif //FME_FMESTORAGEPRESENTER_H
