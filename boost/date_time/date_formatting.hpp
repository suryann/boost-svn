#ifndef DATE_TIME_DATE_FORMATTING_HPP___
#define DATE_TIME_DATE_FORMATTING_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/compiler_config.hpp"
#include "boost/lexical_cast.hpp"
#include <string>
#include <sstream>
#include <iomanip>

/* NOTE: "formatter" code for older compilers, ones that define 
 * BOOST_DATE_TIME_NO_WSTRING_CONVERSIONS, is located in 
 * date_formatting_limited.hpp
 */

namespace boost {
namespace date_time {

  //! Formats a month as as string into an ostream
  template<class month_type, class format_type, class charT=char>
  class month_formatter
  {
  public:
    //! Formats a month as as string into an ostream
    /*! This function demands that month_type provide
     *  functions for converting to short and long strings
     *  if that capability is used.
     */
    static std::basic_ostream<charT>& format_month(const month_type& month,
                                      std::basic_ostream<charT>& os)
    {
      switch (format_type::month_format()) 
      {
        case month_as_short_string: 
        { 
          os << month.as_short_string(); 
          break;
        }
        case month_as_long_string: 
        { 
          os << month.as_long_string(); 
          break;
        }
        case month_as_integer: 
        { 
          os << std::setw(2) << std::setfill(os.widen('0')) << month.as_number();
          break;
        }
     
      }
      return os;
    } // format_month
  };


  //! Convert ymd to a standard string formatting policies
  template<class ymd_type, class format_type, class charT=char>
  class ymd_formatter
  {
  public:
    //! Convert ymd to a standard string formatting policies
    /*! This is standard code for handling date formatting with
     *  year-month-day based date information.  This function 
     *  uses the format_type to control whether the string will
     *  contain separator characters, and if so what the character
     *  will be.  In addtion, it can format the month as either
     *  an integer or a string as controled by the formatting 
     *  policy
     */ 
    static std::basic_string<charT> ymd_to_string(ymd_type ymd)
    {
      typedef typename ymd_type::month_type month_type;
      std::basic_ostringstream<charT> ss;
      ss << ymd.year;
      if (format_type::has_date_sep_chars()) {
        ss << format_type::month_sep_char();
      }
      //this name is a bit ugly, oh well....
      month_formatter<month_type,format_type,charT>::format_month(ymd.month, ss);
      if (format_type::has_date_sep_chars()) {
        ss << format_type::day_sep_char();
      }
      ss  << std::setw(2) << std::setfill(ss.widen('0')) 
          << ymd.day;
      return ss.str();
    }
  };


  //! Convert a date to string using format policies
  template<class date_type, class format_type, class charT=char>
  class date_formatter
  {
  public:
    typedef std::basic_string<charT> string_type;
    //! Convert to a date to standard string using format policies
    static string_type date_to_string(date_type d)
    {
      typedef typename date_type::ymd_type ymd_type;
      if (d.is_not_a_date()) {
        return lexical_cast<string_type>(format_type::not_a_date());
      }
      if (d.is_neg_infinity()) {
        return lexical_cast<string_type>(format_type::neg_infinity());
      }
      if (d.is_pos_infinity()) {
        return lexical_cast<string_type>(format_type::pos_infinity());
      }
      ymd_type ymd = d.year_month_day();
      return ymd_formatter<ymd_type, format_type, charT>::ymd_to_string(ymd);
    }    
  };


} } //namespace date_time


#endif

