#pragma once

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
            assert( min > 0 );
            assert( min < 60 );
            assert( min % 15 == 0 );

            m_hour = hour;
            m_min = min;
        };

    private:
        int m_hour;
        int m_min;
};

class CVolunteer;

class CShift 
{
    public:
        CShift( enum Day day, const CTime &time )
          : m_day(day), m_time(time)
        {};

    private:
        enum Day m_day;
        CTime m_time;
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


class CArea
{
    public:
        CArea();

    private:
        Area m_area;
        std::list<CShift*> m_shifts;
        Rating m_rating;
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
};


class CFilledShift
{
    private:
        CVolunteer *m_pVolunteer;   // volunteer
        CShift     *m_pShift;          // day & time
        CArea      *m_pArea;           // place
};
