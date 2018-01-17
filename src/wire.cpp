//-------------------------------- wire.cpp ----------------------------------

/*******************************************************************************
                                description
                             -------------------
    begin                : 25 June, 2012
    copyright            : (C) 2012 by Simo
    email                : simo@furrydolphin.net
    version              : 1.0
 ***************************************************************************

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   If software can be free, why can't dolphins?                          *
 *                                                                         *
 ***************************************************************************

*/

#include "wire.h"

/*

        Name: Wire

        Type: Subroutine - Constructors
              Copy:       Make new instance from an existing one
	      Overloaded: Make new instance, and initialize.

        Parameters: aDiam (double)    - Wire diameter (inches)
                    aOhmsKft (double) - Wire resistance (ohms/1000')
                    aLbsKft (double)  - Wire weight (lbs/1000')
                    Note: Inherent wire characteristics for each table entry

        Note: Uses initializer list to assign values to class data members
              otherwise, an empty subroutine.

	Note: typedef double double
*/

Wire::Wire(const Wire &Orig)
{
    Diam=    Orig.Diam;
    OhmsKft= Orig.OhmsKft;
    LbsKft=  Orig.LbsKft;
}

//------------------------------------------------------------------------------

Wire::Wire(double aDiam, double aOhmsKft, double aLbsKft) :
Diam(aDiam),
OhmsKft(aOhmsKft),
LbsKft(aLbsKft)
{
}

/*
        Name: operator=

	Type: Function (Reference: Wire)

	Parameters: Orig (Reference: Wire)

	Returns: Reference (Wire)

	Note: Overload the '=' sign so one instance can be assigned to
	      another as with any simple types.
*/

Wire& Wire::operator=(const Wire &Orig)
{
    Diam=    Orig.Diam;
    OhmsKft= Orig.OhmsKft;
    LbsKft=  Orig.LbsKft;

    return *this;
}

//--------------------------------------------------------------------------

/*
       Name: ~Wire
       Type: Destructor
       Note: An empty subroutine: Wire contains no objects that require
             deallocation.
*/

Wire::~Wire(void) {}

//------------------------------- sdwire.cpp ---------------------------------
