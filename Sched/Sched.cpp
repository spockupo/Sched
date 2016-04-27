// Sched.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Classes.h"

// TODO Move these to a utils.cpp class

bool operator!=( const CTime& lhs, const CTime& rhs )
{
    return lhs.m_hour != rhs.m_hour || lhs.m_min != rhs.m_min;
        
}

SHIFTS ShiftFactory( const Day& day, const CTime& startTime, const CTime& stopTime, const int& hourlyDivision )
{
    SHIFTS shifts;
    CTime myStart( startTime );
    while ( myStart != stopTime )
    {
        CTime endOfShift( myStart );
        
        endOfShift.AddDivision( hourlyDivision );
        CShift shift( day, myStart, endOfShift );
        shifts.push_back( shift );

        myStart.AddDivision( hourlyDivision );
    }

    return shifts;
}


int main()
{
    CAreaMgr areaMgr;

    // Generate a series of shifts for Friday, 8am to 5pm, in quarter-hour shifts
    SHIFTS shifts = ShiftFactory( Friday, CTime( 8, 0 ), CTime( 9, 30 ), 4 );

    return 0;
}

