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
#include "Sequencer.h"

using namespace std;
#pragma pack(push, 2)
struct TMidiFileHdr
{
    WORD wFormat;
    WORD wTrackCount;
    WORD wTimeTicks;
};
#pragma pack(pop)

const int cstDefaultProgram[16]={0,33,3,4,48,50,11,28,16,0,7,45,61,73,83,97};

int   __cdecl CompareObject(const void*, const void*);
    
////////////////////////////////////////////////////////////////////////////////
// LA CLASSE CSEQUENCER
////////////////////////////////////////////////////////////////////////////////


CSequencer::CSequencer():
    m_pPatternSelected(NULL)
{
    m_pGlobal = &this->t;
    m_szFileName[0] = 0;
    m_szFileImport[0] = 0;
    for(int i=0; i<MAX_CHANNEL; i++)
    {
        m_tTrack[i].bMute = FALSE;
        m_tTrack[i].channel = i;
        ZeroMemory(&m_mList[i], sizeof(TListObject));
    }
    ZeroMemory(&m_mListMeta, sizeof(TListObject));
    ZeroMemory(m_pGlobal, sizeof(TGlobal));
}

CSequencer::~CSequencer()
{
    DeleteAll();
}


int CSequencer::GetChannelTrack(int numTrack)const
{
    return m_tTrack[numTrack].channel;
}

WORD CSequencer::WordSwap(WORD wValue)
{
    return ((wValue>>8)|((wValue<<8)&0xFF00));
}

DWORD CSequencer::DwordSwap(DWORD dwValue)
{
    return ((dwValue>>24)|((dwValue>>8)&0x0000FF00)|((dwValue<<8)&0x00FF0000)|
        ((dwValue<<24)&0xFF000000));
}

/*****************************************************************
* ReInit : ré-initialisation de toutes les variables utilisée dans
* la classe CSequencer
*
*****************************************************************/

void CSequencer::ReInit()
{
    int i;
    m_Ctrl.dwTimeTick = 480;
    m_Ctrl.cxTick = 10;
    m_Ctrl.cyTrack = 25;
    m_Ctrl.xOrigine = 0;
    m_Ctrl.yOrigine = 0;
    m_Ctrl.nResolution = 4;
    m_Ctrl.nFirstLoop = 0;
    m_Ctrl.nLastLoop = 1920;
    m_Ctrl.nFirstLocator = 0;
    m_Ctrl.nLastLocator = 228480;
    m_Ctrl.nTrackCount = MAX_CHANNEL;
    m_Ctrl.nTrackSelect = -1;
    m_Ctrl.bLooped = FALSE;
    m_Ctrl.bClicked = FALSE;
    m_Ctrl.bGrid = TRUE;
    m_Ctrl.bBkWhite = FALSE;
    m_Ctrl.bInfoInclude = TRUE;
    
    DeleteAll();
    // initialisation nom de fichier courant
    m_szFileName[0] = 0;
    m_szFileImport[0] = 0;
    
    // initialisation des options des pistes
    for(i=0; i<MAX_CHANNEL; i++)
    {
        m_Ctrl.nVolume[i] = 100;
        m_Ctrl.nPan[i] = 63;
        m_Ctrl.bPanActive[i] = FALSE;
        m_tTrack[i].bMute = FALSE;
        m_tTrack[i].channel = i;
        m_cCurrent[i].vol = 100;
        m_cCurrent[i].pan = 63;
        m_cCurrent[i].bVol = FALSE;
        m_cCurrent[i].bPan = FALSE;
    }
   
    // initialisation de tempo
    SetTempo(0, 120);
    
    // initialisation de signature    
    BYTE by[4] = {4,2,24,8};
    SetTimeSignature(0, by);
    
    // initialisation de volume, balance, programme change    
    for(int i=0; i<MAX_CHANNEL; i++)
    {
        SetCtrlChange(CTRLCHANGE_VOLUME, i, 0, 100);
        SetCtrlChange(CTRLCHANGE_PAN, i, 0, 63);
        SetPrgmChange(i, 0, cstDefaultProgram[i]);
    }
     
    // on met à jour le menu s'il y a changement    
    m_pGlobal->bModify = FALSE;
}    



/****************************************************************
* SetPrgmChange :
*
****************************************************************/

void CSequencer::SetPrgmChange(int numTrack, DWORD dwTime, int newValue)
{
    if(!m_pGlobal)
        return;
    
    // on met à jour le menu s'il y a changement
    if(!m_pGlobal->bModify)
    {
        m_pGlobal->bModify = TRUE;
    }
    
    newValue = max(0, min(127, newValue));
    // on verifie si au meme position on a déjà un changement de programme, donc on modifie 
    // seulement sa valeur
    CObjectEvent * p = m_pGlobal->pFirstAll[numTrack];    
    while(p)
    {
        if((p->GetType()==MIDI_PRGMCHANGE)&&(dwTime==(DWORD)p->left))
        {
            ((CObjectEventProgramChange*)p)->numProgram = newValue;
            ((CObjectEventProgramChange*)p)->pControl->byData1 = (BYTE)newValue;
            return;
        }
        p = p->pRight;    
    }
    
    // sinon insérer une liste par ordre croissant du TimeCode
    
    CObjectEventProgramChange * ps = new CObjectEventProgramChange;
    if(!ps)
        return;
    
    ps->left = (int)dwTime;
    ps->numProgram = newValue;
    
    AddControlUnity(ps, numTrack);
    
    p = m_pGlobal->pFirstAll[numTrack];
    if(!p)
    {
        ps->pLeft = NULL;
        ps->pRight = NULL;
        m_pGlobal->pFirstAll[numTrack] = ps;
        m_pGlobal->pLastAll[numTrack] = ps;
        return;
    }
    
    while(p)
    {
        if(dwTime<(DWORD)p->left)
        {
            ps->pLeft = p->pLeft;
            ps->pRight = p;
            if(p == m_pGlobal->pFirstAll[numTrack])
                m_pGlobal->pFirstAll[numTrack] = ps;
            if(p->pLeft)
                p->pLeft->pRight = ps;
            p->pLeft = ps;
            return;
        }
        p = p->pRight;    
    }
    
    if(m_pGlobal->pLastAll[numTrack])
        m_pGlobal->pLastAll[numTrack]->pRight = ps;
    ps->pLeft = m_pGlobal->pLastAll[numTrack];
    ps->pRight = NULL;
    m_pGlobal->pLastAll[numTrack] = ps;
}

/****************************************************************
* SetCtrlChange :
*
****************************************************************/

void CSequencer::SetCtrlChange(BYTE byController, int numTrack, DWORD dwTime, int newValue)
{
    if(!m_pGlobal)
        return;
    
    // on met à jour le menu s'il y a changement
    if(!m_pGlobal->bModify)
    {
        m_pGlobal->bModify = TRUE;
    }
    
    newValue = max(0, min(127, newValue));
    // on verifie si au meme position on a déjà un changement de volume, donc on modifie 
    // seulement sa valeur
    CObjectEvent * p = m_pGlobal->pFirstAll[numTrack];    
    while(p)
    {
        if((p->GetType()==MIDI_CTRLCHANGE)&&
        (((CObjectEventControlChange*)p)->numController==(int)byController)&&
        (dwTime==(DWORD)p->left))
        {
            ((CObjectEventControlChange*)p)->value = newValue;
            return;
        }
        p = p->pRight;    
    }
    
    // sinon insérer une liste par ordre croissant du TimeCode
    
    CObjectEventControlChange * ps = new CObjectEventControlChange;
    if(!ps)
        return;
    
    ps->left = (int)dwTime;
    ps->numController = (int)byController;
    ps->value = newValue;
    
    p = m_pGlobal->pFirstAll[numTrack];
    if(!p)
    {
        ps->pLeft = NULL;
        ps->pRight = NULL;
        m_pGlobal->pFirstAll[numTrack] = ps;
        m_pGlobal->pLastAll[numTrack] = ps;
        return;
    }
    
    while(p)
    {
        if(dwTime<(DWORD)p->left)
        {
            ps->pLeft = p->pLeft;
            ps->pRight = p;
            if(p == m_pGlobal->pFirstAll[numTrack])
                m_pGlobal->pFirstAll[numTrack] = ps;
            if(p->pLeft)
                p->pLeft->pRight = ps;
            p->pLeft = ps;
            return;
        }
        p = p->pRight;    
    }
    
    if(m_pGlobal->pLastAll[numTrack])
        m_pGlobal->pLastAll[numTrack]->pRight = ps;
    ps->pLeft = m_pGlobal->pLastAll[numTrack];
    ps->pRight = NULL;
    m_pGlobal->pLastAll[numTrack] = ps;
}


/*****************************************************************
* GetTempo : recupère le tempo sur un temps précis
*
*****************************************************************/

double CSequencer::GetTempo(DWORD dwTime)
{
    if((!m_pGlobal)||(!m_pGlobal->pFirstTempo))
        return 120;
    
    double tempo = 120;
    DWORD dw = 0;
    CObjectEvent * p = m_pGlobal->pFirstTempo;
    
    while(p)
    {
        if((dwTime>=dw)&&(dwTime>=(DWORD)p->left))
        {
            tempo = ((CObjectMetaEventTempo*)p)->tempo;
            dw = (DWORD)p->left;
        }
        p = p->pRight;    
    }    
    return tempo;
}

/****************************************************************
* SetTempo :
*
****************************************************************/

void CSequencer::SetTempo(DWORD dwTime, double tempo)
{
    // si le pointeur qui contient la liste des tempo n'existe pas, on sort
    
    if(!m_pGlobal)
        return;
    
    // on met à jour le menu s'il y a changement
    if(!m_pGlobal->bModify)
    {
        m_pGlobal->bModify = TRUE;
    }
    
    // deséléctionne les tempos séléctionnées
    
    CObjectEvent * p = m_pGlobal->pFirstTempo;
    while(p)
    {
        ((CObjectMetaEventTempo*)p)->bSelected = FALSE;
        p = p->pRight;    
    }
    
    // verification si au même moment, on a déjà marqué un tempo, si oui on change
    // seulement sa valeur, sinon on ajoute une liste
    p = m_pGlobal->pFirstTempo;
    while(p)
    {
        if(dwTime==(DWORD)p->left)
        {
            ((CObjectMetaEventTempo*)p)->SetTempo(tempo);
            ((CObjectMetaEventTempo*)p)->bSelected = TRUE;
            return;
        }
        p = p->pRight;    
    }
    
    // sinon insérer une liste par ordre croissant du TimeCode
    
    CObjectMetaEventTempo * pt = new CObjectMetaEventTempo;
    if(!pt)
        return;
    
    pt->left = (int)dwTime;
    pt->SetTempo(tempo);
    pt->bSelected = TRUE;
    
    p = m_pGlobal->pFirstTempo;
    if(!p)
    {
        pt->pLeft = NULL;
        pt->pRight = NULL;
        m_pGlobal->pFirstTempo = pt;
        m_pGlobal->pLastTempo = pt;
        return;
    }    
    
    while(p)
    {
        if(dwTime<(DWORD)p->left)
        {
            pt->pLeft = p->pLeft;
            pt->pRight = p;
            if(p == m_pGlobal->pFirstTempo)
                m_pGlobal->pFirstTempo = pt;
            if(p->pLeft)
                p->pLeft->pRight = pt;
            p->pLeft = pt;
            return;
        }
        p = p->pRight;    
    }
    
    if(m_pGlobal->pLastTempo)
        m_pGlobal->pLastTempo->pRight = pt;
    pt->pLeft = m_pGlobal->pLastTempo;
    pt->pRight = NULL;
    m_pGlobal->pLastTempo = pt;
}

TPattern * CSequencer::getPattern()
{
	return m_pGlobal->pFirstPattern ;
}

void CSequencer::SetTimeSignature(DWORD dwTime, const BYTE * pSignature)
{
    // si le pointeur qui contient la liste des signature n'existe pas ou si
    // l'adresse de pSignature est NULL, on sort
    
    if((!m_pGlobal)||(!pSignature))
        return;
    
    // on met à jour le menu pour le changement
    if(!m_pGlobal->bModify)
    {
        m_pGlobal->bModify = TRUE;
    }
    
    // verification si au même moment, on a déjà marqué un signature, si oui on change
    // seulement sa valeur, sinon on ajoute une liste    
    int timeNote;
    CObjectEvent * p = m_pGlobal->pFirstSignature;
    timeNote = GetTimeNoteIndex(dwTime);
    while(p)
    {
        if(timeNote==((CObjectMetaEventTimeSignature*)p)->timeNoteIndex)
        {
            ((CObjectMetaEventTimeSignature*)p)->SetTimeSignature(pSignature[0], 
                pSignature[1], pSignature[2], pSignature[3]);
            return;
        }
        p = p->pRight;    
    }
    
    // sinon insérer une liste par ordre croissant du TimeCode    
    CObjectMetaEventTimeSignature * ps = new CObjectMetaEventTimeSignature;
    if(!ps)
        return;
    
    ps->left = (int)dwTime;
    ps->SetTimeSignature(pSignature[0],pSignature[1],pSignature[2],pSignature[3]);
    ps->timeNoteIndex = timeNote;
    
    p = m_pGlobal->pFirstSignature;
    if(!p)
    {
        ps->pLeft = NULL;
        ps->pRight = NULL;
        m_pGlobal->pFirstSignature = ps;
        m_pGlobal->pLastSignature = ps;
        UpdateTimeSignature();
        return;
    }
    
    while(p)
    {
        if(timeNote<((CObjectMetaEventTimeSignature*)p)->timeNoteIndex)
        {
            ps->pLeft = p->pLeft;
            ps->pRight = p;
            if(p == m_pGlobal->pFirstSignature)
                m_pGlobal->pFirstSignature = ps;
            if(p->pLeft)
                p->pLeft->pRight = ps;
            p->pLeft = ps;
            UpdateTimeSignature();
            return;
        }
        p = p->pRight;    
    }
    
    if(m_pGlobal->pLastSignature)
        m_pGlobal->pLastSignature->pRight = ps;
    ps->pLeft = m_pGlobal->pLastSignature;
    ps->pRight = NULL;
    m_pGlobal->pLastSignature = ps;
    UpdateTimeSignature();
}    

/****************************************************************
* SetTextEvent :
*
****************************************************************/

void CSequencer::SetTextEvent(BYTE type, const void * pText, int taille)
{
    // si le pointeur qui contient la liste des meta n'existe pas on quitte    
    if(!m_pGlobal)
        return;
    
    // on verifie si on a déjà créer un objet de meme type
    CObjectEvent * p = m_pGlobal->pFirstMeta;
    CObjectEvent * pBuf;
    while(p)
    {
        // si on a déjà créé, on change le texte s'il existe ou on supprime l'objet
        // s'il n'existe pas
        if(type==((CObjectMetaEventText*)p)->byType)
        {
            if((pText)&&(taille>0))
            {
                ((CObjectMetaEventText*)p)->SetText((char*)pText, taille);
                // on met à jour le menu pour le changement
                if(!m_pGlobal->bModify)
                {
                    m_pGlobal->bModify = TRUE;
                }
                return;
            }
            else // ici on supprime l'objet
            {
                // avant de supprimer un objet on doit changer tous les noeuds    
                pBuf = p->pLeft;
                if(pBuf)
                    pBuf->pRight = p->pRight;
    
                pBuf = p->pRight;
                if(pBuf)
                    pBuf->pLeft = p->pLeft;
    
                if(m_pGlobal->pFirstMeta==p)
                    m_pGlobal->pFirstMeta = p->pRight;
                if(m_pGlobal->pLastMeta==p)
                    m_pGlobal->pLastMeta = p->pLeft;
    
                // maintenant on peut supprimer l'objet    
                delete p;
                // on met à jour le menu pour le changement
                if(!m_pGlobal->bModify)
                {
                    m_pGlobal->bModify = TRUE;
                }
                return;
            }        
        }
        p = p->pRight;    
    }
    
    // si l'objet de meme type n'existe pas, on va le créer si le texte existe ou 
    // sa taille n'est pas nulle    
    if((!pText)||(taille<=0))
        return;   
    
    CObjectMetaEventText * ps = new CObjectMetaEventText(type);
    if(!ps)
        return;
    
    ps->left = 0;
    ps->SetText((char*)pText, taille);    
    if(m_pGlobal->pLastMeta)
        m_pGlobal->pLastMeta->pRight = ps;
    ps->pLeft = m_pGlobal->pLastMeta;
    ps->pRight = NULL;
    m_pGlobal->pLastMeta = ps;
    if(!m_pGlobal->pFirstMeta)
        m_pGlobal->pFirstMeta = ps;
    // on met à jour le menu pour le changement
    if(!m_pGlobal->bModify)
    {
        m_pGlobal->bModify = TRUE;
    }
}    


/****************************************************************
* GetTimeNoteIndex : retourne l'index de mesure d'un temps 
* timeCode donné
*
****************************************************************/

int CSequencer::GetTimeNoteIndex(DWORD dwTime)
{
    BYTE bySgt[4];
    int   nBuf;
    int   pos = 0;
    int measure = 0;
    
    bySgt[0] = 4;
    bySgt[1] = 2;
    bySgt[2] = 24;
    bySgt[3] = 8;
    
    CObjectEvent * p = m_pGlobal->pFirstSignature;
    while(p)
    {
        if((int)dwTime<p->left)
            break;
        
        ((CObjectMetaEventTimeSignature*)p)->GetTimeSignature(bySgt);
        measure = ((CObjectMetaEventTimeSignature*)p)->timeNoteIndex;
        pos = p->left;
        
        p = p->pRight;
    }
    
    nBuf = (int)dwTime - pos;    
    measure += ((nBuf*(1<<bySgt[1]))/(GetTimeTick()*4*(int)bySgt[0]));
    return measure;
}    

/****************************************************************
* UpdateTimeSignature : recalcule le temps debut d'un changement
* de signature
*
****************************************************************/

void CSequencer::UpdateTimeSignature()
{
    BYTE bySgt[4];
    int   nBuf = 0;
    int   mesure = 0;
    int   oldMesure = 0;
    
    bySgt[0] = 4;
    bySgt[1] = 2;
    bySgt[2] = 24;
    bySgt[3] = 8;
    
    CObjectEvent * p = m_pGlobal->pFirstSignature;
    while(p)
    {
        mesure = ((CObjectMetaEventTimeSignature*)p)->timeNoteIndex;
        nBuf += ((GetTimeTick()*4*(int)bySgt[0]*(mesure - oldMesure))/(1<<bySgt[1]));
        oldMesure = mesure;
        p->left = nBuf;
        ((CObjectMetaEventTimeSignature*)p)->GetTimeSignature(bySgt);
        
        p = p->pRight;
    }
}        

/****************************************************************
* TimeCodeToBeat : cette fonction est utilisée pour savoir le pas
* à pas des mesures et des temps à chaque avancement du timeCode
* pendant la lecture.
* Elle avertit si on lance le metronome.
* Elle retourne : 2 si la mesure avance d'un pas,
*                 1 si le temps avance d'un pas
*                 0 sinon
*
****************************************************************/

int CSequencer::TimeCodeToBeat(DWORD dwTime)
{
    static int oldClickReference = 0;
    int nClick;
    
    nClick = (int)(dwTime % m_Ctrl.dwTimeTick);
    
    if(oldClickReference<=nClick)
    {
        oldClickReference = nClick;
        return 0;
    }    
    
    oldClickReference = nClick;
    
    BYTE bySgt[4];
    int   pos = 0;
    int   mesure = 0;
    int   temps = 0;
    int   time = (int)dwTime;
    
    bySgt[0] = 4;
    bySgt[1] = 2;
    bySgt[2] = 24;
    bySgt[3] = 8;
    
    CObjectEvent * p = m_pGlobal->pFirstSignature;
    while(p)
    {
        if(time < p->left)
            break;
        ((CObjectMetaEventTimeSignature*)p)->GetTimeSignature(bySgt);
        mesure = ((CObjectMetaEventTimeSignature*)p)->timeNoteIndex;
        pos = p->left;
        p = p->pRight; 
    }
    
    int buf1, buf2;
    int bufM, bufT;
    int ret = 0;
    static int mesureReference = 0;
    static int tempReference = 0;
    
    time -= pos;
    buf1 = (GetTimeTick()*4)/(1<<bySgt[1]);
    buf2 = buf1*bySgt[0];
    
    bufM = time/buf2;
    bufT = (time - (buf2*bufM))/buf1;
    bufM += mesure;
    if(bufM>mesureReference)
        ret = 2;
    else if(bufT>tempReference)
        ret = 1;
    
    mesureReference = bufM;
    tempReference = bufT;
    return ret;
}

/****************************************************************
* TimeCodeToTimeClock : convertit le timeCode en millisecondes
*
****************************************************************/
DWORD CSequencer::TimeCodeToTimeClock(DWORD dwTime)
{
	// pour éviter la division par zéro
    if(m_Ctrl.dwTimeTick==0)
        return 0;
 
    double d, dBuf = 0.0;
    double oldTempo = 120.0;
    int oldTime = 0;
    
   	CObjectEvent * p = m_pGlobal->pFirstTempo;

    while(p)
    {	
        if(dwTime<=(DWORD)p->left)
        {
	        d = dBuf + (60000.0*(double)((int)dwTime - oldTime))/
                ((double)oldTempo*(double)m_Ctrl.dwTimeTick);
     
            return (DWORD)d;
        }
        
        dBuf += (60000.0*(double)(p->left - oldTime))/
            ((double)oldTempo*(double)m_Ctrl.dwTimeTick);
        oldTime = p->left;
        oldTempo = ((CObjectMetaEventTempo*)p)->tempo;
        p = p->pRight;
    }   
		
    d = dBuf + (60000.0*(double)((int)dwTime - oldTime))/
        ((double)oldTempo*(double)m_Ctrl.dwTimeTick);
  
    return (DWORD)d;
}    
/******************************************************************
* AddControlUnity : ajoute dans la liste des controles un evenement
*
******************************************************************/

BOOL CSequencer::AddControlUnity(CObjectEvent * pObj, int numTrack)
{
    BYTE type;
    if(!pObj)
        return FALSE;
    type = pObj->GetType();
    if((type!=MIDI_CTRLCHANGE)&&(type!=MIDI_PRGMCHANGE))
        return FALSE;    
    
    TControlUnity * p;
    p = new TControlUnity;
    if(!p)
        return FALSE;
    ZeroMemory(p, sizeof(TControlUnity));
    
    p->dwTime = (DWORD)pObj->left;
    p->byStatus = type;
    p->byTrack = (BYTE)numTrack;
    switch(type)
    {
        case MIDI_CTRLCHANGE:
            p->byData1 = (BYTE)((CObjectEventControlChange*)pObj)->numController;
            p->byData2 = (BYTE)((CObjectEventControlChange*)pObj)->value;
            ((CObjectEventControlChange*)pObj)->pControl = p;
            break;
        case MIDI_PRGMCHANGE:
            p->byData1 = (BYTE)((CObjectEventProgramChange*)pObj)->numProgram;
            ((CObjectEventProgramChange*)pObj)->pControl = p;
            break;
    }
    p->pLeft = m_pGlobal->pLastControl;
    if(m_pGlobal->pLastControl)
        m_pGlobal->pLastControl->pRight = p;
    
    if(!m_pGlobal->pFirstControl)
        m_pGlobal->pFirstControl = p;
    
    m_pGlobal->pLastControl = p;
    
    return TRUE;
}

/************************************************************
* DeleteControlUnity : supprime un evenement dans la liste
* des controles
*
************************************************************/

void CSequencer::DeleteControlUnity(TControlUnity * pDel)
{
    TControlUnity * p;
    
    if(!pDel)
        return;
    
    // avant de supprimer un evenement on doit changer tous les noeuds dans la liste        
    p = pDel->pLeft;
    if(p)
        p->pRight = pDel->pRight;
    
    p = pDel->pRight;
    if(p)
        p->pLeft = pDel->pLeft;
    
    if(m_pGlobal->pFirstControl==pDel)
        m_pGlobal->pFirstControl = pDel->pRight;
    if(m_pGlobal->pLastControl==pDel)
        m_pGlobal->pLastControl = pDel->pLeft;
    
    delete pDel;
}


/****************************************************************
* CreatePattern : creation d'une nouvelle sequence à partir 
* d'une valeur de TPatternValue
*
****************************************************************/

TPattern * CSequencer::CreatePattern(TPatternValue * pv)
{
    if(!pv)
        return NULL;
    
    TPattern * p;
    p = new TPattern;
    if(!p)
        return NULL;
    ZeroMemory(p, sizeof(TPattern));
    
    p->numTrack = pv->numTrack;
    p->left = pv->left;
    p->right = pv->right;
    p->bSelected = pv->bSelected;
    p->bRecord = pv->bRecord;
    p->pLeft = m_pGlobal->pLastPattern;
    lstrcpy(p->szTitle, pv->szTitle);
    
    if(m_pGlobal->pLastPattern)
        m_pGlobal->pLastPattern->pRight = p;    
    if(!m_pGlobal->pFirstPattern)
        m_pGlobal->pFirstPattern = p;    
    m_pGlobal->pLastPattern = p;
    
    return p;
}    

/****************************************************************
* CreateSamePattern : creation d'une nouvelle sequence identique
* à la séquence pSel
*
****************************************************************/

TPattern* CSequencer::CreateSamePattern(TPattern * pSel)
{
    if(!pSel)
        return NULL;
    
    TPattern * p;
    p = new TPattern;
    if(!p)
        return NULL;
        
    CopyMemory(p, pSel, sizeof(TPattern));    
    p->id = 0;
    p->idList = 0;
    p->pRight = NULL;
    p->pLeft = m_pGlobal->pLastPattern;
    if(!strncmp("Copie", pSel->szTitle, 5))
        lstrcpy(p->szTitle, pSel->szTitle);
    else
        wsprintf(p->szTitle, "Copie %s", pSel->szTitle);
    
    if(m_pGlobal->pLastPattern)
        m_pGlobal->pLastPattern->pRight = p;
    
    if(!m_pGlobal->pFirstPattern)
        m_pGlobal->pFirstPattern = p;
    
    m_pGlobal->pLastPattern = p;
    
    p->pFirstEvent = NULL;
    p->pLastEvent = NULL;
    CopyAllEvent(p, pSel);
    return p;
}

/****************************************************************
* MergePattern : fusionne une sequence à celle qui se trouve à
* droite s'il en existe
*
****************************************************************/

BOOL CSequencer::MergePattern(TPattern * pMerge)
{
    TPattern *p, *pSel = NULL;
    int  dist = 0x7FFFFFFF;
    
    if((!pMerge)||(!m_pGlobal))
        return FALSE;
    
    p = m_pGlobal->pFirstPattern;
    while(p)
    {
        if((pMerge!=p)&&(pMerge->numTrack==p->numTrack)&&(pMerge->left<=p->left))
        {
            if((!pSel)||(dist>p->left))
            {
                dist = p->left;
                pSel = p;
            }    
        }    
        p = p->pRight;
    }
    if(!pSel)
        return FALSE;
    
    // on relie à la fin de la queue du noeud le 1er objet de sequence qui se trouve à droite
    CObjectEvent * pe = pSel->pFirstEvent;
    if(pe)
        pe->pLeft = pMerge->pLastEvent;
    if(pMerge->pLastEvent)
        pMerge->pLastEvent->pRight = pe;
    if(!pMerge->pFirstEvent)
        pMerge->pFirstEvent = pe;
    if(pSel->pLastEvent)
        pMerge->pLastEvent = pSel->pLastEvent;
    
    // on modifie la longueur de la sequence
    if(pMerge->right<pSel->right)
        pMerge->right = pSel->right;
    
    // on supprime la sequence à droite sans supprimer les objets
    DeletePattern(pSel, FALSE);
    
    return TRUE;
}        

  

/****************************************************************
* 
*
****************************************************************/

void  CSequencer::UpdateIDPattern(int idRef)
{
    TPattern * p;
    if(!m_pGlobal)
        return;
    
    p = m_pGlobal->pFirstPattern;
    while(p)
    {
        if(p->id > idRef)
            p->id--;
        if(p->idList > idRef)
            p->idList--;
        p = p->pRight;
    }
}    


/*******************************************************************
* CopyAllEvent :  copie tous les evenements d'une sequence dans une
* autre sequence
*
*******************************************************************/

BOOL CSequencer::CopyAllEvent(TPattern * pCible, TPattern * pSource)
{
    BOOL bRedraw = FALSE;
    if((!pSource)||(!pCible))
        return FALSE;

    CObjectEvent * p;
    CObjectEvent * pn = pSource->pFirstEvent;
    while(pn)
    {
        p = NULL; 
        switch(pn->GetType())
        {
            case MIDI_NOTEON:
                p = new CObjectEventNote;
                if(!p) return FALSE;
                CopyMemory(p, pn, sizeof(CObjectEventNote));
                break;
            case MIDI_PITCHBEND:
                p = new CObjectEventPitchBend;
                if(!p) return FALSE;
                CopyMemory(p, pn, sizeof(CObjectEventPitchBend));
                break;
            case MIDI_CHANPRESS:
                p = new CObjectEventChannelPressure;
                if(!p) return FALSE;
                CopyMemory(p, pn, sizeof(CObjectEventChannelPressure));
                break;
            case MIDI_KEYAFTERTOUCH:
                p = new CObjectEventKeyAfterTouch;
                if(!p) return FALSE;
                CopyMemory(p, pn, sizeof(CObjectEventKeyAfterTouch));
                break;
            case MIDI_CTRLCHANGE:
                p = new CObjectEventControlChange;
                if(!p) return FALSE;
                CopyMemory(p, pn, sizeof(CObjectEventControlChange));
                ((CObjectEventControlChange*)p)->pControl = NULL;
                AddControlUnity(p, pCible->numTrack);
                break;
            case MIDI_PRGMCHANGE:
                p = new CObjectEventProgramChange;
                if(!p) return FALSE;
                CopyMemory(p, pn, sizeof(CObjectEventProgramChange));
                ((CObjectEventProgramChange*)p)->pControl = NULL;
                AddControlUnity(p, pCible->numTrack);
                break;
            default:
                break;
        }
        if(p)
        { 
            bRedraw = TRUE;
            p->pRight = NULL;
            p->pLeft = pCible->pLastEvent;    
            if(pCible->pLastEvent)
                pCible->pLastEvent->pRight = p;    
            if(!pCible->pFirstEvent)
                pCible->pFirstEvent = p;    
            pCible->pLastEvent = p;
        }    
        pn = pn->pRight;
    }
    return bRedraw;    
}

/*****************************************************************************
* ScreenToTimeEvent : convertit les coordonnées écrans en mesure temps
*
****************************************************************************/    

int CSequencer::ScreenToTimeEvent(int x)
{
    int k = x - 10 - m_Ctrl.xOrigine;
    
    return ((k*(int)m_Ctrl.dwTimeTick)/m_Ctrl.cxTick);
}   

/****************************************************************************
* ScreenToNumTrack : convertit les coordonnées écrans en numéro de piste
*
****************************************************************************/

int CSequencer::ScreenToNumTrack(int y)
{
    int k = (y - m_Ctrl.yOrigine)/m_Ctrl.cyTrack;
    if((k<0)||(k>=m_Ctrl.nTrackCount))
        return -1;
    
    return k;
}

/*********************************************************
* ScreenToPattern : retourne l'adresse mémoire de la
* sequence pointée par le curseur (x,y)
*
*********************************************************/

TPattern * CSequencer::ScreenToPattern(int x, int y, UINT * pZone)
{
    int a, b;
    a = ScreenToTimeEvent(x);
    b = ScreenToNumTrack(y);
    if((a<0)||(b<0))
    {
        if(pZone)
            *pZone = ZONE_NULL;
        return NULL;
    }    
    
    TPattern *p;
    p = m_pGlobal->pFirstPattern;
    while(p)
    {
        if((p->numTrack==b)&&(p->left<=a)&&(p->right>=a))
        {
            if((pZone)&&(a>=p->left)&&(a<p->right - (int)m_Ctrl.dwTimeTick/3))
                *pZone = ZONE_MOVING;
            else if((pZone)&&(a<=p->right)&&(a>=p->right - (int)m_Ctrl.dwTimeTick/3))
                *pZone = ZONE_SIZING;
            return p;
        }    
        p = p->pRight;
    }
    if(pZone)
        *pZone = ZONE_NULL;
    return NULL;
}    

/************************************************************
* SelectPattern : séléctionner une ou plusieures sequences
* pointées par (x,y)
*   bMultiple(in) : TRUE si on veut séléctionner plusieures
*     sequences
*   retourne l'adresse de dernière sequence séléctionnée
*
************************************************************/

TPattern * CSequencer::SelectPattern(int x, int y, BOOL bMultiple, UINT * pZone)
{
    TPattern * p;
    
    p = ScreenToPattern(x, y, pZone);
    if(!p)
    {
        if(!bMultiple)
            DeselectedAllPattern();
        m_pPatternSelected = NULL;
        return NULL;
    }
    if(!((p->bSelected)||(bMultiple)))
        DeselectedAllPattern();
           
    p->bSelected = TRUE;
    m_pPatternSelected = p;
    return p;
}    



/*************************************************************
* IsCutNote : cette fonction sert à verifier si pendant le
* redimensionnement d'une sequence, la position de curseur
* est inférieur à une des notes comprises dans la sequence
*
*************************************************************/

BOOL CSequencer::IsCutNote(TPattern * p, int cursor)
{
    CObjectEvent * pn;
    pn = p->pFirstEvent;
    while(pn)
    {
        if(((pn->GetType()==MIDI_NOTEON)&&(cursor<=((CObjectEventNote*)pn)->right))||
        (cursor<=pn->left))
            return TRUE;
        pn = pn->pRight;
    }    
    return FALSE;
}    



/************************************************************
* DeletePattern : supprime une sequence dans la liste
*
************************************************************/

void CSequencer::DeletePattern(TPattern * pDel, BOOL bEvent)
{
    TPattern * p;
    
    if(!pDel)
        return;
    
    // avant de supprimer une séquence on doit changer tous les noeuds de sequence suivante et
    // précedente
    
    if(pDel==m_pPatternSelected)
        m_pPatternSelected = NULL;
    
    p = pDel->pLeft;
    if(p)
        p->pRight = pDel->pRight;
    
    p = pDel->pRight;
    if(p)
        p->pLeft = pDel->pLeft;
    
    if(m_pGlobal->pFirstPattern==pDel)
        m_pGlobal->pFirstPattern = pDel->pRight;
    if(m_pGlobal->pLastPattern==pDel)
        m_pGlobal->pLastPattern = pDel->pLeft;
    
    int idBuf = pDel->id;
    
    // supprime tous les evenements    
    if(bEvent)
        DeleteAllEvent(pDel);
    
    // supprime la sequence    
    delete pDel;
}    


void CSequencer::DeselectedAllPattern()
{
    TPattern *p;
    p = m_pGlobal->pFirstPattern;
    while(p)
    {
        p->bSelected = FALSE;
        p = p->pRight;
    }    
}    

/********************************************************************************
* DeleteAll : libération de toutes les ressources utilisées
*
********************************************************************************/

void CSequencer::DeleteAll()
{
    TPattern * p, * pBuf;
    CObjectEvent * pe, *peBuf;
    int i;
    
    if(m_pGlobal)
    {
        // libérer liste sequences
        p = m_pGlobal->pFirstPattern;
        while(p)
        {
            pBuf = p->pRight;
            DeletePattern(p, TRUE);
            p = pBuf;
        }
        
        for(i=0; i<MAX_CHANNEL; i++)
        {
            pe = m_pGlobal->pFirstAll[i];
            while(pe)
            {
                peBuf = pe->pRight;
                delete pe;
                pe = peBuf;
            }    
        }    
        // libérer liste tempo
        pe = m_pGlobal->pFirstTempo;
        while(pe)
        {
            peBuf = pe->pRight;
            delete pe;
            pe = peBuf;
        }
        // libérer liste signature
        pe = m_pGlobal->pFirstSignature;
        while(pe)
        {
            peBuf = pe->pRight;
            delete pe;
            pe = peBuf;
        }
        // libérer liste meta
        pe = m_pGlobal->pFirstMeta;
        while(pe)
        {
            peBuf = pe->pRight;
            delete pe;
            pe = peBuf;
        }
        // libérer liste d'evenement temporaire        
        for(i=0; i<MAX_CHANNEL; i++)
           delete m_pGlobal->pTempNameTrack[i];
        
        // libérer liste control
        TControlUnity * pu = m_pGlobal->pFirstControl;
        TControlUnity * puBuf;
        while(pu)
        {
            puBuf = pu->pRight;
            delete pu;
            pu = puBuf;
        }
        // reinitialiser les valeurs des membres de m_pGlobal
        ZeroMemory(m_pGlobal, sizeof(TGlobal));
    }
    FreeListObject();    
}

/*******************************************************************
* CreateNote : création d'une nouvelle note
*
*******************************************************************/

CObjectEvent * CSequencer::CreateNote(TPattern * pPtrn)
{
    if(!pPtrn)
        return NULL;
    
    CObjectEventNote * p;
    p = new CObjectEventNote;
    if(!p)
        return NULL;
    
    p->left = pPtrn->left;
    p->right = pPtrn->right;
    p->bSelected = FALSE;
    p->note = 36;
    p->velocity = 100;
    p->pLeft = pPtrn->pLastEvent;
    
    if(pPtrn->pLastEvent)
        pPtrn->pLastEvent->pRight = p;
    
    if(!pPtrn->pFirstEvent)
        pPtrn->pFirstEvent = p;
    
    pPtrn->pLastEvent = p;
    
    return p;
}

/****************************************************************
* ScreenToTimeEvent : convertit la coordonnée abcisse de l'écran
* en mesure temps
*
****************************************************************/

int CSequencer::ScreenToTimeEvent(int x, TEditorData * pData)
{
    int k = x - 10 - pData->xo;
    if(k<0)
        return -1;
    
    return ((k*(int)m_Ctrl.dwTimeTick)/pData->cxTick);
}

/****************************************************************
* ScreenToNoteValue : convertit l'ordonnée de l'écran en indice
* de note
*
****************************************************************/

int CSequencer::ScreenToNoteValue(int y, TEditorData * pData)
{
    int octave, note;
    
    octave = 9 - (y - pData->yo)/120;
    note = 11 - ((y - pData->yo)%120)/10;
    note += (octave*12);
    if((octave<0)||(note>127))
        return -1;
    
    return note;
}

/*********************************************************
* ScreenToNoteObject : retourne l'adresse mémoire de la
* note pointée par le curseur (x,y)
*
*********************************************************/

CObjectEventNote * CSequencer::ScreenToNoteObject(int x, int y, TEditorData * pData, UINT * pZone)
{
    int a, b;
    a = ScreenToTimeEvent(x, pData);
    b = ScreenToNoteValue(y, pData);
    if((a<0)||(b<0))
    {
        if(pZone)
            *pZone = ZONE_NULL;
        return NULL;
    }    
    
    
    CObjectEvent * pe;
    CObjectEventNote * p;
    pe = pData->pPtrn->pFirstEvent;
    while(pe)
    {
        if(pe->GetType()==MIDI_NOTEON)
        {
            p = (CObjectEventNote*)pe;
        if((p->note==b)&&(p->left<=a)&&(p->right>=a))
        {
            if((pZone)&&(a>=p->left)&&(a<p->right - (int)m_Ctrl.dwTimeTick/12))
                *pZone = ZONE_MOVING;
            else if((pZone)&&(a<=p->right)&&(a>=p->right - (int)m_Ctrl.dwTimeTick/12))
                *pZone = ZONE_SIZING;
            return p;
        }
        }        
        pe = pe->pRight;
    }
    if(pZone)
        *pZone = ZONE_NULL;
    return NULL;
}


/*************************************************************
* DeleteAllEvent : supprime tous les evenements dans la 
* sequence pDel
* 
*************************************************************/

void CSequencer::DeleteAllEvent(TPattern * pDel)
{
    if(!pDel)
        return;
    
    CObjectEvent * p, *pBuf;
    p = pDel->pFirstEvent;
    while(p)
    {
        pBuf = p->pRight;
        // on verifie si un objet CtrlChange ou PrgmChange. Si oui on supprime dans
        // la liste des controles 
        if(p->GetType()==MIDI_CTRLCHANGE)
            DeleteControlUnity(((CObjectEventControlChange*)p)->pControl);
        else if(p->GetType()==MIDI_PRGMCHANGE)
            DeleteControlUnity(((CObjectEventProgramChange*)p)->pControl);
        delete p;
        p = pBuf;
    }    
}


/*******************************************************************
* CreatePitchBend : création d'un objet Pitch Bend
*
*******************************************************************/

CObjectEvent * CSequencer::CreatePitchBend(TPattern * pPtrn)
{
    if(!pPtrn)
        return NULL;
    
    CObjectEventPitchBend * p;
    p = new CObjectEventPitchBend;
    if(!p)
        return NULL;
    
    p->left = pPtrn->left;
    p->bSelected = FALSE;
    p->value1 = 0;
    p->value2 = 64; // centre 0x40
    p->pLeft = pPtrn->pLastEvent;
    
    if(pPtrn->pLastEvent)
        pPtrn->pLastEvent->pRight = p;
    
    if(!pPtrn->pFirstEvent)
        pPtrn->pFirstEvent = p;
    
    pPtrn->pLastEvent = p;
    
    return p;
}

/*******************************************************************
* CreateKeyAfterTouch : création d'un objet Key After Touch
*
*******************************************************************/

CObjectEvent * CSequencer::CreateKeyAfterTouch(TPattern * pPtrn)
{
    if(!pPtrn)
        return NULL;
    
    CObjectEventKeyAfterTouch * p;
    p = new CObjectEventKeyAfterTouch;
    if(!p)
        return NULL;
    
    p->left = pPtrn->left;
    p->bSelected = FALSE;
    p->note = 0;
    p->velocity = 0;
    p->pLeft = pPtrn->pLastEvent;
    
    if(pPtrn->pLastEvent)
        pPtrn->pLastEvent->pRight = p;
    
    if(!pPtrn->pFirstEvent)
        pPtrn->pFirstEvent = p;
    
    pPtrn->pLastEvent = p;
    
    return p;
}

/*******************************************************************
* CreateCtrlChange : création d'un objet Control Change
*
*******************************************************************/

CObjectEvent * CSequencer::CreateControlChange(TPattern * pPtrn)
{
    if(!pPtrn)
        return NULL;
    
    CObjectEventControlChange * p;
    p = new CObjectEventControlChange;
    if(!p)
        return NULL;
    
    p->left = pPtrn->left;
    p->bSelected = FALSE;
    p->numController = 7;
    p->value = 100;
    p->pLeft = pPtrn->pLastEvent;
    
    if(pPtrn->pLastEvent)
        pPtrn->pLastEvent->pRight = p;
    
    if(!pPtrn->pFirstEvent)
        pPtrn->pFirstEvent = p;
    
    pPtrn->pLastEvent = p;
    
    return p;
}

/*******************************************************************
* CreateProgramChange : création d'un objet Program Change
*
*******************************************************************/

CObjectEvent * CSequencer::CreateProgramChange(TPattern * pPtrn)
{
    if(!pPtrn)
        return NULL;
    
    CObjectEventProgramChange * p;
    p = new CObjectEventProgramChange;
    if(!p)
        return NULL;
    
    p->left = pPtrn->left;
    p->bSelected = FALSE;
    p->numProgram = 0;
    p->pLeft = pPtrn->pLastEvent;
    
    if(pPtrn->pLastEvent)
        pPtrn->pLastEvent->pRight = p;    
    if(!pPtrn->pFirstEvent)
        pPtrn->pFirstEvent = p;    
    pPtrn->pLastEvent = p;
    
    return p;
}

/*******************************************************************
* CreateChannelPressure : création d'un objet Channel Pressure
*
*******************************************************************/

CObjectEvent * CSequencer::CreateChannelPressure(TPattern * pPtrn)
{
    if(!pPtrn)
        return NULL;
    
    CObjectEventChannelPressure * p;
    p = new CObjectEventChannelPressure;
    if(!p)
        return NULL;
    
    p->left = pPtrn->left;
    p->bSelected = FALSE;
    p->value = 0;
    p->pLeft = pPtrn->pLastEvent;
    
    if(pPtrn->pLastEvent)
        pPtrn->pLastEvent->pRight = p;
    
    if(!pPtrn->pFirstEvent)
        pPtrn->pFirstEvent = p;
    
    pPtrn->pLastEvent = p;
    
    return p;
}

/****************************************************************
* ImportMidiFile : chargement d'un fichier MIDI
*   pFileName(in) : pointeur sur le nom de fichier
*
****************************************************************/

BOOL CSequencer::ImportMidiFile(const char * pFileName)
{
    if(!pFileName)
        return FALSE;
    
    HANDLE hFile;
    DWORD  dwSize, dwRead;
    int count, countEvent, i, j;
    
    // ouvrir un fichier prêt pour la lecture
    
    hFile = CreateFile(pFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, 0);
    
    if(hFile==INVALID_HANDLE_VALUE)
        return FALSE;
    
    char  szBuf[12];
    DWORD dwBuf;
    int   buf1, buf2, buf3, buf4;
    TMidiFileHdr hdr;
    
    // verifier l'entete s'il contient l'identification "MThd"
    ReadFile(hFile, &dwBuf, 4, &dwRead, NULL);
    if(dwBuf!=0x6468544D)
    {
        CloseHandle(hFile);
        return FALSE;
    }
    // verifier la taille de l'entete
    ReadFile(hFile, &dwBuf, 4, &dwRead, NULL);
    dwBuf = DwordSwap(dwBuf);
    if(dwBuf!=sizeof(TMidiFileHdr))
    {
        CloseHandle(hFile);
        return FALSE;
    }
    // recupérer l'entete
    ReadFile(hFile, &hdr, sizeof(TMidiFileHdr), &dwRead, NULL);

    hdr.wFormat = WordSwap(hdr.wFormat);
    hdr.wTrackCount = WordSwap(hdr.wTrackCount);
    hdr.wTimeTicks = WordSwap(hdr.wTimeTicks);
    
    // ici on ne traite que le format 0 et 1
    if((hdr.wFormat>1)||(hdr.wTrackCount==0)||(hdr.wTimeTicks==0))
    {
        CloseHandle(hFile);
        return FALSE;
    }
    m_Ctrl.dwTimeTick = (DWORD)hdr.wTimeTicks;
    
    // traitement de bloc de piste
    DWORD dwLenght, dwTime;
    LPBYTE pData = NULL;
    LPBYTE pBuf;
    m_maxLenght = 0;
  
    for(i=0; i<(int)hdr.wTrackCount ; i++)
    {
        // verifier l'entete s'il contient l'identification "MTrk"
        ReadFile(hFile, &dwBuf, 4, &dwRead, NULL);
        if(dwBuf!=0x6B72544D)
        {
            CloseHandle(hFile);
            return FALSE;
        }
        //recupérer la taille de donnée
        ReadFile(hFile, &dwLenght, 4, &dwRead, NULL);
        dwLenght = DwordSwap(dwLenght);
        
        // allouer des memoires pour recupérer les données
        pData = (LPBYTE)malloc(dwLenght);
        if(!pData)
        {
            CloseHandle(hFile);
            return FALSE;
        }
        // recupérer les données
        ReadFile(hFile, pData, dwLenght, &dwRead, NULL);
        
        // traitement des données
        dwTime = 0;
        m_pOldPattern = NULL;
        m_byStatus = 0;
        m_szNameTrack[0] = 0;
        
        for(pBuf=pData; pBuf<pData+dwLenght; pBuf++)
        {
            dwTime += GetVarLen(&pBuf);
            pBuf++;
            CollectMidiData(&pBuf, dwTime);
        }
                
        // libération des memoires
        free(pData);
        pData = NULL;
    }
    m_Ctrl.nLastLocator = m_maxLenght;
    CloseHandle(hFile);
    lstrcpy(m_szFileImport, pFileName);
    return TRUE;
}    

/******************************************************************************
* CollectMidiData :
*
******************************************************************************/

BOOL CSequencer::CollectMidiData(LPBYTE * pp, DWORD dwTime)
{
    int i;
    if((**pp)==MIDI_META)
    {
        (*pp)++;
        CollectMidiMeta(pp, dwTime);
        m_byStatus = MIDI_META;
    }
    else
    {
        switch((**pp) & 0xF0)
        {
            case MIDI_NOTEON:
                m_byStatus = MIDI_NOTEON;
                CollectMidiNote(pp, dwTime, FALSE);
                break;
            case MIDI_NOTEOFF:
                m_byStatus = MIDI_NOTEOFF;
                CollectMidiNote(pp, dwTime, FALSE);
                break;
            case MIDI_PRGMCHANGE:
                m_byStatus = MIDI_PRGMCHANGE;
                CollectMidiPrgmChange(pp, dwTime, FALSE);
                break;
            case MIDI_CTRLCHANGE:
                CollectMidiCtrlChange(pp, dwTime, FALSE);
                m_byStatus = MIDI_CTRLCHANGE;
                break;
            case MIDI_KEYAFTERTOUCH:
                CollectMidiKeyAfterTouch(pp, dwTime, FALSE);
                m_byStatus = (BYTE)0xA0;
                break;
            case MIDI_CHANPRESS:
                CollectMidiChannelPressure(pp, dwTime, FALSE);
                m_byStatus = (BYTE)0xD0;
                break;
            case MIDI_PITCHBEND:
                CollectMidiPitchBend(pp, dwTime, FALSE);
                m_byStatus = MIDI_PITCHBEND;
                break;
            case 0xF0: // systeme exclusif
                do
                {
                    (*pp)++;
                }while((**pp)!=0xF7);
                m_byStatus = 0;
                break;
            default:
                if((((**pp) & 0x80)==0)&&((m_byStatus==MIDI_NOTEON)||(m_byStatus==MIDI_NOTEOFF)))
                    CollectMidiNote(pp, dwTime, TRUE);
                else if((((**pp) & 0x80)==0)&&(m_byStatus==MIDI_KEYAFTERTOUCH))
                    CollectMidiKeyAfterTouch(pp, dwTime, TRUE);
                else if((((**pp) & 0x80)==0)&&(m_byStatus==MIDI_PITCHBEND))
                    CollectMidiPitchBend(pp, dwTime, TRUE);
                else if((((**pp) & 0x80)==0)&&(m_byStatus==MIDI_CHANPRESS))
                    CollectMidiChannelPressure(pp, dwTime, TRUE);
                else if((((**pp) & 0x80)==0)&&(m_byStatus==MIDI_CTRLCHANGE))
                    CollectMidiCtrlChange(pp, dwTime, TRUE);
                else if((((**pp) & 0x80)==0)&&(m_byStatus==MIDI_PRGMCHANGE))
                    CollectMidiPrgmChange(pp, dwTime, TRUE);
                break;
        }    
    }        
    return TRUE;
}    

/******************************************************************************
* CollectMidiMeta :
*
******************************************************************************/

BOOL CSequencer::CollectMidiMeta(LPBYTE * pp, DWORD dwTime)
{
    DWORD dw ;
    int i;
    BYTE byMeta;
    
    switch(**pp)
    {
        case META_TEMPO:
            (*pp) += 2;
            dw = (((unsigned int)(**pp))<<16)|(((unsigned char)(*((*pp)+1)))<<8)|(*((*pp)+2));
            (*pp) += 2;
            SetTempo(dwTime, dw!=0 ? 60000000.0/dw : 120.0);
            break;
        
        case META_SIGNATURE:
            (*pp) += 2;
            SetTimeSignature(dwTime, *pp);
            (*pp) += 3;
            break;
            
        case META_TEXT:
        case META_COPYRIGHT:
        case META_LYRIC:
        case META_MARKER:
        case META_CUEPOINT:
            byMeta = (**pp);
            (*pp)++;
            i = (int)(**pp);
            SetTextEvent(byMeta, ((*pp)+1), i);
            (*pp) += i;
            break;
        
        case META_NAMETRACK:
            (*pp)++;
            i = (int)(**pp);
            CopyMemory(m_szNameTrack, (*pp)+1, i);
            m_szNameTrack[i] = 0;
            if(m_pOldPattern)
            {
                if(!strncmp(m_pOldPattern->szTitle, "MIDI", 4))
                    lstrcpy(m_pOldPattern->szTitle, m_szNameTrack);
            }    
            (*pp) += i;
            break;
        // ici on traite pas les données, on avance le pointeur suivant la longueur de donnée
        default:
            (*pp)++;
            i = (int)(**pp);
            (*pp) += i;
    }    
    return TRUE;
}    

/******************************************************************************
* CollectMidiNote :
*
******************************************************************************/

BOOL CSequencer::CollectMidiNote(LPBYTE * pp, DWORD dwTime, BOOL bCopie)
{
    TPattern * p = NULL;
    CObjectEvent * pe = NULL;
    CObjectEvent * pn = NULL;
    int nType;
    
    if(!bCopie)
    {
        // recuperer le numero de canal MIDI
        int nChannel = (int)((**pp) & 0x0F);
        nType = (int)((**pp) & 0xF0);
        // chercher si ce canal est déjà utilisé
        int i;
        TPatternValue patv;    
    
        p = m_pGlobal->pFirstPattern;
        while(p)
        {
            if(p->numTrack == nChannel)
                break;
            p = p->pRight;
        }
    
        if(!p)
        {
            patv.numTrack = nChannel;
            patv.left = (int)dwTime;
            patv.right = (int)dwTime;
            patv.bSelected = FALSE;
            patv.bRecord = FALSE;
            if(lstrlen(m_szNameTrack))
                lstrcpy(patv.szTitle, m_szNameTrack);
            else
                wsprintf(patv.szTitle, "MIDI %i", nChannel+1);
            p = CreatePattern(&patv);            
        }
        m_pOldPattern = p;
        (*pp)++;
    }
    else
    {
        p = m_pOldPattern;
        nType = (int)m_byStatus;
    }        
    
    int nNote, nVel;
    int lenghtNote;
    
    nNote = (int)(**pp);
    (*pp)++;
    nVel = (int)(**pp);
    if(nVel==0)
        nType = (int)MIDI_NOTEOFF;
    
    if(!p)
        return FALSE;
    
    lenghtNote = (int)dwTime + (int)m_Ctrl.dwTimeTick/24;
    
    if(nType ==(int)MIDI_NOTEON)
    {
        if(p->right<lenghtNote)
            p->right = lenghtNote;
        if(p->left>(int)dwTime)
            p->left = (int)dwTime;
        
        m_maxLenght = max(lenghtNote, m_maxLenght);
        pe = CreateNote(p);
        pe->left = (int)dwTime;
        ((CObjectEventNote*)pe)->right = lenghtNote;
        ((CObjectEventNote*)pe)->note = nNote;
        ((CObjectEventNote*)pe)->velocity = nVel;
        ((CObjectEventNote*)pe)->bSelected = FALSE;
        ((CObjectEventNote*)pe)->bDisabled = TRUE;
    }
    else
    {
        pe = p->pFirstEvent;
        while(pe)
        {
            if((((CObjectEventNote*)pe)->note==nNote)&&(pe->GetType()==MIDI_NOTEON)&&
            (((CObjectEventNote*)pe)->bDisabled))
                pn = pe;
            
            pe = pe->pRight;    
        }
        if(pn)
        {
            if(p->right<(int)dwTime)
                p->right = (int)dwTime;            
            
            m_maxLenght = max((int)dwTime, m_maxLenght);
            ((CObjectEventNote*)pn)->right = (int)dwTime;
            // pour éviter que la noteoff est executé avant noteon
            if(pn->left==((CObjectEventNote*)pn)->right)
                ((CObjectEventNote*)pn)->right++; 
            ((CObjectEventNote*)pn)->bDisabled = FALSE;
        }    
    }        
    
    return TRUE;
}    

/******************************************************************************
* CollectMidiPitchBend :
*
******************************************************************************/

BOOL CSequencer::CollectMidiPitchBend(LPBYTE * pp, DWORD dwTime, BOOL bCopie)
{
    TPattern * p = NULL;
    CObjectEvent * pe = NULL;
    
    if(!bCopie)
    {
        // recuperer le numero de canal MIDI
        int nChannel = (int)((**pp) & 0x0F);
    
        // chercher si ce canal est déjà utilisé
        int i;
        TPatternValue patv;    
    
        p = m_pGlobal->pFirstPattern;
        while(p)
        {
            if(p->numTrack == nChannel)
                break;
            p = p->pRight;
        }
    
        if(!p)
        {
            patv.numTrack = nChannel;
            patv.left = (int)dwTime;
            patv.right = (int)dwTime;
            patv.bSelected = FALSE;
            patv.bRecord = FALSE;
            if(lstrlen(m_szNameTrack))
                lstrcpy(patv.szTitle, m_szNameTrack);
            else
                wsprintf(patv.szTitle, "MIDI %i", nChannel+1);
            p = CreatePattern(&patv);            
        }
        m_pOldPattern = p;
        (*pp)++;
    }
    else
        p = m_pOldPattern;
    
    int val1, val2;
    
    val1 = (int)(**pp);
    (*pp)++;
    val2 = (int)(**pp);
        
    if(!p)
        return FALSE;
        
    if(p->right<(int)dwTime)
        p->right = (int)dwTime;
    m_maxLenght = max((int)dwTime, m_maxLenght);
    pe = CreatePitchBend(p);
    if(!pe)
        return FALSE;
    pe->left = (int)dwTime;
    ((CObjectEventPitchBend*)pe)->value1 = val1;
    ((CObjectEventPitchBend*)pe)->value2 = val2;
    ((CObjectEventPitchBend*)pe)->bSelected = FALSE;
    
    return TRUE;
}

/******************************************************************************
* CollectMidiKeyAfterTouch :
*
******************************************************************************/

BOOL CSequencer::CollectMidiKeyAfterTouch(LPBYTE * pp, DWORD dwTime, BOOL bCopie)
{
    TPattern * p = NULL;
    CObjectEvent * pe = NULL;
    
    if(!bCopie)
    {
        // recuperer le numero de canal MIDI
        int nChannel = (int)((**pp) & 0x0F);
    
        // chercher si ce canal est déjà utilisé
        int i;
        TPatternValue patv;    
    
        p = m_pGlobal->pFirstPattern;
        while(p)
        {
            if(p->numTrack == nChannel)
                break;
            p = p->pRight;
        }
    
        if(!p)
        {
            patv.numTrack = nChannel;
            patv.left = (int)dwTime;
            patv.right = (int)dwTime;
            patv.bSelected = FALSE;
            patv.bRecord = FALSE;
            if(lstrlen(m_szNameTrack))
                lstrcpy(patv.szTitle, m_szNameTrack);
            else
                wsprintf(patv.szTitle, "MIDI %i", nChannel+1);
            p = CreatePattern(&patv);            
        }
        m_pOldPattern = p;
        (*pp)++;
    }
    else
        p = m_pOldPattern;
    
    int val1, val2;    
    val1 = (int)(**pp);
    (*pp)++;
    val2 = (int)(**pp);
        
    if(!p)
        return FALSE;
        
    if(p->right<(int)dwTime)
        p->right = (int)dwTime;
    m_maxLenght = max((int)dwTime, m_maxLenght);
    pe = CreateKeyAfterTouch(p);
    if(!pe)
        return FALSE;
    pe->left = (int)dwTime;
    ((CObjectEventKeyAfterTouch*)pe)->note = val1;
    ((CObjectEventKeyAfterTouch*)pe)->velocity = val2;
    ((CObjectEventKeyAfterTouch*)pe)->bSelected = FALSE;
    
    return TRUE;
}

/******************************************************************************
* CollectMidiChannelPressure :
*
******************************************************************************/

BOOL CSequencer::CollectMidiChannelPressure(LPBYTE * pp, DWORD dwTime, BOOL bCopie)
{
    TPattern * p = NULL;
    CObjectEvent * pe = NULL;
    
    if(!bCopie)
    {
        // recuperer le numero de canal MIDI
        int nChannel = (int)((**pp) & 0x0F);
    
        // chercher si ce canal est déjà utilisé
        int i;
        TPatternValue patv;    
    
        p = m_pGlobal->pFirstPattern;
        while(p)
        {
            if(p->numTrack == nChannel)
                break;
            p = p->pRight;
        }
    
        if(!p)
        {
            patv.numTrack = nChannel;
            patv.left = (int)dwTime;
            patv.right = (int)dwTime;
            patv.bSelected = FALSE;
            patv.bRecord = FALSE;
            if(lstrlen(m_szNameTrack))
                lstrcpy(patv.szTitle, m_szNameTrack);
            else
                wsprintf(patv.szTitle, "MIDI %i", nChannel+1);
            p = CreatePattern(&patv);
        }
        m_pOldPattern = p;
        (*pp)++;
    }
    else
        p = m_pOldPattern; 
    
    int val1;
    val1 = (int)(**pp);
        
    if(!p)
        return FALSE;
        
    if(p->right<(int)dwTime)
        p->right = (int)dwTime;
    m_maxLenght = max((int)dwTime, m_maxLenght);
    pe = CreateChannelPressure(p);
    if(!pe)
        return FALSE;
    pe->left = (int)dwTime;
    ((CObjectEventChannelPressure*)pe)->value = val1;
    ((CObjectEventChannelPressure*)pe)->bSelected = FALSE;
    
    return TRUE;
}

/******************************************************************************
* CollectMidiPrgmChange :
*
******************************************************************************/

BOOL CSequencer::CollectMidiPrgmChange(LPBYTE * pp, DWORD dwTime, BOOL bCopie)
{
    TPattern * p = NULL;
    CObjectEvent * pe = NULL;
    
    if(!bCopie)
    {
        // recuperer le numero de canal MIDI
        int nChannel = (int)((**pp) & 0x0F);
    
        // chercher si ce canal est déjà utilisé
        int i;
        TPatternValue patv;    
    
        p = m_pGlobal->pFirstPattern;
        while(p)
        {
            if(p->numTrack == nChannel)
                break;
            p = p->pRight;
        }
    
        if(!p)
        {
            patv.numTrack = nChannel;
            patv.left = (int)dwTime;
            patv.right = (int)dwTime;
            patv.bSelected = FALSE;
            patv.bRecord = FALSE;
            if(lstrlen(m_szNameTrack))
                lstrcpy(patv.szTitle, m_szNameTrack);
            else
                wsprintf(patv.szTitle, "MIDI %i", nChannel+1);
            p = CreatePattern(&patv);            
        }
        m_pOldPattern = p;
        (*pp)++;
    }
    else
        p = m_pOldPattern;
    
    int val1;    
    val1 = (int)(**pp);
        
    if(!p)
        return FALSE;
        
    if(p->right<(int)dwTime)
        p->right = (int)dwTime;
    if(p->left>(int)dwTime)
            p->left = (int)dwTime;
    m_maxLenght = max((int)dwTime, m_maxLenght);
    pe = CreateProgramChange(p);
    if(!pe)
        return FALSE;
    pe->left = (int)dwTime;
    ((CObjectEventProgramChange*)pe)->numProgram = val1;
    ((CObjectEventProgramChange*)pe)->bSelected = FALSE;
    if(dwTime==0)
        SetPrgmChange(p->numTrack, 0, val1);
    // ajoute dans la liste controle
    AddControlUnity(pe, p->numTrack);
    
    return TRUE;
}    

/******************************************************************************
* CollectMidiCtrlChange :
*
******************************************************************************/

BOOL CSequencer::CollectMidiCtrlChange(LPBYTE * pp, DWORD dwTime, BOOL bCopie)
{
    TPattern * p = NULL;
    CObjectEvent * pe = NULL;
    
    if(!bCopie)
    {
        // recuperer le numero de canal MIDI
        int nChannel = (int)((**pp) & 0x0F);
    
        // chercher si ce canal est déjà utilisé
        int i;
        TPatternValue patv;    
    
        p = m_pGlobal->pFirstPattern;
        while(p)
        {
            if(p->numTrack == nChannel)
                break;
            p = p->pRight;
        }
    
        if(!p)
        {
            patv.numTrack = nChannel;
            patv.left = (int)dwTime;
            patv.right = (int)dwTime;
            patv.bSelected = FALSE;
            patv.bRecord = FALSE;
            if(lstrlen(m_szNameTrack))
                lstrcpy(patv.szTitle, m_szNameTrack);
            else
                wsprintf(patv.szTitle, "MIDI %i", nChannel+1);
            p = CreatePattern(&patv);            
        }
        m_pOldPattern = p;
        (*pp)++;
    }
    else
        p = m_pOldPattern;
    
    int val1, val2;    
    val1 = (int)(**pp);
    (*pp)++;
    val2 = (int)(**pp);
        
    if(!p)
        return FALSE;
        
    if(p->right<(int)dwTime)
        p->right = (int)dwTime;
    if(p->left>(int)dwTime)
            p->left = (int)dwTime;
    m_maxLenght = max((int)dwTime, m_maxLenght);
    pe = CreateControlChange(p);
    if(!pe)
        return FALSE;
    pe->left = (int)dwTime;
    ((CObjectEventControlChange*)pe)->numController = val1;
    ((CObjectEventControlChange*)pe)->value = val2;
    ((CObjectEventControlChange*)pe)->bSelected = FALSE;
    // ajoute dans la liste controle
    AddControlUnity(pe, p->numTrack);
    
    return TRUE;
}

/******************************************************************************
* GetVarLen :
*
******************************************************************************/

DWORD CSequencer::GetVarLen(LPBYTE * pp)
{
    if((!pp)||(!(*pp)))
        return 0;
    DWORD dwValue;
    
    dwValue = (DWORD)(**pp);
    if(dwValue & 0x80)
    {
        dwValue &= 0x7F;
        do
        {
            (*pp)++;
            dwValue = (dwValue<<7) + ((**pp) & 0x7F);
        }while((**pp) & 0x80);    
    }    
    return dwValue;
}

/*******************************************************************************
* AddListObject : ajoute une reference d'objet dans la liste avant exportation
* en fichier MIDI
*
*******************************************************************************/

BOOL CSequencer::AddListObject(TListObject * pList, TReferenceObject * p)
{
    // pour éviter l'extension de mémoire à chaque fois qu'on ajoute une liste,
    // on alloue un paquet de 100 listes
    
    if(!pList->pRef)
    {
        pList->pRef = (TReferenceObject*)malloc(100 * sizeof(TReferenceObject));
        if(pList->pRef)
            pList->arraySize = 100;
        else
            return FALSE;
    }
    
    TReferenceObject * pBuf;
    
    if(pList->count >= pList->arraySize)
    {
        pBuf = (TReferenceObject*)realloc(pList->pRef,
            (pList->arraySize + 100) * sizeof(TReferenceObject));
        if(pBuf)
        {
            pList->pRef = pBuf;
            pList->arraySize += 100;
        }    
        else
            return FALSE;
    }
    
    CopyMemory(&pList->pRef[pList->count], p, sizeof(TReferenceObject));
    pList->count++;
    return TRUE;
}

/*******************************************************************************
* ExtractListObject : Extraire tous les objets dans la liste avant exportation
* en fichier MIDI
*
*******************************************************************************/

void CSequencer::ExtractListObject(int format)
{
    int i;
    TPattern * p;
    CObjectEvent * pe;
    CObjectEventNote * pn;
    TReferenceObject buffer;
    
    // libérer toutes les listes d'abord    
    FreeListObject();
    
    // verifier si format inexistant    
    if((format!=FORMAT_0)&&(format!=FORMAT_1))
        return;
    
    // extraire les noms des pistes
    for(i=0; i<m_Ctrl.nTrackCount; i++)
    {
        if(m_pGlobal->pTempNameTrack[i])
        {
            buffer.dwTime = 0;
            buffer.pObject = (CObjectEvent*)m_pGlobal->pTempNameTrack[i];
            buffer.channel = GetChannelTrack(i);
            buffer.reserved = 0;
            if(format==FORMAT_0)
                AddListObject(&m_mListMeta, &buffer);
            else
                AddListObject(&m_mList[i], &buffer);
        }    
    }    
    
    // extraire les evenements dans chaque piste    
    for(i=0; i<m_Ctrl.nTrackCount; i++)
    {
        pe = m_pGlobal->pFirstAll[i];
        while(pe)
        {
            buffer.dwTime = (DWORD)pe->left;
            buffer.pObject = pe;
            buffer.channel = GetChannelTrack(i);
            switch(pe->GetType())
            {
                case MIDI_CTRLCHANGE:
                    if(((CObjectEventControlChange*)pe)->numController==CTRLCHANGE_VOLUME)
                        buffer.reserved = m_Ctrl.nVolume[i];
                    else if((((CObjectEventControlChange*)pe)->numController==CTRLCHANGE_PAN)&&
                    (m_Ctrl.bPanActive[i]))
                        buffer.reserved = m_Ctrl.nPan[i] + 256;// si reserved>256 = pan activé
                    else
                        buffer.reserved = 0;
                    break;
                default:
                    buffer.reserved = 0;
            }
            
            if(format==FORMAT_0)
                AddListObject(&m_mListMeta, &buffer);
            else
                AddListObject(&m_mList[i], &buffer);
            pe = pe->pRight;
        }    
    }
    
    // extraire les objects dans chaque sequence    
    p = m_pGlobal->pFirstPattern;
    while(p)
    {
        if(!m_tTrack[p->numTrack].bMute)
        {
            pe = p->pFirstEvent;
            while(pe)
            {
                buffer.dwTime = (DWORD)pe->left;
                buffer.pObject = pe;
                buffer.channel = GetChannelTrack(p->numTrack);
                switch(pe->GetType())
                {
                    case MIDI_CTRLCHANGE:
                        if(((CObjectEventControlChange*)pe)->numController==CTRLCHANGE_VOLUME)
                            buffer.reserved = m_Ctrl.nVolume[p->numTrack];
                        else if((((CObjectEventControlChange*)pe)->numController==CTRLCHANGE_PAN)&&
                        (m_Ctrl.bPanActive[p->numTrack]))
                            buffer.reserved = m_Ctrl.nPan[p->numTrack] + 256;                        
                        else
                            buffer.reserved = 0;
                        break;
                    default:
                        buffer.reserved = 0;
                }
                if(format==FORMAT_0)
                    AddListObject(&m_mListMeta, &buffer);
                else
                    AddListObject(&m_mList[p->numTrack], &buffer);
                // extraire les evenements NoteOff
                if(pe->GetType()==MIDI_NOTEON)
                {
                    pn = (CObjectEventNote*)pe;
                    buffer.dwTime = (DWORD)pn->right;
                    buffer.pObject = pe;
                    buffer.reserved = 1;
                    buffer.channel = GetChannelTrack(p->numTrack);
                    if(format==FORMAT_0)
                    {
                        AddListObject(&m_mListMeta, &buffer);
                        m_mListMeta.bEnable = TRUE;
                    }
                    else
                    {    
                        AddListObject(&m_mList[p->numTrack], &buffer);
                        m_mList[p->numTrack].bEnable = TRUE;
                    }    
                }
            
                pe = pe->pRight;
            }
        }    
        p = p->pRight;    
    }
    
    // extraire les tempo
    pe = m_pGlobal->pFirstTempo;
    while(pe)
    {
        buffer.dwTime = (DWORD)pe->left;
        buffer.pObject = pe;
        buffer.reserved = 0;
        buffer.channel = 0;
        AddListObject(&m_mListMeta, &buffer);
        if(!m_mListMeta.bEnable)
            m_mListMeta.bEnable = TRUE;
        pe = pe->pRight;
    }
    // extraire les signature
    pe = m_pGlobal->pFirstSignature;
    while(pe)
    {
        buffer.dwTime = (DWORD)pe->left;
        buffer.pObject = pe;
        buffer.reserved = 0;
        buffer.channel = 0;
        AddListObject(&m_mListMeta, &buffer);
        if(!m_mListMeta.bEnable)
            m_mListMeta.bEnable = TRUE;
        pe = pe->pRight;
    }
    // extraire les meta texte
    pe = m_pGlobal->pFirstMeta;
    BYTE byType;
    while(pe)
    {
        byType = ((CObjectMetaEvent*)pe)->GetMetaType();
        if((!m_Ctrl.bInfoInclude)&&((byType==META_TEXT)||(byType==META_COPYRIGHT)||
        (byType==META_LYRIC)||(byType==META_MARKER)||(byType==META_CUEPOINT)))
        {
            pe = pe->pRight;
        }
        else
        {    
            buffer.dwTime = (DWORD)pe->left;
            buffer.pObject = pe;
            buffer.reserved = 0;
            buffer.channel = 0;
            AddListObject(&m_mListMeta, &buffer);
            if(!m_mListMeta.bEnable)
                m_mListMeta.bEnable = TRUE;
            pe = pe->pRight;
        }    
    }
    // maintenant trier suivant le temps d'evenement
    if(format==FORMAT_1)
        for(i=0; i<MAX_CHANNEL; i++)
            SortListObject(&m_mList[i]);
    
    SortListObject(&m_mListMeta);
}

/**************************************************************************
* SortListObject : tri les listes des objets avant exportation en fichier
* MIDI
*
**************************************************************************/

void  CSequencer::SortListObject(TListObject * pList)
{
    if((pList)&&(pList->pRef)&&(pList->bEnable))
    {
        qsort((void*)pList->pRef, pList->count, sizeof(TReferenceObject), CompareObject);
    }
}

/*******************************************************************************
* FreeListObject : libère les mémoires allouées aux listes d'objets
*
*******************************************************************************/

void  CSequencer::FreeListObject()
{
    for(int i=0; i<MAX_CHANNEL; i++)
    {
        if(m_mList[i].pRef)
            free(m_mList[i].pRef);
        ZeroMemory(&m_mList[i], sizeof(TListObject));
    }
    if(m_mListMeta.pRef)
        free(m_mListMeta.pRef);
    ZeroMemory(&m_mListMeta, sizeof(TListObject));   
} 

/******************************************************************************
*
*
******************************************************************************/

void  CSequencer::CreateTempNameTrack(int numTrack, char * pText)
{
    if((!pText)||(numTrack<0)||(numTrack>15)||(!m_pGlobal))
        return;
    
    // on verifie si on a déjà créer un objet sur la meme piste
    CObjectMetaEventText * p = m_pGlobal->pTempNameTrack[numTrack];
    if((p)&&(lstrlen(pText)>0))
        p->SetText(pText, lstrlen(pText));
    else if(lstrlen(pText)>0)
    {
        p = new CObjectMetaEventText(META_NAMETRACK);
        if(!p)
            return;
    
        p->left = 0;
        p->SetText(pText, lstrlen(pText));
        m_pGlobal->pTempNameTrack[numTrack] = p;    
    }    
}    


/***************************************************************************
* CompareObject : comparaison de 2 elements du ListObject pour le tri 
* au quicksort
*
***************************************************************************/

int __cdecl CompareObject(const void* t1, const void* t2)
{
    int delta = (int)((TReferenceObject*)t1)->dwTime - (int)((TReferenceObject*)t2)->dwTime;
    if(delta==0)
    {
        if((((TReferenceObject*)t1)->reserved==1)&&(((TReferenceObject*)t2)->reserved==0))
            return -1;
        if((((TReferenceObject*)t1)->reserved==0)&&(((TReferenceObject*)t2)->reserved==1))
            return 1;
    }    
    return delta;
}


