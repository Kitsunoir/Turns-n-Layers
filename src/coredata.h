//------------------------------ coredata.h  ------------------------------

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
 ***************************************************************************


        Name: CoreData
        Type: Struct (Base)
        Members: Subroutines -
                               CoreData  - Constructor (default)
                               CoreData  - Constructor (copy)
                               CoreData  - Constructor (overloaded)
                               operator=   - Overload the '=' sign for assignment
                               ~CoreData - Destructor

                 Variables: CoreDiam (double)   - Core diameter (inches)

                            CoreHeight (double) - Core height (inches),
                                                  rectangular cores.

                            CoreWidth (double)  - Core Width (inches),
                                                  rectangular cores

                            CoreLength (double) - Core length (inches),

                            Ilit (double)       - Inter-layer insulation thickness
                                                  (mils)

        Note: Structure used as arguement to function as convenient means to pass
              related data as opposed to passing each member as an individule
              parameter. (Important as the functions in question change the
              member variables).

*/

#ifndef SDCORE_H
#define SDCORE_H

struct CoreData
{
    CoreData(void) {}
    CoreData(const CoreData&);
    CoreData(double aCoreDiam, double aCoreWidth, double aCoreHeight,
	       double aCoreLength, double aIlit);
    virtual ~CoreData(void);

    CoreData& operator=(const CoreData&);
	
    double CoreDiam, CoreWidth, CoreHeight, CoreLength, Ilit;

};

#endif

//------------------------------ coredata.h  ------------------------------
