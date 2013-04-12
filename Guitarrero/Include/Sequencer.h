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

#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_

#include "include.h"
#include "ObjectMidi.h"


#define  MAX_CHANNEL  16

#define ZONE_NULL   (UINT)0
#define ZONE_SIZING (UINT)1
#define ZONE_MOVING (UINT)2

#define FILTER_NOTE         1
#define FILTER_KEYPRESS     2
#define FILTER_CTRLCHANGE   4
#define FILTER_PRGMCHANGE   8
#define FILTER_CHANPRESS    16
#define FILTER_PITCHBEND    32
#define FILTER_SYSEX        64

#define FORMAT_0    1
#define FORMAT_1    2

struct TGlobal
{
    CObjectEvent          * pFirstMeta;
    CObjectEvent          * pLastMeta;
    CObjectEvent          * pFirstAll[MAX_CHANNEL];
    CObjectEvent          * pLastAll[MAX_CHANNEL];
    CObjectEvent          * pFirstSignature;
    CObjectEvent          * pLastSignature;
    CObjectMetaEventTempo * pFirstTempo;
    CObjectMetaEventTempo * pLastTempo;
    CObjectMetaEventText  * pTempNameTrack[MAX_CHANNEL];
    TControlUnity         * pFirstControl;
    TControlUnity         * pLastControl;
    TPattern              * pFirstPattern;
    TPattern              * pLastPattern;
    BOOL                    bOpen;
    BOOL                    bModify;
};

struct TOptionClick
{
    BOOL   bActiveM;
    BOOL   bActiveB;
    int    noteM;
    int    noteB;
    int    channelM;
    int    channelB;
    int    velocityM;
    int    velocityB;
}; 

struct TInit
{
    int           mod; // midiout device
    int           mid; // midiin device
    BOOL          bDemix; // demixage auto
    BOOL          bClick; // activation metronome pendant enregistrement
    BOOL          bFusion; // fusion des sequences créées
    BOOL          bQuantise; // activation de la qunatisation
    int           nQuantise; // valeur de la quantise
    UINT          uFilter; // parametre des filtres
    TOptionClick  optClick; // parametre de metronome
};
    
struct TTrackType
{
    int  channel;
    BOOL bMute;
};    

struct TEditorData
{
    TPattern  * pPtrn;   // sequence associé à la fenetre editeur
    int         xo;
    int         yo;
    int         cxTick;
    BOOL        bClose; 
};

struct TTempoMdiData
{
    int    xo;
    int    yo;
    int    cxTick;
    BOOL   bClose;
};

// structure utilisée pour garder les valeurs courantes des controleurs volume et pan
struct TControlMidiCurrent
{
    int  vol;
    int  pan;
    BOOL bVol;
    BOOL bPan;
};  

// structure utilisée pour referencer chaque objet dans une liste
struct TReferenceObject
{
    DWORD          dwTime;
    CObjectEvent * pObject;
    int            channel;
    int            reserved;
};    

// structure utilisée pour stocker la liste de tous les objets avant
// l'exportation des evenements en fichier MIDI
struct TListObject
{
    TReferenceObject * pRef;
    BOOL               bEnable;
    int                arraySize;
    int                count;
};    

struct TControl
{
    DWORD dwTimeTick;
    int   cxTick;
    int   cyTrack;
    int   xOrigine;     // point origine de scrollbar horizontal
    int   yOrigine;     // point d'origine de scrollbar vertical
    int   nResolution;
    int   nFirstLoop;
    int   nLastLoop;
    int   nFirstLocator;
    int   nLastLocator;
    int   nTrackCount;
    int   nTrackSelect;  // numero de piste selectionnée
    int   nVolume[MAX_CHANNEL];
    int   nPan[MAX_CHANNEL];
    BOOL  bPanActive[MAX_CHANNEL];
    BOOL  bLooped; // activer ou non le boucle de lecture
    BOOL  bClicked; // activer ou non le metronome
    BOOL  bGrid; // afficher grille ou non dans la fenetre arrangement
    BOOL  bBkWhite; // fond en blanc ou non la fenetre arrangement
    BOOL  bMaximize; // agrandir ou non les fenetre MDI
    BOOL  bInfoInclude; // inclure ou non les informations sequence
    
    TControl(): dwTimeTick(480),
                cxTick(10),
                cyTrack(25),
                xOrigine(0),
                yOrigine(0),
                nResolution(4),
                nFirstLoop(0),
                nLastLoop(1920),
                nFirstLocator(0),
                nLastLocator(228480),
                nTrackCount(16),
                nTrackSelect(-1),
                bLooped(FALSE),
                bClicked(FALSE),
                bGrid(TRUE),
                bBkWhite(FALSE),
                bMaximize(FALSE),
                bInfoInclude(TRUE)
                {}
};

class CSequencer
{
public:
    CSequencer();
    ~CSequencer();
    
    TPattern* getPattern();  
    DWORD GetTimeTick()const{return m_Ctrl.dwTimeTick;}
    int   GetChannelTrack(int)const;  
    void  ReInit();
      
    // tempo
    double   GetTempo(DWORD);
    void  SetTempo(DWORD, double);  
    
    // signature
    void  SetTimeSignature(DWORD, const BYTE*);
     
    // meta texte
    void  SetTextEvent(BYTE, const void*, int);    
    
    // ctrl change
    void  SetCtrlChange(BYTE, int, DWORD, int);  
    
    // prgm change
    void  SetPrgmChange(int, DWORD, int);
      
    // convertions
    int   GetTimeNoteIndex(DWORD);  // retourne l'index mesure d'un temps donné
    DWORD TimeCodeToTimeClock(DWORD);
    int   TimeCodeToBeat(DWORD);
    
    // liste des controles
    BOOL  AddControlUnity(CObjectEvent*, int);
    void  DeleteControlUnity(TControlUnity*);
    
    // patterns
	TPattern *  CreatePattern(TPatternValue*);
    TPattern *  SelectPattern(int, int, BOOL, UINT*); // seléctionner une sequence
    void  UpdateIDPattern(int); // remet à jour les identifiants des sequences

    // notes
    CObjectEvent * CreateNote(TPattern *);
    
    // pitch bend
    CObjectEvent * CreatePitchBend(TPattern *);
    
    // channel pressure
    CObjectEvent * CreateChannelPressure(TPattern *);
    
    // key after touch
    CObjectEvent * CreateKeyAfterTouch(TPattern *);
    
    // ctrl change
    CObjectEvent * CreateControlChange(TPattern *);
    
    // Prgm Change
    CObjectEvent * CreateProgramChange(TPattern*);
        
    void  DeleteAll();
    int   ScreenToTimeEvent(int);   // convertit l'abcisse de l'ecran en mesure temps
    
private:   
    void  UpdateTimeSignature();
    BOOL  CopyAllEvent(TPattern * , TPattern * );
    TPattern* CreateSamePattern(TPattern *);    
    int   ScreenToNumTrack(int);
    TPattern * ScreenToPattern(int, int, UINT*); // retourne l'adresse d'une sequence pointée 
    void  DeletePattern(TPattern *, BOOL);
    void  DeselectedAllPattern();
    BOOL  IsCutNote(TPattern*, int);
    BOOL  MergePattern(TPattern *); // fusionne une sequence avec celle de droite
   
    int   ScreenToTimeEvent(int, TEditorData *);
    int   ScreenToNoteValue(int, TEditorData *);
    CObjectEventNote * ScreenToNoteObject(int, int, TEditorData *, UINT *);
    void  DeleteAllEvent(TPattern *); // supprime tous les evenements dans une sequence
	  
private:
    TPattern * m_pPatternSelected;
    TTrackType m_tTrack[MAX_CHANNEL]; // pour savoir le n° canaux affécté à la piste
    TGlobal  * m_pGlobal;
    TGlobal  	t;
    char       m_szFileName[MAX_PATH]; // nom de fichier courant
    char       m_szFileImport[MAX_PATH]; // nom de fichier midi importé
    
public:
    TControlMidiCurrent m_cCurrent[MAX_CHANNEL];
    TControl            m_Ctrl;

    
/********************************************************************
* Import et export des fichiers MIDI
*
********************************************************************/
public:
    BOOL   ImportMidiFile(const char*);
    BOOL   ExportMidiFile(char*, int);
    
private:
    WORD   WordSwap(WORD); // pour convertir les données ENDIAN
    DWORD  DwordSwap(DWORD);
    DWORD  GetVarLen(LPBYTE *);
    BOOL   CollectMidiData(LPBYTE*, DWORD);
    BOOL   CollectMidiMeta(LPBYTE*, DWORD);
    BOOL   CollectMidiNote(LPBYTE*, DWORD, BOOL);
    BOOL   CollectMidiPitchBend(LPBYTE*, DWORD, BOOL);
    BOOL   CollectMidiKeyAfterTouch(LPBYTE*, DWORD, BOOL);
    BOOL   CollectMidiChannelPressure(LPBYTE*, DWORD, BOOL);
    BOOL   CollectMidiPrgmChange(LPBYTE*, DWORD, BOOL);
    BOOL   CollectMidiCtrlChange(LPBYTE*, DWORD, BOOL);
    
    void  ExtractListObject(int);
    BOOL  AddListObject(TListObject*, TReferenceObject*);
    void  SortListObject(TListObject*);
    void  FreeListObject();
    void  CreateTempNameTrack(int, char*);
    
    TListObject m_mList[MAX_CHANNEL];
    TListObject m_mListMeta;
    TPattern  * m_pOldPattern;
    BYTE        m_byStatus;
    char        m_szNameTrack[256];
    int         m_oldChannel;
    int         m_maxLenght;
};    

#endif
