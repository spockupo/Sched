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
            assert( hour >= 6 );
            assert( hour <= 23 );
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

        bool operator==( const CTime& time ) const
        {
            return m_hour == time.m_hour && m_min == time.m_min;
        }

        bool operator<( const CTime& time ) const
        {
            if ( m_hour < time.m_hour )
                return true;
            else if ( m_hour == time.m_hour )
            {
                if ( m_min < time.m_min )
                    return true;
            }

            return false;
        }

        bool operator>( const CTime& time ) const
        {
            if ( *this < time )
                return false;
            else if ( *this == time )
                return false;
            else 
                return true;
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

        bool operator==( const CShift& shift ) const
        {
            if ( m_startTime == shift.m_startTime &&
                 m_stopTime == shift.m_stopTime )
                return true;
            else
                return false;
        }

        bool IsAssigned() const
        {
            return m_pVolunteer != nullptr;
        };

        // Does this shift match/fit into given shift?
        bool IsMatch( const CShift& shift )
        {
            /*
            if ( m_day == shift.m_day )
            {
                if ( m_startTime < shift.m_startTime
            }
            */
            return false;
        };

        void Assign( CVolunteer *vol )
        {
            m_pVolunteer = vol;
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

        Rating GetRating() const {
            return m_rating;
        };

        Area GetArea() const {
            return m_area;
        };

        POSITIONS& GetPositions() {
            return m_positions;
        };

    private:
        Area m_area;
        POSITIONS m_positions;  // An area has many positions to fill; e.g. 10 autograph tables means 10 'positions' need to be filled
        Rating m_rating;
};


typedef std::vector<Area> PREFERRED_AREAS;


class CAreaMgr
{
    public:
        CAreaMgr() {};

        void AddArea( const CArea& pArea )
        {
            m_areas.push_back( pArea );
        };

    private:
        std::list<CArea> m_areas;
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
        CPerson( const std::wstring& firstname, const std::wstring& lastname, const Age& age, const Rating& rating = Neutral )
            : m_FirstName( firstname ), m_LastName( lastname ), m_age( age ), m_rating( rating )
        {};

        bool IsRatingMatch( const Rating& rating )
        {
            if ( m_rating >= rating )
                return true;
            else
                return false;
        };

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
        CVolunteer( const CPerson& person, const SHIFTS& availability, const PREFERRED_AREAS& areas )
            : m_person( person ), m_availability( availability ), m_preferredAreas( areas ), m_matches( 0 )
        {};

        bool IsRatingMatch( const Rating& rating )
        {
            return m_person.IsRatingMatch( rating );
        };

        bool IsPreferredArea( const Area& area )
        {
            // This doesn't care about preferred #1 or #2 areas - just finds a preferred area - TBD
            return std::find( m_preferredAreas.begin(), m_preferredAreas.end(), area ) != m_preferredAreas.end();
        };

        bool IsAvailable( const CShift& shift ) const
        {
            bool bFound( false );
            for ( auto myShift : m_availability )
            {
                if ( myShift == shift && ! myShift.IsAssigned() )
                {
                    bFound = true;
                    break;
                }
            }
            return bFound;
        };

        void Assign( CShift& shift )
        {
            assert( ! shift.IsAssigned() );

            bool bFound( false );
            for ( auto myShift : m_availability )
            {
                if ( myShift == shift && ! myShift.IsAssigned() )
                {
                    bFound = true;
                    myShift.Assign( this );
                    shift.Assign( this );
                    break;
                }
            }

            assert( bFound );
        };

        void ClearMatches()
        {
            m_matches = 0;
        };

        void IncrementMatch()
        {
            ++m_matches;
        };

        int Matches() const {
            return m_matches;
        };

    private:
        int m_matches;
        CPerson m_person;
        SHIFTS m_availability;
        PREFERRED_AREAS m_preferredAreas;
};


class CVolMgr
{
    public:
        CVolMgr() {};

        void AddVol( const CVolunteer& vol )
        {
            CVolunteer *pVol = new CVolunteer( vol );
            m_vols.push_back( pVol );
        };

        void GetVol( CArea& area );

    private:
        std::list<CVolunteer*> m_vols;
};


class CFilledShift
{
    private:
        CVolunteer *m_pVolunteer;   // volunteer
        CShift     *m_pShift;          // day & time
        CArea      *m_pArea;           // place
};
