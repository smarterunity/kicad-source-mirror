/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2004 Jean-Pierre Charras, jaen-pierre.charras@gipsa-lab.inpg.com
 * Copyright (C) 1992-2011 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/**
 * @file class_pcb_text.h
 * @brief TEXTE_PCB class definition.
 */

#ifndef CLASS_PCB_TEXT_H
#define CLASS_PCB_TEXT_H

#include <eda_text.h>
#include <class_board_item.h>


class LINE_READER;
class MSG_PANEL_ITEM;


class TEXTE_PCB : public BOARD_ITEM, public EDA_TEXT
{
public:
    TEXTE_PCB( BOARD_ITEM* parent );

    // Do not create a copy constructor & operator=.
    // The ones generated by the compiler are adequate.

    ~TEXTE_PCB();

    static inline bool ClassOf( const EDA_ITEM* aItem )
    {
        return aItem && PCB_TEXT_T == aItem->Type();
    }

    wxString GetShownText( int aDepth = 0 ) const override;

    bool Matches( wxFindReplaceData& aSearchData, void* aAuxData ) override
    {
        return BOARD_ITEM::Matches( GetShownText(), aSearchData );
    }

    virtual const wxPoint GetPosition() const override
    {
        return EDA_TEXT::GetTextPos();
    }

    virtual void SetPosition( const wxPoint& aPos ) override
    {
        EDA_TEXT::SetTextPos( aPos );
    }

    void Move( const wxPoint& aMoveVector ) override
    {
        EDA_TEXT::Offset( aMoveVector );
    }

    void SetTextAngle( double aAngle ) override;

    void Rotate( const wxPoint& aRotCentre, double aAngle ) override;

    void Flip( const wxPoint& aCentre, bool aFlipLeftRight ) override;

    void GetMsgPanelInfo( EDA_DRAW_FRAME* aFrame, std::vector<MSG_PANEL_ITEM>& aList ) override;

    bool HitTest( const wxPoint& aPosition, int aAccuracy ) const override
    {
        return TextHitTest( aPosition, aAccuracy );
    }

    /** @copydoc BOARD_ITEM::HitTest(const EDA_RECT& aRect,
     *                               bool aContained = true, int aAccuracy ) const
     */
    bool HitTest( const EDA_RECT& aRect, bool aContained, int aAccuracy = 0 ) const override
    {
        return TextHitTest( aRect, aContained, aAccuracy );
    }

    wxString GetClass() const override
    {
        return wxT( "PTEXT" );
    }

    /**
     * Function TransformShapeWithClearanceToPolygonSet
     * Convert the text shape to a set of polygons (one by segment)
     * Used in 3D viewer
     * Circles and arcs are approximated by segments
     * @param aCornerBuffer = a buffer to store the polygon
     * @param aClearanceValue = the clearance around the text
     * @param aError = deviation from true arc position to segment approx
     */
    void TransformShapeWithClearanceToPolygonSet(
            SHAPE_POLY_SET& aCornerBuffer, int aClearanceValue, int aError = ARC_HIGH_DEF ) const;

    wxString GetSelectMenuText( EDA_UNITS aUnits ) const override;

    BITMAP_DEF GetMenuImage() const override;

    // Virtual function
    const EDA_RECT GetBoundingBox() const override;

    EDA_ITEM* Clone() const override;

    virtual void SwapData( BOARD_ITEM* aImage ) override;

#if defined(DEBUG)
    virtual void Show( int nestLevel, std::ostream& os ) const override { ShowDummy( os ); }
#endif
};

#endif  // #define CLASS_PCB_TEXT_H
