#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    int result = 0;

    std::string srcCmdLine;

    try
    {
        while (std::getline(std::cin >> std::ws, srcCmdLine))
        {
            if (srcCmdLine.empty())
                continue;

        }
    }
    catch (const std::exception& exc)
    {
        result = -1;
        std::cout << "ERROR: " << exc.what();
    }

    return result;
}
