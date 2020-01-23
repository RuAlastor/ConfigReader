#ifndef XMLREADER_H
#define XMLREADER_H

#include "configreader.h"

#include <exception>
#include <string>

#define ABSTRACT
#define EXCEPTION
#define ATTRIBUTES
#define METHODS

//------------------------------------------------------------------------

namespace xmlpp
{ class DomParser; }

//------------------------------------------------------------------------


namespace Common
{

    //------------------------------------------------------------------------

    ABSTRACT class BaseXMLReader : Common::ConfigReader
    {

    //------------------------------------------------------------------------

    public METHODS:
        BaseXMLReader() noexcept( false );
        explicit BaseXMLReader( std::string&& ) noexcept( false );

        virtual errorList parse( dataContainer& )                   noexcept( true ) override = 0;
        virtual errorList parse( std::string&&, dataContainer& )    noexcept( true ) override = 0;

        virtual ~BaseXMLReader() noexcept( true ) override;

    //------------------------------------------------------------------------

    protected METHODS:
        virtual errorList   _initialize()   noexcept( true ) override;
        virtual errorList   _clear()        noexcept( true ) override;

    //------------------------------------------------------------------------

    protected ATTRIBUTES:
        xmlpp::DomParser* _xml;

    }; // class BaseXMLReader

    //------------------------------------------------------------------------

    class BaseXMLReaderException : public std::exception
    {

        //------------------------------------------------------------------------

        #define thisClass BaseXMLReaderException

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

    }; // class BaseXMLReaderException

    //------------------------------------------------------------------------

    //------------------------------------------------------------------------

} // namespace Common

#undef ABSTRACT
#undef EXCEPTION
#undef ATTRIBUTES
#undef METHODS

#endif // XMLREADER_H
