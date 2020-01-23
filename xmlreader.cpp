#include "xmlreader.h"

#include <libxml++/libxml++.h>

//------------------------------------------------------------------------

#define runSafelyError( funcToRun )         \
{                                           \
    localRes = funcToRun;                   \
    if ( localRes != errorList::noError )   \
    { return localRes; }                    \
}

#define runSafelyException( funcToRun )                 \
{                                                       \
    localRes = funcToRun;                               \
    if ( localRes != errorList::noError )               \
    { throw BaseXMLReaderException( localRes ); } \
}

//------------------------------------------------------------------------

using namespace Common;
using namespace xmlpp;

//------------------------------------------------------------------------

BaseXMLReader::BaseXMLReader() noexcept( false ) : _xml( nullptr ) {}

//------------------------------------------------------------------------

BaseXMLReader::BaseXMLReader( std::string&& xmlName ) noexcept( false )
    : ConfigReader( std::forward< std::string >( xmlName ) ), _xml( nullptr )
{
    auto localRes = errorList::noError;
    runSafelyException( _initialize() );
}

//------------------------------------------------------------------------

BaseXMLReader::errorList BaseXMLReader::_initialize() noexcept( true )
{
    auto localRes = errorList::noError;
    try
    {
        _xml = new xmlpp::DomParser();
        _xml->parse_file( _cfgFname.c_str() );
    }
    catch (...)
    { localRes = errorList::initError; }

    return  localRes;
}

//------------------------------------------------------------------------

BaseXMLReader::errorList BaseXMLReader::_clear() noexcept( true )
{
    auto localRes = errorList::noError;
    try
    {
        _cfgFname.clear();
        delete _xml;
        _xml = nullptr;
    }
    catch (...)
    { localRes = errorList::undefinedError; }

    return  localRes;
}

//------------------------------------------------------------------------

BaseXMLReader::~BaseXMLReader() noexcept( true )
{
    _clear();
}

//------------------------------------------------------------------------

const char* BaseXMLReaderException::what() const noexcept( true )
{
    switch ( _errorNumber )
    {
    case ConfigReader::errorList::initError:
    { return "Init error!\n"; }
    case ConfigReader::errorList::readingError:
    { return "Reading error!\n"; }
    default:
    { return "Undefined error!\n"; }
    }
}

//------------------------------------------------------------------------

