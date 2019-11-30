#include <iostream>
#include <string>

#include "FMEStorage.h"
#include "FMEStoragePresenter.h"

int main(int argc, char** argv)
{
    int result = 0;

    try
    {
        FMEStorage disk;

        std::string srcCmdLine;
        while (std::getline(std::cin >> std::ws, srcCmdLine))
        {
            if (srcCmdLine.empty())
                continue;

        }

        FMEStoragePresenter presenter(std::cout);
        presenter.show(disk);
    }
    catch (const std::exception& exc)
    {
        result = -1;
        std::cout << "ERROR: " << exc.what();
    }

    return result;
}
