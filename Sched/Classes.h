#pragma once

/* Branching test 2 */

#include "stdafx.h"

enum Day
{
    Friday = 0,
    Saturday,
    Sunday
};

class CTime
{
    public:
        CTime( int hour, int min )
        {
            assert( hour >= 7 );
            assert( hour <= 18 );
            assert( min >= 0 );
            assert( min < 60 );
            assert( min % 15 == 0 );

            m_hour = hour;
            m_min = min;
        };

        void AddDivision( const int& hourlyDivision )
        {
            assert( hourlyDivision >= 0 && hourlyDivision <= 4 );

            int minutes( 60 / hourlyDivision );
            m_min += minutes;
            if ( m_min >= 60 )
            {
                ++m_hour;
                m_min -= 60;
            }
        }

        int m_hour;
        int m_min;
};


class CVolunteer;


// A CShift represents a shift during which a single volunteer works a single period; e.g. a four-hour shift on Saturday.
class CShift 
{
    public:
        CShift( enum Day day, const CTime &startTime, const CTime &stopTime )
            : m_day( day ), m_startTime( startTime ), m_stopTime( stopTime ), m_pVolunteer( nullptr )
        {};

        bool operator<( const CShift& lhs ) const
        {
            return true;
        };

    private:
        enum Day m_day;
        CTime m_startTime;
        CTime m_stopTime;
        CVolunteer *m_pVolunteer;   // Shift not scheduled if this is nullptr
};


// Volunteer & Area ratings
enum Rating
{
    Special = 0,
    New,
    Neutral,
    MVV
};


enum Area
{
    Registration,
    PhotoOps,
    Hall4Doors,
    Kids,
    WeaponsCheck,
    MainEvents,
    Autographs
};


typedef std::list<CShift> SHIFTS;
typedef std::vector<SHIFTS> POSITIONS;


class CArea
{
    public:
        CArea( const Area& area, const POSITIONS& positions, const Rating& rating )
            : m_area( area ), m_positions( positions ), m_rating( rating )
        {};

    private:
        Area m_area;
        POSITIONS m_positions;  // An area has many positions to fill; e.g. 10 autograph tables means 10 'positions' need to be filled
        Rating m_rating;
};


class CAreaMgr
{
    public:
        CAreaMgr() {};

        void AddArea( CArea* pArea )
        {
            m_areas.push_back( pArea );
        };

    private:
        std::list<CArea*> m_areas;
};


enum Age
{
    Below18,
    Age18_34,
    Over35
};


class CPerson
{
    public:
        CPerson();

    private:
        std::wstring m_ID;

        std::wstring m_FirstName;
        std::wstring m_LastName;
        std::wstring m_Nickname;
        Age m_age;

        Rating m_rating;
};


class CVolunteer
{
    public:
        CVolunteer();

    private:
        CPerson m_person;
        std::list<CShift*> m_availability;
        std::vector<CArea*> m_preferredAreas;
};


class CFilledShift
{
    private:
        CVolunteer *m_pVolunteer;   // volunteer
        CShift     *m_pShift;          // day & time
        CArea      *m_pArea;           // place
};
