#ifndef BaseCJSONReader_H
#define BaseCJSONReader_H

#include "configreader.h"

#include <exception>

#define ABSTRACT
#define EXCEPTION
#define ATTRIBUTES
#define METHODS

//------------------------------------------------------------------------

struct cJSON;

//------------------------------------------------------------------------

namespace Common
{

    //------------------------------------------------------------------------

    class BaseCJSONReader;
    class BaseCJSONReaderException;

     //------------------------------------------------------------------------

    ABSTRACT class BaseCJSONReader : public Common::ConfigReader
    {

    //------------------------------------------------------------------------

    public METHODS:
        BaseCJSONReader() noexcept( false );
        explicit BaseCJSONReader( std::string&& ) noexcept( false );

        virtual errorList parse( dataContainer& )                   noexcept( true ) = 0;
        virtual errorList parse( std::string&&, dataContainer& )    noexcept( true ) = 0;

        virtual ~BaseCJSONReader() noexcept( true );

    //------------------------------------------------------------------------

    protected METHODS:
        virtual errorList   _initialize() noexcept( true ) override;
        virtual char*       _readFile()   noexcept( true ) override;
        virtual errorList   _clear()      noexcept( true ) override;

    //------------------------------------------------------------------------

    protected ATTRIBUTES:
        cJSON*  _json;

    //------------------------------------------------------------------------

    }; // class BaseCJSONReader

    //------------------------------------------------------------------------

    class BaseCJSONReaderException : public std::exception
    {

    public METHODS:
        explicit BaseCJSONReaderException( ConfigReader::errorList errorNum ) noexcept( true ) :
            _errorNumber( errorNum ) {}

        virtual const char* what() const noexcept( true ) override
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

    protected ATTRIBUTES:
        ConfigReader::errorList _errorNumber;

    }; // class BaseCJSONReaderException

    //------------------------------------------------------------------------

} // namespace Common

//------------------------------------------------------------------------

#undef ABSTRACT
#undef ATTRIBUTES
#undef METHODS

#endif // BaseCJSONReader_H