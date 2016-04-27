// Sched.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Classes.h"

// TODO Move these to a utils.cpp class

bool operator!=( const CTime& lhs, const CTime& rhs )
{
    return lhs.m_hour != rhs.m_hour || lhs.m_min != rhs.m_min;
        
}

SHIFTS ShiftFactory( const Day& day, const CTime& startTime, const CTime& stopTime, const int& hourlyDivision = 4 )
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

    // Generate a series of shifts mirroring Pop Expo 2015 Saturday autographs shifts.
    // This data will be read from a config .csv file.
    POSITIONS positions;
    positions.push_back( ShiftFactory( Saturday, CTime( 9, 30 ), CTime( 19, 0 ) ) );
    positions.push_back( ShiftFactory( Saturday, CTime( 9, 30 ), CTime( 19, 0 ) ) );
    positions.push_back( ShiftFactory( Saturday, CTime( 10, 0 ), CTime( 19, 0 ) ) );
    positions.push_back( ShiftFactory( Saturday, CTime( 10, 0 ), CTime( 19, 0 ) ) );
    positions.push_back( ShiftFactory( Saturday, CTime( 10, 0 ), CTime( 19, 0 ) ) );
    positions.push_back( ShiftFactory( Saturday, CTime( 10, 0 ), CTime( 19, 0 ) ) );
    positions.push_back( ShiftFactory( Saturday, CTime( 10, 30 ), CTime( 19, 0 ) ) );
    positions.push_back( ShiftFactory( Saturday, CTime( 10, 30 ), CTime( 19, 0 ) ) );

    CArea area( Autographs, positions, MVV );

    // TODO
    //
    // Generate some volunteers in a list.
    // And start the algorithm, assigning a pointer to a volunteer that matches a series of shifts in a position.
    // Once the volunteer is no longer available, look for other volunteers to continue matching shifts.
    // Eventually, you run out of volunteers or shifts.
    // Write to console a listing of the results, mimicing the Excel schedule as much as possible, then
    // potentially write it out as a CSV that can be imported into Excel, and in such as way as to allow edits -
    // all for prototyping at this point, and proof-of-concept usage.  Effectively, trying to see if this is not
    // an NP problem.
    // Afterward, algorithm can be tweaked to sort volunteers in order of largest-blocks of availability - and they
    // have to get priority over volunteers with limited availability.  That should be ok for coveted areas like
    // Autographs - you want to reward those that are available for full day.  This may conflict with aim to get
    // as many people refunded as possible; that would be interesting to support.
    //


    return 0;
}

