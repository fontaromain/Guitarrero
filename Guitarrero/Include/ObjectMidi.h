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

#ifndef _OBJECTMIDI_H_
#define _OBJECTMIDI_H_

#include "windows.h"

#define MIDI_NOTEON        ((unsigned char)0x90)
#define MIDI_NOTEOFF       ((unsigned char)0x80)
#define MIDI_KEYAFTERTOUCH ((unsigned char)0xA0)
#define MIDI_CTRLCHANGE    ((unsigned char)0xB0)
#define MIDI_PRGMCHANGE    ((unsigned char)0xC0)
#define MIDI_CHANPRESS     ((unsigned char)0xD0)
#define MIDI_PITCHBEND     ((unsigned char)0xE0)
#define MIDI_META          ((unsigned char)0xFF)

#define META_TEXT          ((unsigned char)0x01)
#define META_COPYRIGHT     ((unsigned char)0x02)
#define META_NAMETRACK     ((unsigned char)0x03)
#define META_LYRIC         ((unsigned char)0x05)
#define META_MARKER        ((unsigned char)0x06)
#define META_CUEPOINT      ((unsigned char)0x07)
#define META_TEMPO         ((unsigned char)0x51)
#define META_SIGNATURE     ((unsigned char)0x58)

#define CTRLCHANGE_VOLUME  0x07
#define CTRLCHANGE_PAN     0x0A

#define  MAX_CHANNEL  16

class CObjectEvent;

struct TControlUnity
{
    unsigned long dwTime;
    unsigned char  byTrack;
    unsigned char  byStatus;
    unsigned char  byData1;
    unsigned char  byData2;
    TControlUnity * pLeft;
    TControlUnity * pRight;
};    

struct TListBuffer
{
    LPBYTE  pData;
    int     count;
    int     arraySize;
};

class CObjectEvent
{
public:
    CObjectEvent();
    virtual ~CObjectEvent();
    virtual unsigned char GetType() = 0;
   
    int  left;
    CObjectEvent * pRight;
    CObjectEvent * pLeft;
};    

// Objet Note

class CObjectEventNote : public CObjectEvent
{
public:
    CObjectEventNote();
    virtual ~CObjectEventNote();
    virtual unsigned char GetType(){return MIDI_NOTEON;}
   
    int  note;
    int  velocity;
    int  right;
    int bDisabled;
    int bSelected;
};

// Objet Pitch Bend

class CObjectEventPitchBend : public CObjectEvent
{
public:
    CObjectEventPitchBend();
    virtual ~CObjectEventPitchBend();
    virtual unsigned char GetType(){return MIDI_PITCHBEND;}
    
    int  value1;
    int  value2;
    int bSelected;
};

// Objet Key After Touch

class CObjectEventKeyAfterTouch : public CObjectEvent
{
public:
    CObjectEventKeyAfterTouch();
    virtual ~CObjectEventKeyAfterTouch();
    virtual unsigned char GetType(){return MIDI_KEYAFTERTOUCH;}
  
    int  note;
    int  velocity;
    int bSelected;
};


// Objet Channel Pressure

class CObjectEventChannelPressure : public CObjectEvent
{
public:
    CObjectEventChannelPressure();
    virtual ~CObjectEventChannelPressure();
    virtual unsigned char GetType(){return MIDI_CHANPRESS;}
   
    int  value;
    int bSelected;
};

// Objet Controle Change

class CObjectEventControlChange : public CObjectEvent
{
public:
    CObjectEventControlChange();
    virtual ~CObjectEventControlChange();
    virtual unsigned char GetType(){return MIDI_CTRLCHANGE;}
   
    int  numController;
    int  value;
    int bSelected;
    TControlUnity * pControl;
};

// Objet Programme Change

class CObjectEventProgramChange : public CObjectEvent
{
public:
    CObjectEventProgramChange();
    virtual ~CObjectEventProgramChange();
    virtual unsigned char GetType(){return MIDI_PRGMCHANGE;}
  
    int  numProgram;
    int bSelected;
    TControlUnity * pControl;
};

// Objet Meta

class CObjectMetaEvent : public CObjectEvent
{
public:
    CObjectMetaEvent();
    virtual ~CObjectMetaEvent();
    virtual unsigned char GetType(){return MIDI_META;}
    virtual unsigned char GetMetaType() = 0;
    
    int    dataLen;
    unsigned char * pData;
};

// Objet Meta Tempo

class CObjectMetaEventTempo : public CObjectMetaEvent
{
public:
    CObjectMetaEventTempo();
    virtual ~CObjectMetaEventTempo();
    virtual unsigned char GetMetaType(){return META_TEMPO;}
   
    void SetTempo(double);
    double tempo;
    int bSelected;
};    

// Objet Meta Signature

class CObjectMetaEventTimeSignature : public CObjectMetaEvent
{
public:
    CObjectMetaEventTimeSignature();
    virtual ~CObjectMetaEventTimeSignature();
    virtual unsigned char GetMetaType(){return META_SIGNATURE;}
   
    void SetTimeSignature(unsigned char, unsigned char, unsigned char, unsigned char);
    void GetTimeSignature(LPBYTE);
    int  timeNoteIndex;      // index de mesure pour référence
};

// Objet Meta Texte, Copyright, Paroles, Marqueur et Spécial

class CObjectMetaEventText : public CObjectMetaEvent
{
public:
    CObjectMetaEventText(unsigned char);
    virtual ~CObjectMetaEventText();
    virtual unsigned char GetMetaType(){return byType;}
    
    void SetText(char*, int);
    void GetText(char*);
    unsigned char byType;
};


struct TPatternValue
{
    int  numTrack;
    int  left;
    int  right;
    int bSelected;
    int bRecord;
    char szTitle[256];
};

struct TPattern
{
    int  numTrack;
    int  left;
    int  right;
    int bSelected;
    int bRecord;
    char szTitle[256];
    TPattern * pLeft;
    TPattern * pRight;
    int  id;
    int  idList;
    CObjectEvent * pFirstEvent;
    CObjectEvent * pLastEvent;
};

/*******************************************************************************
* AddListBuffer : ajoute un evenement dans la liste 
*
*******************************************************************************/

static int AddListBuffer(TListBuffer * pList, unsigned char byData)
{
    // pour éviter l'extension de mémoire à chaque fois qu'on ajoute une liste,
    // on alloue un paquet de 100 listes
    
    if(!pList->pData)
    {
        pList->pData = (LPBYTE)malloc(100 * sizeof(unsigned char));
        if(pList->pData)
            pList->arraySize = 100;
        else
            return 0;
    }
    
    LPBYTE pBuf;
    
    if(pList->count >= pList->arraySize)
    {
        pBuf = (LPBYTE)realloc(pList->pData,
            (pList->arraySize + 100) * sizeof(unsigned char));
        if(pBuf)
        {
            pList->pData = pBuf;
            pList->arraySize += 100;
        }    
        else
            return 0;
    }
    
    pList->pData[pList->count] = byData;
    pList->count++;
    return 1;
}


static void FreeListBuffer(TListBuffer * pList)
{
    if((pList)&&(pList->pData))
    {
        free(pList->pData);
        ZeroMemory(pList, sizeof(TListBuffer));
    }    
}
 
/*******************************************************************************
* AddListDeltaTime : ajoute la durée d'evenement suivant dans la liste 
*
*******************************************************************************/

static int AddListDeltaTime(TListBuffer * pList, int value)
{
    unsigned long dwValue = (unsigned long)value;
    unsigned long dwBuf = dwValue & 0x7F;
    unsigned char  byBuf;
    
    while(dwValue >>= 7)
    {
        dwBuf <<= 8;
        dwBuf |= ((dwValue & 0x7F) | 0x80);
    }
    
    while(1)
    {
        byBuf = (unsigned char)(dwBuf & 0xFF);
        AddListBuffer(pList, byBuf);
        if(dwBuf & 0x80)
            dwBuf >>= 8;
        else
            break;
    }    
    return 1;
}    

/*******************************************************************************
* AddListEndOfTrack : ajoute la fin de bloc de piste
*
*******************************************************************************/

static int AddListEndOfTrack(TListBuffer * pList)
{
    AddListBuffer(pList, 0xFF);
    AddListBuffer(pList, 0x2F);
    AddListBuffer(pList, 0);
    return 1;
}    
#endif
