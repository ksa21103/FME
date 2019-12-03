./tests - folder contains batch files with commands and pattern results;

./Google_tests - folder contain Google test system, included as submodule; 

For run Google tests, please setup Working folder as $PROJECT_DIR$ in Edit configurations dialog for Google_Tests_run configuration.

Format of command line:
1) FME  < (some input stream) - read and process data from specified input stream;
2) FME (batch file name) - read and process data from specified file name;