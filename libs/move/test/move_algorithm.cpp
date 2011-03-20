//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright David Abrahams, Vicente Botet, Ion Gaztanaga 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <boost/move/move.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include "../example/movable.hpp"

int main()
{
   namespace bi = ::boost::interprocess;
   //Default construct 10 movable objects
   bi::vector<movable> v(10);
   bi::vector<movable> v2(10);

   //Move to v2
   boost::move(v.begin(), v.end(), v2.begin());

   //Test values have been moved
   if(!v[0].moved()){
      return 1;
   }

   if(v2.size() != 10){
      return 1;
   }

   if(v2[0].moved()){
      return 1;
   }

   //Move to v again
   boost::move_backward(v2.begin(), v2.end(), v.end());

   //Test values have been moved
   if(!v2[0].moved()){
      return 1;
   }

   if(v.size() != 10){
      return 1;
   }

   if(v[0].moved()){
      return 1;
   }

   return 0;
}