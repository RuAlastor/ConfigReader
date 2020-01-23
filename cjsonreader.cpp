#include "cjsonreader.h"

#include <cstdio>
#include <memory>

extern "C"
{
    #include "cjson.h"
}

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
    { throw BaseCJSONReaderException( localRes ); } \
}

//------------------------------------------------------------------------

using namespace Common;

//------------------------------------------------------------------------

BaseCJSONReader::BaseCJSONReader( std::string&& cjsonName ) noexcept( false )
    : ConfigReader( std::forward< std::string >( cjsonName ) )
{
    auto localRes = errorList::noError;
    runSafelyException( _initialize() );
}

//------------------------------------------------------------------------

BaseCJSONReader::errorList BaseCJSONReader::_initialize() noexcept( true )
{
    auto data = _readFile();
    if ( data == nullptr )
    {
        _cfgFname.clear();
        return errorList::readingError;
    }

    _json = cJSON_Parse( data );
    if ( _json == nullptr )
    {
        _cfgFname.clear();
        free( data );
        data = nullptr;
        return errorList::parseError;
    }
    free( data );
    data = nullptr;

    return errorList::noError;
}

//------------------------------------------------------------------------

static inline char* safe_return( std::FILE* file )
{
    if ( file != nullptr )
    { std::fclose( file ); }

    file = nullptr;
    return nullptr;
}

char* BaseCJSONReader::_readFile() noexcept( true )
{
    std::FILE* file = nullptr;
    char* data;
    const char* filename = _cfgFname.c_str();
    long length = 0;
    std::size_t read_chars = 0;

    //open in read binary mode
    file = std::fopen( filename, "rb" );
    if ( file == nullptr )
    { return nullptr; }

    //get the length
    if ( std::fseek( file, 0, SEEK_END ) != 0 )
    { return safe_return( file ); }

    length = std::ftell( file );
    if ( length < 0 )
    { return safe_return( file ); }

    if ( std::fseek( file, 0, SEEK_SET ) != 0 )
    { return safe_return( file ); }

    //allocate content buffer
    data = static_cast< char* >(
               malloc( static_cast< std::size_t >( length ) + sizeof("") ) );
    if ( data == nullptr )
    { return safe_return( file ); }

    //read the file into memory
    read_chars = std::fread( data, sizeof( char ), static_cast< std::size_t >( length ), file );
    if ( static_cast< long >( read_chars ) != length )
    {
        free( data );
        data = nullptr;
        return safe_return(file);
    }
    data[read_chars] = '\0';

    // LEAK FIX
    if ( std::fclose( file ) )
    {
        free( data );
        data = nullptr;
        file = nullptr;
        return nullptr;
    }
    file = nullptr;

    return data;
}

//------------------------------------------------------------------------

BaseCJSONReader::errorList BaseCJSONReader::_clear() noexcept( true )
{
    auto localRes = errorList::noError;

    _cfgFname.clear();

    if ( _json != nullptr )
    {
        cJSON_Delete(_json);
        _json = nullptr;
    }

    return localRes;
}

//------------------------------------------------------------------------

BaseCJSONReader::~BaseCJSONReader() noexcept( true )
{
    /*[[maybe_unused]] auto localRes =*/ _clear();
}

//------------------------------------------------------------------------
