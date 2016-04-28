// Sched.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "Classes.h"


// TODO Move these to a utils.cpp class


bool operator!=( const CTime& lhs, const CTime& rhs )
{
    return lhs.m_hour != rhs.m_hour || lhs.m_min != rhs.m_min;
        
}


CVolunteer VolunteerFactory( const std::wstring& firstname, const std::wstring& lastname, const Age& age, const Rating& rating,
                             const SHIFTS& availability, const PREFERRED_AREAS& areas )
{
    CPerson person( firstname, lastname, age, rating );
    CVolunteer volunteer( person, availability, areas );
    return volunteer;
}


// Generates test data only...
PREFERRED_AREAS PreferredAreasFactory()
{
    static int i( 0 );
    PREFERRED_AREAS areas;
    if ( i == 0 )
    {
        areas.push_back( Autographs );
        areas.push_back( Registration );
        ++i;
    }
    else if ( i == 1 )
    {
        areas.push_back( Registration );
        areas.push_back( Autographs );
        ++i;
    }
    else if ( i == 2 )
    {
        areas.push_back( Autographs );
        areas.push_back( Kids );
        i = 0;
    }

    return areas;
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

    CArea autographsArea( Autographs, positions, MVV );

    CVolMgr VolMgr;

    // Volunteer 1

    SHIFTS shifts1( ShiftFactory( Saturday, CTime( 9, 30 ), CTime( 17, 30 ) ) );
    SHIFTS shifts2( ShiftFactory( Sunday, CTime( 11, 0 ), CTime( 16, 00 ) ) );
    shifts1.splice( shifts1.end(), shifts2 );

    CVolunteer vol1 = VolunteerFactory( L"Francois", L"Kupo", Over35, MVV, shifts1, PreferredAreasFactory() );
    VolMgr.AddVol( vol1 );
    
    // Volunteer 2

    SHIFTS shifts3( ShiftFactory( Saturday, CTime( 12, 30 ), CTime( 16, 0 ) ) );
    SHIFTS shifts4( ShiftFactory( Sunday, CTime( 10, 0 ), CTime( 16, 0 ) ) );
    shifts3.splice( shifts3.end(), shifts4 );

    CVolunteer vol2 = VolunteerFactory( L"Jean-Guy", L"Boboslack", Age18_34, Special, shifts3, PreferredAreasFactory() );
    VolMgr.AddVol( vol2 );

    VolMgr.GetVol( autographsArea );

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

