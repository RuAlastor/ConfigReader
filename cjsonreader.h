#ifndef BaseCJSONReader_H
#define BaseCJSONReader_H

#include "configreader.h"

#include <exception>
#include <string>

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

        virtual errorList parse( dataContainer& )                   noexcept( true ) override = 0;
        virtual errorList parse( std::string&&, dataContainer& )    noexcept( true ) override = 0;

        virtual ~BaseCJSONReader() noexcept( true ) override;

    //------------------------------------------------------------------------

    protected METHODS:
        virtual errorList   _initialize()   noexcept( true ) override;
        virtual errorList   _clear()        noexcept( true ) override;

    //------------------------------------------------------------------------

    private METHODS:
        char* _readFile() noexcept( true );

    //------------------------------------------------------------------------

    protected ATTRIBUTES:
        cJSON*  _json;

    //------------------------------------------------------------------------

    }; // class BaseCJSONReader

    //------------------------------------------------------------------------

    class BaseCJSONReaderException : public std::exception
    {

        //------------------------------------------------------------------------

        #define thisClass BaseCJSONReaderException

        //------------------------------------------------------------------------

    public METHODS:
        explicit thisClass( ConfigReader::errorList errorNum ) noexcept( true ) :
            _errorNumber( errorNum ) {}

        thisClass( const thisClass& )               = default;
        thisClass& operator= ( const thisClass& )   = default;
        thisClass( thisClass&& )                = default;
        thisClass& operator= ( thisClass&& )    = default;

        virtual const char* what() const noexcept( true ) override;

        //------------------------------------------------------------------------

    protected ATTRIBUTES:
        ConfigReader::errorList _errorNumber;

        //------------------------------------------------------------------------

        #undef thisClass

        //------------------------------------------------------------------------

    }; // class BaseCJSONReaderException

    //------------------------------------------------------------------------

} // namespace Common

//------------------------------------------------------------------------

#undef ABSTRACT
#undef ATTRIBUTES
#undef METHODS

#endif // BaseCJSONReader_H
