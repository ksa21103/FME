//
// Created by Копиенко Сергей on 03.12.2019.
//

#ifndef FME_FMEMAIN_H
#define FME_FMEMAIN_H

#include <istream>

#include "FMEStorage.h"

////////////////////////////////////////////////////////////////////////////////
/// class FMEMain - class with main worker function
class FMEMain
{
public:

    /// Main worker function
    /**
     * Worker function of FME application
     * @param streamIn - stream for read source text with FME commands
     * @param streamOut - stream for rite results of processing
     * @param disk - FME disk storage
     * @return result code: 0 if success, -1 if errors
     *
     * @exception std::runtime_error - if unknown command received
     */
    static int worker(std::istream &streamIn, std::ostream &streamOut, FMEStorage &disk);
};

#endif //FME_FMEMAIN_H
