///////////////////////////////////////////////////////////////////////////////
// This file is part of Guitarrero. Copyright (C) 2009-2012 FONTA Romain
//
// Guitarrero is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Guitarrero is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Guitarrero.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "ObjectMidi.h"

//////////////////////////////////////////////////////////////////////////
//  OBJETS DES SEQUENCES
//////////////////////////////////////////////////////////////////////////

CObjectEvent::CObjectEvent() :
    left(0),
    pRight(NULL),
    pLeft(NULL)
{
}

CObjectEvent::~CObjectEvent()
{
}

// Objet Note

CObjectEventNote::CObjectEventNote():
    note(0),
    velocity(80),
    right(0)
{
}

CObjectEventNote::~CObjectEventNote()
{
}

// Objet Pitch Bend

CObjectEventPitchBend::CObjectEventPitchBend():
    value1(0),
    value2(64)
{
}

CObjectEventPitchBend::~CObjectEventPitchBend()
{
}

// Objet Key After Touch

CObjectEventKeyAfterTouch::CObjectEventKeyAfterTouch():
    note(0),
    velocity(0)
{
}

CObjectEventKeyAfterTouch::~CObjectEventKeyAfterTouch()
{
}

// Objet Channel Pressure

CObjectEventChannelPressure::CObjectEventChannelPressure():
    value(0)
{
}

CObjectEventChannelPressure::~CObjectEventChannelPressure()
{
}

// Objet Controle Change

CObjectEventControlChange::CObjectEventControlChange():
    numController(7),
    value(100),
    pControl(NULL)
{
}

CObjectEventControlChange::~CObjectEventControlChange()
{
}


// Objet Programme Change

CObjectEventProgramChange::CObjectEventProgramChange():
    numProgram(0),
    pControl(NULL)
{
}

CObjectEventProgramChange::~CObjectEventProgramChange()
{
}

// Objet Meta

CObjectMetaEvent::CObjectMetaEvent():
    dataLen(0),
    pData(NULL)
{
}

CObjectMetaEvent::~CObjectMetaEvent()
{
}    

// Objet Tempo

CObjectMetaEventTempo::CObjectMetaEventTempo():
    tempo(120)
{
    dataLen = 3;
    pData = new BYTE[3];
    SetTempo(120);
}

CObjectMetaEventTempo::~CObjectMetaEventTempo()
{
    if(pData)
        delete pData;
}

void  CObjectMetaEventTempo::SetTempo(double t)
{
    double buf;
    buf = min(250, max(30, t)); // pour éviter la division par zero
    tempo = buf;
    buf = 60000000.0/buf;
    
    pData[0] = 0;
    pData[1] = 0;
    pData[2] = 0;
}

// Objet Time Signature

CObjectMetaEventTimeSignature::CObjectMetaEventTimeSignature()
{
    dataLen = 4;
    pData = new BYTE[4];
    if(pData)
    {
        pData[0] = (BYTE)4;
        pData[1] = (BYTE)2;
        pData[2] = (BYTE)24;
        pData[3] = (BYTE)8;
    }
    timeNoteIndex = 0;    
}

CObjectMetaEventTimeSignature::~CObjectMetaEventTimeSignature()
{
    if(pData)
        delete pData;
}

void CObjectMetaEventTimeSignature::SetTimeSignature(BYTE n, BYTE d, BYTE c, BYTE b)
{
    if(!pData)
        pData = new BYTE[4];
    if(pData)
    {
        pData[0] = n;
        pData[1] = d;
        pData[2] = c;
        pData[3] = b;
    }
}    

void CObjectMetaEventTimeSignature::GetTimeSignature(LPBYTE pSignature)
{
    if((pSignature)&&(pData))
    {
        pSignature[0] = pData[0];
        pSignature[1] = pData[1];
        pSignature[2] = pData[2];
        pSignature[3] = pData[3];
    }    
}

// Objet Texte, Copyright, paroles, marqueur, spécial

CObjectMetaEventText::CObjectMetaEventText(BYTE type)
{
    byType = type;
}

CObjectMetaEventText::~CObjectMetaEventText()
{
    if(pData)
        delete pData;
}

void CObjectMetaEventText::SetText(char * pText, int taille)
{
    if(!pText)
        return;
    if(pData)
        delete pData;
    
    dataLen = min(taille, 255);
    pData = new BYTE[dataLen];
    if(!pData)
    {
        dataLen = 0;
        return;
    }
    CopyMemory(pData, pText, dataLen);
}    

void CObjectMetaEventText::GetText(char * pText)
{
    if(!pText)
        return;
    if(!pData)
    {
        pText[0] = 0;
        return;
    }
    CopyMemory(pText, pData, dataLen);
    pText[dataLen] = 0; // terminaison NULL pour chaine de caractère
}
