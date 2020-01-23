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

class DomParser;

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

        virtual errorList parse( dataContainer& )                   noexcept( true ) = 0;
        virtual errorList parse( std::string&&, dataContainer& )    noexcept( true ) = 0;

        virtual ~BaseXMLReader() noexcept( true );

    //------------------------------------------------------------------------

    protected METHODS:
        virtual errorList   _initialize()   noexcept( true ) override;
        virtual char*       _readFile()     noexcept( true ) override;
        virtual errorList   _clear()        noexcept( true ) override;

    //------------------------------------------------------------------------

    protected ATTRIBUTES:
        DomParser* _xml;

    }; // class BaseXMLReader

    //------------------------------------------------------------------------

} // namespace Common

#undef ABSTRACT
#undef ATTRIBUTES
#undef METHODS

#endif // XMLREADER_H
