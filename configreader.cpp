#include "configreader.h"

using namespace Common;

//------------------------------------------------------------------------

ConfigReader::ConfigReader( std::string&& cfgFname ) noexcept( true )
    : _cfgFname( std::forward< std::string >( cfgFname ) ) {}

//------------------------------------------------------------------------
