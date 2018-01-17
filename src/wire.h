//--------------------------------- wire.h  -----------------------------------

/***************************************************************************
                          wire.h  -  description
                             -------------------
    begin                : 25 June, 2012
    copyright            : (C) 2012 by Simo
    email                : simo@furrydolphin.net
    version		 : 1.0
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

/*      Name: Wire
        Object type: Base Class
        Public Members:
                        Wire  - subroutine: Constructor
                        ~Wire - subroutine: Destructor

                        Diameter   - FXdouble (real) function
                        Resistance - FXdouble (real) function
                        Weight     - FXdouble (real) function
		        Note: typedef double FXdouble

        Private Members:
                         Diam (FXdouble)    - Wire diameter in inches
                         OhmsKft (FXdouble) - Wire resistance (ohms/1000')
                         LbsKft (FXdouble)  - Wire weight in pounds (lbs/1000')
		         Note: typedef double FXdouble

        Note: Wire forms the basis for a wire characteristic look-up
              table.
*/

#ifndef WIRE_H
#define WIRE_H

class Wire
{
   public:
            Wire(void) {}
            Wire(const Wire&);
	    Wire(double aDiam, double aOhmsKft, double aLbsKft);
	    virtual ~Wire(void);

//----------------------- Functions & Subroutines ----------------------

            Wire& operator=(const Wire&);

	    /*
	              Name: Diameter

		      Type: double function; inline

		      Parameters: None

		      Returns: Wire diameter (inches)

		      Note: A "getter" function that simply returns a
		            private data member

		            typedef double double
	    */
	    		
	    double Diameter(void)
	    {
	       return Diam;
	    }

//-----------------------------------------------------------------------
	    /*
	              Name: Resistance

		      Type: double function; inline

		      Parameters: Length - wire length in feet

		      Returns: Total wire resistance (ohms)

		      Note: typedef double double
	    */

	    double Resistance(double Length)
	    {
		return (OhmsKft * (Length/1000.0));
	    }

//-------------------------------------------------------------------------
	    /*
	             Name: Weight

		     Type: double function; inline

		     Parameters: Length - wire length in feet

		     Returns: Total weight of wire (lbs)

		     Note: typedef double double
	    */

	    double Weight(double Length)
	    {
	       return (LbsKft * (Length/1000.0));
	    }

//------------------------------------ Data ----------------------------------
				
   private: double Diam, OhmsKft, LbsKft;

};

#endif

//-------------------------------- End wire.h ---------------------------------
