#ifndef ConfigReader_H
#define ConfigReader_H

#include <string>
#include <utility>

#define ABSTRACT
#define ATTRIBUTES
#define METHODS

//------------------------------------------------------------------------

namespace Common
{

    //------------------------------------------------------------------------

    ABSTRACT class ConfigReader
    {

    //------------------------------------------------------------------------

    public ATTRIBUTES:
        using dataContainer = std::string;

        enum errorList
        {
            undefinedError  = -1,
            noError         = 0,
            initError       = 100,
            readingError    = 200,
            parseError      = 300
        };

    //------------------------------------------------------------------------

    public METHODS:
        ConfigReader()  = default;
        explicit ConfigReader( std::string&& cfgFname ) noexcept( true )
            : _cfgFname( std::forward< std::string >( cfgFname ) ) {}

        ConfigReader            ( const ConfigReader& ) = delete;
        ConfigReader& operator= ( const ConfigReader& ) = delete;
        ConfigReader            ( ConfigReader&& ) = delete;
        ConfigReader& operator= ( ConfigReader&& ) = delete;

        virtual errorList parse( dataContainer& )                   noexcept( true ) = 0;
        virtual errorList parse( std::string&&, dataContainer& )    noexcept( true ) = 0;

        virtual ~ConfigReader() = default;

    //------------------------------------------------------------------------

    protected METHODS:
        virtual errorList   _initialize() noexcept( true ) = 0;
        virtual char*       _readFile()   noexcept( true ) = 0;
        virtual errorList   _clear()      noexcept( true ) = 0;

    //------------------------------------------------------------------------

    protected ATTRIBUTES:
        std::string _cfgFname;

    //------------------------------------------------------------------------

    }; // class ConfigReader

    //------------------------------------------------------------------------

} // namespace Common

//------------------------------------------------------------------------

#undef ABSTRACT
#undef ATTRIBUTES
#undef METHODS

#endif // ConfigReader_H
