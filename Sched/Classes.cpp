#include "stdafx.h"
#include "Classes.h"



// *The* algorithm
void CVolMgr::GetVol( CArea& area )
{
    // Given the area:

    // Build list of matching volunteers for an area

    std::list<CVolunteer*> matchingVols;
    for ( auto pVol : m_vols )
    {
        // Does rating match area's rating?
        if ( pVol->IsRatingMatch( area.GetRating() ) )
        {
            // Does area match vol's desired areas?
            // For the first pass, we care - for a "second pass" (TBD), we will no longer look at desired ratings
            if ( pVol->IsPreferredArea( area.GetArea() ) )
            {
                matchingVols.push_back( pVol );
            }
        }
    }

    // For each area-matching volunteer, calculate their score on how many area shifts they can cover

    /*
    typedef std::list<CShift> SHIFTS;
    typedef std::vector<SHIFTS> POSITIONS;
    */

    for ( auto pVol : matchingVols )
    {
        POSITIONS& areaPositions = area.GetPositions();
        for ( auto shifts : areaPositions )
        {
            // For this position, find the maximum available volunteer that fits all shifts
            pVol->ClearMatches();
            for ( auto shift : shifts )
            {
                // Given a shift without assigned volunteer, see if vol's availability is a match; if so - assign
                if ( !shift.IsAssigned() && pVol->IsAvailable( shift ) )
                {
                    pVol->IncrementMatch();
                }
            }
        }
    }

    // Who matched the most?  Assign
    CVolunteer* ptrMaxMatchedVolunteer( nullptr );
    int max( 0 );

    for ( auto pVol : matchingVols )
    {
        if ( pVol->Matches() > max )
        {
            max = pVol->Matches();
            ptrMaxMatchedVolunteer = pVol;
        }
    }

    if ( ptrMaxMatchedVolunteer )
    {
        POSITIONS& areaPositions = area.GetPositions();
        for ( auto shifts : areaPositions )
        {
            for ( auto shift : shifts )
            {
                if ( !shift.IsAssigned() && ptrMaxMatchedVolunteer->IsAvailable( shift ) )
                {
                    ptrMaxMatchedVolunteer->Assign( shift );
                }
            }
        }
    }
}