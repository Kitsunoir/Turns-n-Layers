//-------------------------------- coredata.cpp --------------------------------

/***************************************************************************

    Begin                : 25 June, 2012
    Copyright            : (C) 2012 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.0
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
 ***************************************************************************/

#include "coredata.h"

/*
        Name: CoreData

	Type: Constructors

	Note: Default constructor - no parameters; does nothing.
	      Useful in case someone wants to initialize members
	      individually (i.e. use like a C-type struct).

              Copy Constructor: Used when initializing a new instance
                  from an existing one.

              Overloaded Constructor: The main constructor used to
                  initialize a new instance.
*/

CoreData::CoreData(const CoreData &Orig)
{
    CoreDiam=   Orig.CoreDiam;
    CoreWidth=  Orig.CoreWidth;
    CoreHeight= Orig.CoreHeight;
    CoreLength= Orig.CoreLength;
    Ilit=       Orig.Ilit;
}

CoreData::CoreData(double aCoreDiam, double aCoreWidth, double aCoreHeight,
		   double aCoreLength, double aIlit) :
CoreDiam(aCoreDiam),
CoreWidth(aCoreWidth),
CoreHeight(aCoreHeight),
CoreLength(aCoreLength),
Ilit(aIlit)
{
}

//------------------------------------------------------------------------------

/*
        Name: operator=

        Type: Function

        Parameters: Orig (Reference: CoreData)

        Returns: Reference (CoreData)

        Note: Overloads the '=' sign so that one instance can be assigned to
              another instance as any simple variable types.
*/

CoreData& CoreData::operator=(const CoreData &Orig)
{
    CoreDiam=   Orig.CoreDiam;
    CoreWidth=  Orig.CoreWidth;
    CoreHeight= Orig.CoreHeight;
    CoreLength= Orig.CoreLength;
    Ilit=       Orig.Ilit;

    return *this;
}

//--------------------------------------------------------------------------------

/*
        Name: ~CoreData

	Type: Destructor

	Note: Empty subroutine - CoreData contains no objects that require
	      deallocation.
*/

CoreData::~CoreData(void) {}

//-------------------------------- coredata.cpp ----------------------------------
