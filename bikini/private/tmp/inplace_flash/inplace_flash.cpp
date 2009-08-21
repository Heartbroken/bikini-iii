#include "inplace_flash.h"















// Code from PopCap (modified) --------------------------------------------------------------------


#pragma comment(lib, "comsuppw.lib")

//////////////////////////////////////////////////////////////////////////
// Interfaces imported from flash.ocx

#include <comdef.h>

#pragma pack(push, 8)

namespace ShockwaveFlashObjects 
{

//
// Forward references and typedefs
//

struct __declspec(uuid("d27cdb6b-ae6d-11cf-96b8-444553540000"))
/* LIBID */ __ShockwaveFlashObjects;
struct __declspec(uuid("d27cdb6c-ae6d-11cf-96b8-444553540000"))
/* dual interface */ IShockwaveFlash;
struct __declspec(uuid("d27cdb6d-ae6d-11cf-96b8-444553540000"))
/* dispinterface */ _IShockwaveFlashEvents;
struct /* coclass */ ShockwaveFlash;
struct /* coclass */ FlashProp;
struct __declspec(uuid("d27cdb70-ae6d-11cf-96b8-444553540000"))
/* interface */ IFlashFactory;
struct __declspec(uuid("d27cdb72-ae6d-11cf-96b8-444553540000"))
/* interface */ IFlashObjectInterface;
struct __declspec(uuid("a6ef9860-c720-11d0-9337-00a0c90dcaa9"))
/* interface */ IDispatchEx;
struct /* coclass */ FlashObjectInterface;

//
// Smart pointer typedef declarations
//

_COM_SMARTPTR_TYPEDEF(IShockwaveFlash, __uuidof(IShockwaveFlash));
_COM_SMARTPTR_TYPEDEF(_IShockwaveFlashEvents, __uuidof(_IShockwaveFlashEvents));
_COM_SMARTPTR_TYPEDEF(IFlashFactory, __uuidof(IFlashFactory));
_COM_SMARTPTR_TYPEDEF(IDispatchEx, __uuidof(IDispatchEx));
_COM_SMARTPTR_TYPEDEF(IFlashObjectInterface, __uuidof(IFlashObjectInterface));

//
// Type library items
//

struct __declspec(uuid("d27cdb6c-ae6d-11cf-96b8-444553540000"))
IShockwaveFlash : IDispatch
{
    //
    // Property data
    //

    __declspec(property(get=GetStacking,put=PutStacking))
    _bstr_t Stacking;
    __declspec(property(get=GetWMode,put=PutWMode))
    _bstr_t WMode;
    __declspec(property(get=GetMovie,put=PutMovie))
    _bstr_t Movie;
    __declspec(property(get=GetSAlign,put=PutSAlign))
    _bstr_t SAlign;
    __declspec(property(get=GetMenu,put=PutMenu))
    VARIANT_BOOL Menu;
    __declspec(property(get=GetQuality,put=PutQuality))
    int Quality;
    __declspec(property(get=GetLoop,put=PutLoop))
    VARIANT_BOOL Loop;
    __declspec(property(get=GetFrameNum,put=PutFrameNum))
    long FrameNum;
    __declspec(property(get=GetBase,put=PutBase))
    _bstr_t Base;
    __declspec(property(get=Getscale,put=Putscale))
    _bstr_t scale;
    __declspec(property(get=GetDeviceFont,put=PutDeviceFont))
    VARIANT_BOOL DeviceFont;
    __declspec(property(get=GetEmbedMovie,put=PutEmbedMovie))
    VARIANT_BOOL EmbedMovie;
    __declspec(property(get=GetBGColor,put=PutBGColor))
    _bstr_t BGColor;
    __declspec(property(get=GetQuality2,put=PutQuality2))
    _bstr_t Quality2;
    __declspec(property(get=GetReadyState))
    long ReadyState;
    __declspec(property(get=GetScaleMode,put=PutScaleMode))
    int ScaleMode;
    __declspec(property(get=GetAlignMode,put=PutAlignMode))
    int AlignMode;
    __declspec(property(get=GetBackgroundColor,put=PutBackgroundColor))
    long BackgroundColor;
    __declspec(property(get=GetTotalFrames))
    long TotalFrames;
    __declspec(property(get=GetPlaying,put=PutPlaying))
    VARIANT_BOOL Playing;
    __declspec(property(get=GetSWRemote,put=PutSWRemote))
    _bstr_t SWRemote;

    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall get_ReadyState (
        /*[out,retval]*/ long * thestate ) = 0;
      virtual HRESULT __stdcall get_TotalFrames (
        /*[out,retval]*/ long * numframes ) = 0;
      virtual HRESULT __stdcall get_Playing (
        /*[out,retval]*/ VARIANT_BOOL * Playing ) = 0;
      virtual HRESULT __stdcall put_Playing (
        /*[in]*/ VARIANT_BOOL Playing ) = 0;
      virtual HRESULT __stdcall get_Quality (
        /*[out,retval]*/ int * Quality ) = 0;
      virtual HRESULT __stdcall put_Quality (
        /*[in]*/ int Quality ) = 0;
      virtual HRESULT __stdcall get_ScaleMode (
        /*[out,retval]*/ int * scale ) = 0;
      virtual HRESULT __stdcall put_ScaleMode (
        /*[in]*/ int scale ) = 0;
      virtual HRESULT __stdcall get_AlignMode (
        /*[out,retval]*/ int * align ) = 0;
      virtual HRESULT __stdcall put_AlignMode (
        /*[in]*/ int align ) = 0;
      virtual HRESULT __stdcall get_BackgroundColor (
        /*[out,retval]*/ long * color ) = 0;
      virtual HRESULT __stdcall put_BackgroundColor (
        /*[in]*/ long color ) = 0;
      virtual HRESULT __stdcall get_Loop (
        /*[out,retval]*/ VARIANT_BOOL * Loop ) = 0;
      virtual HRESULT __stdcall put_Loop (
        /*[in]*/ VARIANT_BOOL Loop ) = 0;
      virtual HRESULT __stdcall get_Movie (
        /*[out,retval]*/ BSTR * path ) = 0;
      virtual HRESULT __stdcall put_Movie (
        /*[in]*/ BSTR path ) = 0;
      virtual HRESULT __stdcall get_FrameNum (
        /*[out,retval]*/ long * FrameNum ) = 0;
      virtual HRESULT __stdcall put_FrameNum (
        /*[in]*/ long FrameNum ) = 0;
      virtual HRESULT __stdcall SetZoomRect (
        /*[in]*/ long left,
        /*[in]*/ long top,
        /*[in]*/ long right,
        /*[in]*/ long bottom ) = 0;
      virtual HRESULT __stdcall Zoom (
        /*[in]*/ int factor ) = 0;
      virtual HRESULT __stdcall Pan (
        /*[in]*/ long x,
        /*[in]*/ long y,
        /*[in]*/ int mode ) = 0;
      virtual HRESULT __stdcall Play ( ) = 0;
      virtual HRESULT __stdcall Stop ( ) = 0;
      virtual HRESULT __stdcall Back ( ) = 0;
      virtual HRESULT __stdcall Forward ( ) = 0;
      virtual HRESULT __stdcall Rewind ( ) = 0;
      virtual HRESULT __stdcall StopPlay ( ) = 0;
      virtual HRESULT __stdcall GotoFrame (
        /*[in]*/ long FrameNum ) = 0;
      virtual HRESULT __stdcall CurrentFrame (
        /*[out,retval]*/ long * FrameNum ) = 0;
      virtual HRESULT __stdcall IsPlaying (
        /*[out,retval]*/ VARIANT_BOOL * Playing ) = 0;
      virtual HRESULT __stdcall PercentLoaded (
        /*[out,retval]*/ long * __MIDL_0011 ) = 0;
      virtual HRESULT __stdcall FrameLoaded (
        /*[in]*/ long FrameNum,
        /*[out,retval]*/ VARIANT_BOOL * loaded ) = 0;
      virtual HRESULT __stdcall FlashVersion (
        /*[out,retval]*/ long * version ) = 0;
      virtual HRESULT __stdcall get_WMode (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall put_WMode (
        /*[in]*/ BSTR pVal ) = 0;
      virtual HRESULT __stdcall get_SAlign (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall put_SAlign (
        /*[in]*/ BSTR pVal ) = 0;
      virtual HRESULT __stdcall get_Menu (
        /*[out,retval]*/ VARIANT_BOOL * pVal ) = 0;
      virtual HRESULT __stdcall put_Menu (
        /*[in]*/ VARIANT_BOOL pVal ) = 0;
      virtual HRESULT __stdcall get_Base (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall put_Base (
        /*[in]*/ BSTR pVal ) = 0;
      virtual HRESULT __stdcall get_scale (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall put_scale (
        /*[in]*/ BSTR pVal ) = 0;
      virtual HRESULT __stdcall get_DeviceFont (
        /*[out,retval]*/ VARIANT_BOOL * pVal ) = 0;
      virtual HRESULT __stdcall put_DeviceFont (
        /*[in]*/ VARIANT_BOOL pVal ) = 0;
      virtual HRESULT __stdcall get_EmbedMovie (
        /*[out,retval]*/ VARIANT_BOOL * pVal ) = 0;
      virtual HRESULT __stdcall put_EmbedMovie (
        /*[in]*/ VARIANT_BOOL pVal ) = 0;
      virtual HRESULT __stdcall get_BGColor (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall put_BGColor (
        /*[in]*/ BSTR pVal ) = 0;
      virtual HRESULT __stdcall get_Quality2 (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall put_Quality2 (
        /*[in]*/ BSTR pVal ) = 0;
      virtual HRESULT __stdcall LoadMovie (
        /*[in]*/ int layer,
        /*[in]*/ BSTR url ) = 0;
      virtual HRESULT __stdcall TGotoFrame (
        /*[in]*/ BSTR target,
        /*[in]*/ long FrameNum ) = 0;
      virtual HRESULT __stdcall TGotoLabel (
        /*[in]*/ BSTR target,
        /*[in]*/ BSTR label ) = 0;
      virtual HRESULT __stdcall TCurrentFrame (
        /*[in]*/ BSTR target,
        /*[out,retval]*/ long * FrameNum ) = 0;
      virtual HRESULT __stdcall TCurrentLabel (
        /*[in]*/ BSTR target,
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall TPlay (
        /*[in]*/ BSTR target ) = 0;
      virtual HRESULT __stdcall TStopPlay (
        /*[in]*/ BSTR target ) = 0;
      virtual HRESULT __stdcall SetVariable (
        /*[in]*/ BSTR name,
        /*[in]*/ BSTR value ) = 0;
      virtual HRESULT __stdcall GetVariable (
        /*[in]*/ BSTR name,
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall TSetProperty (
        /*[in]*/ BSTR target,
        /*[in]*/ int property,
        /*[in]*/ BSTR value ) = 0;
      virtual HRESULT __stdcall TGetProperty (
        /*[in]*/ BSTR target,
        /*[in]*/ int property,
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall TCallFrame (
        /*[in]*/ BSTR target,
        /*[in]*/ int FrameNum ) = 0;
      virtual HRESULT __stdcall TCallLabel (
        /*[in]*/ BSTR target,
        /*[in]*/ BSTR label ) = 0;
      virtual HRESULT __stdcall TSetPropertyNum (
        /*[in]*/ BSTR target,
        /*[in]*/ int property,
        /*[in]*/ double value ) = 0;
      virtual HRESULT __stdcall TGetPropertyNum (
        /*[in]*/ BSTR target,
        /*[in]*/ int property,
        /*[out,retval]*/ double * pVal ) = 0;
      virtual HRESULT __stdcall get_SWRemote (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall put_SWRemote (
        /*[in]*/ BSTR pVal ) = 0;
      virtual HRESULT __stdcall get_Stacking (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall put_Stacking (
        /*[in]*/ BSTR pVal ) = 0;
};

struct __declspec(uuid("d27cdb6d-ae6d-11cf-96b8-444553540000"))
_IShockwaveFlashEvents : IDispatch
{
    //
    // Wrapper methods for error-handling
    //

    // Methods:
    HRESULT OnReadyStateChange(long newState);
    HRESULT OnProgress(long percentDone);
    HRESULT FSCommand(_bstr_t command, _bstr_t args);
};

struct __declspec(uuid("d27cdb6e-ae6d-11cf-96b8-444553540000"))
ShockwaveFlash;
    // [ default ] interface IShockwaveFlash
    // [ default, source ] dispinterface _IShockwaveFlashEvents

struct __declspec(uuid("1171a62f-05d2-11d1-83fc-00a0c9089c5a"))
FlashProp;
    // [ default ] interface IUnknown

struct __declspec(uuid("d27cdb70-ae6d-11cf-96b8-444553540000"))
IFlashFactory : IUnknown
{};

struct __declspec(uuid("a6ef9860-c720-11d0-9337-00a0c90dcaa9"))
IDispatchEx : IDispatch
{
    //
    // Wrapper methods for error-handling
    //

    HRESULT GetDispID (
        _bstr_t bstrName,
        unsigned long grfdex,
        long * pid );
    HRESULT RemoteInvokeEx (
        long id,
        unsigned long lcid,
        unsigned long dwFlags,
        struct DISPPARAMS * pdp,
        VARIANT * pvarRes,
        struct EXCEPINFO * pei,
        struct IServiceProvider * pspCaller,
        unsigned int cvarRefArg,
        unsigned int * rgiRefArg,
        VARIANT * rgvarRefArg );
    HRESULT DeleteMemberByName (
        _bstr_t bstrName,
        unsigned long grfdex );
    HRESULT DeleteMemberByDispID (
        long id );
    HRESULT GetMemberProperties (
        long id,
        unsigned long grfdexFetch,
        unsigned long * pgrfdex );
    HRESULT GetMemberName (
        long id,
        BSTR * pbstrName );
    HRESULT GetNextDispID (
        unsigned long grfdex,
        long id,
        long * pid );
    HRESULT GetNameSpaceParent (
        IUnknown * * ppunk );

    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall raw_GetDispID (
        /*[in]*/ BSTR bstrName,
        /*[in]*/ unsigned long grfdex,
        /*[out]*/ long * pid ) = 0;
      virtual HRESULT __stdcall raw_RemoteInvokeEx (
        /*[in]*/ long id,
        /*[in]*/ unsigned long lcid,
        /*[in]*/ unsigned long dwFlags,
        /*[in]*/ struct DISPPARAMS * pdp,
        /*[out]*/ VARIANT * pvarRes,
        /*[out]*/ struct EXCEPINFO * pei,
        /*[in]*/ struct IServiceProvider * pspCaller,
        /*[in]*/ unsigned int cvarRefArg,
        /*[in]*/ unsigned int * rgiRefArg,
        /*[in,out]*/ VARIANT * rgvarRefArg ) = 0;
      virtual HRESULT __stdcall raw_DeleteMemberByName (
        /*[in]*/ BSTR bstrName,
        /*[in]*/ unsigned long grfdex ) = 0;
      virtual HRESULT __stdcall raw_DeleteMemberByDispID (
        /*[in]*/ long id ) = 0;
      virtual HRESULT __stdcall raw_GetMemberProperties (
        /*[in]*/ long id,
        /*[in]*/ unsigned long grfdexFetch,
        /*[out]*/ unsigned long * pgrfdex ) = 0;
      virtual HRESULT __stdcall raw_GetMemberName (
        /*[in]*/ long id,
        /*[out]*/ BSTR * pbstrName ) = 0;
      virtual HRESULT __stdcall raw_GetNextDispID (
        /*[in]*/ unsigned long grfdex,
        /*[in]*/ long id,
        /*[out]*/ long * pid ) = 0;
      virtual HRESULT __stdcall raw_GetNameSpaceParent (
        /*[out]*/ IUnknown * * ppunk ) = 0;
};

struct __declspec(uuid("d27cdb72-ae6d-11cf-96b8-444553540000"))
IFlashObjectInterface : IDispatchEx
{};

struct __declspec(uuid("d27cdb71-ae6d-11cf-96b8-444553540000"))
FlashObjectInterface;
    // [ default ] interface IFlashObjectInterface

} // namespace ShockwaveFlashObjects

#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////
// _flash_player - Handles Flash ActiveX   

class _control_site;
class _flash_sink;

class _flash_player
{
public:
	enum
	{
		STATE_IDLE,
		STATE_PLAYING,
		STATE_STOPPED
	};

	enum
	{
		QUALITY_LOW,
		QUALITY_MEDIUM,
		QUALITY_HIGH
	};

public:
	int						mState;
	ipf::player_ID			m_ID;
//	FlashListener*			mFlashListener;
	HMODULE					mFlashLibHandle;		

	_control_site*			m_control_site;
	_flash_sink*			m_flash_sink;
	ShockwaveFlashObjects::IShockwaveFlash* m_flash_interface_p;
	IOleObject*				mOleObject;
	IOleInPlaceObjectWindowless* m_windowless_object_p;

	int						mCOMCount;
//	DDImage*				mImage;	
	int						mPauseCount;
	bool					mHasLostFocus;

//	Rect					mDirtyRect;
	bool					mFlashDirty;
	
	int						mCurCursor;
	HCURSOR					mCurOverrideCursor;
	
	bool					mAutoPause;
//	Image*					mBkgImage;
//	Rect					mBkgImageSrcRect;
//	Color					mBkgColor;				

public:
	void					CleanupImages();
	void					RebuildImages();
	void					CheckCursor();

protected:
//	virtual void			DrawFlashBackground(Graphics* g);

private:
	int m_mouse_x, m_mouse_y;
	bool m_pressed;

public:
	_flash_player(ipf::player_ID _ID);
	~_flash_player();
	
	static double			GetFlashVersion();

	bool load(const char* _filename);
	bool play();
	bool pause();
	bool stop();
	bool draw(HDC _hdc);
	bool mouse(int _x, int _y, bool _pressed);
	bool key(unsigned int _key, unsigned int _flags);
	bool message(UINT _msg, WPARAM _wparam, LPARAM _lparam);

//	bool					StartAnimation(const std::string& theFileName);	
	void					SetQuality(int theQuality);
	void					Pause();
	void					Unpause();
	bool					IsPlaying();	
	void					Rewind();
	void					Back();
	void					Forward();	
	void					GotoFrame(int theFrameNum);
	int						GetCurrentFrame();
//	std::string				GetCurrentLabel(const std::string& theTimeline);
//	void					CallFrame(const std::string& theTimeline, int theFrameNum);
//	void					CallLabel(const std::string& theTimeline, const std::string& theLabel);
//	std::string				GetVariable(const std::string& theName);
//	void					SetVariable(const std::string& theName, const std::string& theValue);
		
	virtual void			Resize(int theX, int theY, int theWidth, int theHeight);
	
	virtual void			Update();
//	virtual void			Draw(Graphics* g);

	virtual void			MouseDown(int x, int y, int theBtnNum, int theClickCount);		
	virtual void			MouseUp(int x, int y, int theBtnNum, int theClickCount);
	virtual void			MouseMove(int x, int y);
	virtual void			MouseDrag(int x, int y);
	
	virtual void			MouseLeave();

	virtual void			SysColorChanged();
};

//////////////////////////////////////////////////////////////////////////
// _flash_sink - Receives flash events   

class _flash_sink : public ShockwaveFlashObjects::_IShockwaveFlashEvents
{
public:	
	LPCONNECTIONPOINT		mConnectionPoint;	
	DWORD					mCookie;
	int						m_refcount;
	_flash_player*			m_player_p;

public:
	_flash_sink()
	{		
		mCookie = 0;
		mConnectionPoint = NULL;
		m_refcount = 0;
		m_player_p = NULL;		
	}

	virtual ~_flash_sink()
	{
		m_player_p->mCOMCount--;
	}

	HRESULT Init(_flash_player *_player_p)
	{
		m_player_p = _player_p;
		m_player_p->mCOMCount++;

		HRESULT aResult = NOERROR;
		LPCONNECTIONPOINTCONTAINER aConnectionPoint = NULL;
						
		if ((m_player_p->m_flash_interface_p->QueryInterface(IID_IConnectionPointContainer, (void**) &aConnectionPoint) == S_OK) &&
			(aConnectionPoint->FindConnectionPoint(__uuidof(ShockwaveFlashObjects::_IShockwaveFlashEvents), &mConnectionPoint) == S_OK))			
		{
			IDispatch* aDispatch = NULL;
			QueryInterface(__uuidof(IDispatch), (void**) &aDispatch);
			if (aDispatch != NULL)
			{
				aResult = mConnectionPoint->Advise((LPUNKNOWN)aDispatch, &mCookie);
				aDispatch->Release();
			}
		}
				
		if (aConnectionPoint != NULL) 
			aConnectionPoint->Release();

		return aResult;
	}

	HRESULT Shutdown()
	{
		HRESULT aResult = S_OK;

		if (mConnectionPoint)
		{
			if (mCookie)
			{
				aResult = mConnectionPoint->Unadvise(mCookie);
				mCookie = 0;
			}

			mConnectionPoint->Release();
			mConnectionPoint = NULL;
		}

		return aResult;
	}
 
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv)
	{
		*ppv = NULL;

		if (riid == IID_IUnknown)
		{
			*ppv = (LPUNKNOWN)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IDispatch)
		{
			*ppv = (IDispatch*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == __uuidof(ShockwaveFlashObjects::_IShockwaveFlashEvents))
		{
			*ppv = (ShockwaveFlashObjects::_IShockwaveFlashEvents*) this;
			AddRef();
			return S_OK;
		}
		else
		{   
			return E_NOTIMPL;
		}
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{  
		return ++m_refcount;
	}

	ULONG STDMETHODCALLTYPE Release()
	{  
		int aRefCount = --m_refcount;
		if (aRefCount == 0)		
			delete this;		

		return aRefCount;
	}

 // IDispatch method
  virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT* pctinfo)
   { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo)
	{
		return E_NOTIMPL; 
	}

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames,
		UINT cNames, LCID lcid,DISPID* rgDispId)
	{
		return E_NOTIMPL; 
	}

	virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,
		WORD wFlags, ::DISPPARAMS __RPC_FAR *pDispParams, VARIANT __RPC_FAR *pVarResult,
		::EXCEPINFO __RPC_FAR *pExcepInfo, UINT __RPC_FAR *puArgErr)
	{
		switch(dispIdMember)
		{
		case 0x7a6:			
			break;
		case 0x96:			
			if ((pDispParams->cArgs == 2) &&
				(pDispParams->rgvarg[0].vt == VT_BSTR) &&
				(pDispParams->rgvarg[1].vt == VT_BSTR))
			{
				FSCommand(pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal);
			}
			break;
		case DISPID_READYSTATECHANGE:					
			break;
		default:			
			return DISP_E_MEMBERNOTFOUND;
		} 
		
		return NOERROR;
	}

	HRESULT OnReadyStateChange (long newState)
	{	
		return S_OK;
	}
    
	HRESULT OnProgress(long percentDone )
	{		
		return S_OK;
	}

	HRESULT FSCommand (_bstr_t command, _bstr_t args)
	{
		//if (m_player_p->mFlashListener != NULL)
		//	m_player_p->mFlashListener->FlashCommand(m_player_p->mId, (char*) command, (char*) args);
		return S_OK;
	}	
};

using namespace ShockwaveFlashObjects;

//////////////////////////////////////////////////////////////////////////
// _control_site - container that holds the flash control

class _control_site : 	
	public IOleInPlaceSiteWindowless, 
	public IOleClientSite	
{
public:
	int						m_refcount;
	_flash_player*			m_player_p;

public:
	_control_site()
	{		
		m_refcount = 0;		
		m_player_p = NULL;
	}	

	virtual ~_control_site()
	{
		if (m_player_p != NULL)
			m_player_p->mCOMCount--;
	}

	void Init(_flash_player *_player_p)
	{
		m_player_p = _player_p;
		m_player_p->mCOMCount++;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv)
	{
		*ppv = NULL;

		if (riid == IID_IUnknown)
		{
			*ppv = (IUnknown*) (IOleWindow*) this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleWindow)
		{
			*ppv = (IOleWindow*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleInPlaceSite)
		{
			*ppv = (IOleInPlaceSite*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleInPlaceSiteEx)
		{
			*ppv = (IOleInPlaceSiteEx*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleInPlaceSiteWindowless)
		{
			*ppv = (IOleInPlaceSiteWindowless*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleClientSite)
		{
			*ppv = (IOleClientSite*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == __uuidof(ShockwaveFlashObjects::_IShockwaveFlashEvents))
		{
			*ppv = (ShockwaveFlashObjects::_IShockwaveFlashEvents*) this;
			AddRef();
			return S_OK;
		}
		else
		{   
			return E_NOTIMPL;
		}
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{  
		return ++m_refcount;
	}

	ULONG STDMETHODCALLTYPE Release()
	{ 
		int l_refcount = --m_refcount;
		if (l_refcount == 0)		
			delete this;		

		return l_refcount;
	}

	//////////////////////////////////////////////////////////////////////////	

	virtual HRESULT  STDMETHODCALLTYPE SaveObject(void)
	{
		return S_OK;
	}

	virtual HRESULT  STDMETHODCALLTYPE GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker,IMoniker** ppmk )
	{
		*ppmk = NULL;
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetContainer(IOleContainer ** theContainerP)
	{
		//return QueryInterface(__uuidof(IOleContainer), (void**) theContainerP);				
		return E_NOINTERFACE;
	}


	virtual HRESULT  STDMETHODCALLTYPE ShowObject(void)
	{
		return E_NOTIMPL;
	}

	virtual HRESULT  STDMETHODCALLTYPE OnShowWindow(BOOL)
	{
		return E_NOTIMPL;
	}

	virtual HRESULT  STDMETHODCALLTYPE RequestNewObjectLayout(void)
	{
		return E_NOTIMPL;
	}
		//		
	

	HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(/* [in] */ BOOL fEnterMode)
	{
	    return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetWindow(/* [out] */ HWND __RPC_FAR* theWnndow)
	{
		return E_FAIL;

	    //*theWnndow = NULL;
		//*theWnndow = gSexyAppBase->mHWnd;
		//return S_OK;
	}

	HRESULT STDMETHODCALLTYPE CanInPlaceActivate(void)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnInPlaceActivate(void)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnUIActivate(void)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE GetWindowContext(/* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame, /* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc, /* [out] */ LPRECT lprcPosRect, /* [out] */ LPRECT lprcClipRect, /* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo)
	{
		//RECT aRect = m_player_p->GetRect().ToRECT();
		RECT aRect = {0,0,100,100};//m_player_p->get_rect();

		*lprcPosRect = aRect;
		*lprcClipRect = aRect;
		
		*ppFrame = NULL;
		QueryInterface(__uuidof(IOleInPlaceFrame), (void**) ppFrame);		
		*ppDoc = NULL;

		lpFrameInfo->fMDIApp = FALSE;
		lpFrameInfo->hwndFrame = NULL;
		lpFrameInfo->haccel = NULL;
		lpFrameInfo->cAccelEntries = 0;
		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE Scroll(/* [in] */ SIZE scrollExtant)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnUIDeactivate(/* [in] */ BOOL fUndoable)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate(void)
	{	
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE DiscardUndoState(void)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE DeactivateAndUndo(void)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnPosRectChange(/* [in] */ LPCRECT lprcPosRect)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnInPlaceActivateEx(/* [out] */ BOOL __RPC_FAR *pfNoRedraw, /* [in] */ DWORD dwFlags)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnInPlaceDeactivateEx(/* [in] */ BOOL fNoRedraw)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE RequestUIActivate(void)
	{
		return S_FALSE;
	}


	HRESULT STDMETHODCALLTYPE CanWindowlessActivate(void)
	{
		// Allow windowless activation?
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE GetCapture(void)
	{
		// TODO capture the mouse for the object
		return S_FALSE;
	}


	HRESULT STDMETHODCALLTYPE SetCapture(/* [in] */ BOOL fCapture)
	{
		// TODO capture the mouse for the object
		return S_FALSE;
	}


	HRESULT STDMETHODCALLTYPE GetFocus(void)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE SetFocus(/* [in] */ BOOL fFocus)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetDC(/* [in] */ LPCRECT pRect, /* [in] */ DWORD grfFlags, /* [out] */ HDC __RPC_FAR *phDC)
	{		
		return E_INVALIDARG;		
	}


	HRESULT STDMETHODCALLTYPE ReleaseDC(/* [in] */ HDC hDC)
	{
		return E_INVALIDARG;
	}


	HRESULT STDMETHODCALLTYPE InvalidateRect(/* [in] */ LPCRECT pRect, /* [in] */ BOOL fErase)
	{	
		//if (pRect == NULL)
		//{
		//	m_player_p->mDirtyRect = m_player_p->GetRect();
		//	m_player_p->mFlashDirty = true;
		//}
		//else if (!m_player_p->mFlashDirty)
		//{
		//	m_player_p->mDirtyRect = Rect(pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top);
		//	m_player_p->mFlashDirty = true;
		//}
		//else
		//{			
		//	m_player_p->mDirtyRect = m_player_p->mDirtyRect.Union(Rect(pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top));
		//}		
		
		//return S_OK;
		return S_FALSE;
	}

	HRESULT STDMETHODCALLTYPE InvalidateRgn(/* [in] */ HRGN _rgn, /* [in] */ BOOL _erase)
	{	
		RECT l_rect; GetRgnBox(_rgn, &l_rect);
		return InvalidateRect(&l_rect, _erase);
		//m_player_p->mDirtyRect = m_player_p->GetRect();
		//m_player_p->mFlashDirty = true;
		//return S_OK;
	}

	HRESULT STDMETHODCALLTYPE ScrollRect(/* [in] */ INT dx, /* [in] */ INT dy, /* [in] */ LPCRECT pRectScroll, /* [in] */ LPCRECT pRectClip)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE AdjustRect(/* [out][in] */ LPRECT prc)
	{
		if (prc == NULL)
		{
			return E_INVALIDARG;
		}
		
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnDefWindowMessage(/* [in] */ UINT msg, /* [in] */ WPARAM wParam, /* [in] */ LPARAM lParam, /* [out] */ LRESULT __RPC_FAR *plResult)
	{
		return S_FALSE;
	}
};

//////////////////////////////////////////////////////////////////////////

const CLSID CLSID_ShockwaveFlash =
  { 0xD27CDB6E, 0xAE6D, 0x11cf, {0x96, 0xB8, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} };

typedef HRESULT (__stdcall *DllGetClassObjectFunc)(REFCLSID rclsid, REFIID riid, LPVOID * ppv); 

_flash_player::_flash_player(ipf::player_ID _ID)
{
	HRESULT aResult;

	mState = STATE_IDLE;

//	mCurCursor = CURSOR_POINTER;
	mCurOverrideCursor = NULL;

	mCOMCount = 0;
	mPauseCount = 0;
	mAutoPause = true;
//	mHasLostFocus = !gSexyAppBase->mHasFocus;
	mFlashDirty = true;	

//	mBkgColor.mAlpha = 0;
	m_ID = _ID;
//	mFlashListener = theFlashListener;	

	m_flash_sink = NULL;
	
//	mImage = NULL;	
	m_flash_interface_p = NULL;
	mOleObject = NULL;
	m_windowless_object_p = NULL;

//	mBkgImage = NULL;
	mFlashLibHandle = NULL;

	CoInitialize(NULL);

	m_control_site = new _control_site();
	m_control_site->AddRef();	
	m_control_site->Init(this);
		
	//mFlashLibHandle = LoadLibraryA("Flash10a.ocx");
	mFlashLibHandle = LoadLibraryA("flash.ocx");
	if (mFlashLibHandle != NULL)
	{
		IClassFactory* aClassFactory = NULL;
		DllGetClassObjectFunc aDllGetClassObjectFunc = (DllGetClassObjectFunc) GetProcAddress(mFlashLibHandle, "DllGetClassObject");
		aResult = aDllGetClassObjectFunc(CLSID_ShockwaveFlash, IID_IClassFactory, (void**)&aClassFactory);
		aClassFactory->CreateInstance(NULL, IID_IOleObject, (void**)&mOleObject);
		aClassFactory->Release();	
	}
	else
	{
		CoCreateInstance(CLSID_ShockwaveFlash, NULL, 
			CLSCTX_INPROC_SERVER,
			IID_IOleObject,
			(void**)&mOleObject);
	}

	IOleClientSite* aClientSite = NULL;
	m_control_site->QueryInterface(__uuidof(IOleClientSite), (void**) &aClientSite);
	mOleObject->SetClientSite(aClientSite);	

	mOleObject->QueryInterface(__uuidof(IShockwaveFlash), (LPVOID*) &m_flash_interface_p);
	_bstr_t aTrans = "Transparent";
	m_flash_interface_p->put_WMode(aTrans);

	aResult = mOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, aClientSite, 0, NULL, NULL);
	aClientSite->Release();	
		
	mOleObject->QueryInterface(__uuidof(IOleInPlaceObjectWindowless), (LPVOID*) &m_windowless_object_p);
			
	m_flash_sink = new _flash_sink();
	m_flash_sink->AddRef();	
	m_flash_sink->Init(this);

	m_mouse_x = m_mouse_y = 0;
	m_pressed = false;
}

_flash_player::~_flash_player()
{
	CleanupImages();
		
	if (m_windowless_object_p != NULL)
		m_windowless_object_p->Release();
	if (m_flash_interface_p != NULL)
		m_flash_interface_p->Release();	

	if (m_flash_sink != NULL)
	{
		m_flash_sink->Shutdown();
		m_flash_sink->Release();
	}

	mOleObject->Close(OLECLOSE_NOSAVE);
		
	if (mOleObject != NULL)
		mOleObject->Release();	

	if (m_control_site != NULL)
		m_control_site->Release();

	// Make sure all our COM objects were actually destroyed
//	DBG_ASSERTE(mCOMCount == 0);

	if (mFlashLibHandle != NULL)
		FreeLibrary(mFlashLibHandle);	
}

double _flash_player::GetFlashVersion()
{
	CoInitialize(NULL);

	IOleObject* anOleObject = NULL;
	if (FAILED(CoCreateInstance(CLSID_ShockwaveFlash, NULL, 
		CLSCTX_INPROC_SERVER,
		IID_IOleObject,
		(void**) &anOleObject)))
		return 0.0;	

	IShockwaveFlash* aFlashInterface = NULL;
	if (FAILED(anOleObject->QueryInterface(__uuidof(IShockwaveFlash), (LPVOID*) &aFlashInterface)))
		return 0.0;
	
	long aVersion = 0;
	aFlashInterface->FlashVersion(&aVersion);

	aFlashInterface->Release();
	anOleObject->Release();

	return aVersion / 65536.0;
}

void _flash_player::CleanupImages()
{
	//if (mImage != NULL)
	//{
	//	delete mImage;
	//	mImage = NULL;
	//}
}

void _flash_player::RebuildImages()
{
	CleanupImages();

	//mImage = new DDImage(gSexyAppBase->mDDInterface);
	//mImage->Create(mWidth, mHeight);
	//mImage->SetImageMode(false, false);	
}

void _flash_player::CheckCursor()
{
	//HCURSOR aCursor = GetCursor();
	//if (aCursor == ::LoadCursor(NULL, IDC_ARROW))
	//{
	//	mCurCursor = CURSOR_POINTER;
	//	gSexyAppBase->mOverrideCursor = NULL;
	//	gSexyAppBase->SetCursor(mCurCursor);
	//}
	//else if (aCursor != NULL)
	//{
	//	gSexyAppBase->mOverrideCursor = aCursor;
	//	mCurCursor = CURSOR_HAND;
	//	gSexyAppBase->SetCursor(mCurCursor);
	//}
}

//void _flash_player::DrawFlashBackground(Graphics* g)
//{
//	if (mBkgColor.mAlpha != 0)
//	{
//		g->SetColor(mBkgColor);
//		g->FillRect(0, 0, mWidth, mHeight);
//	}
//
//	if (mBkgImage != NULL)
//	{
//		if ((mBkgImageSrcRect.mWidth != 0) && (mBkgImageSrcRect.mHeight != 0))
//			g->DrawImage(mBkgImage, 0, 0, mBkgImageSrcRect);
//		else
//			g->DrawImage(mBkgImage, 0, 0);
//	}
//}

//bool _flash_player::StartAnimation(const std::string& theFileName)
//{
//	std::string aFullPath = GetFullPath(theFileName);
//	
//	_bstr_t bstr((char*) aFullPath.c_str());		
//	m_flash_interface_p->put_Movie(bstr); // you have to change the path here	
//	if ((mPauseCount == 0) && (m_flash_interface_p->Play() != S_OK))
//		return false;	
//
//	if ((mWidgetManager != NULL) && (mIsOver))
//		MouseMove(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY);
//
//	mState = STATE_PLAYING;	
//	return true;
//}

bool _flash_player::load(const char* _filename)
{
	if (m_flash_interface_p->LoadMovie(0, _bstr_t(_filename)) != S_OK) return false;
	//if (m_flash_interface_p->Play() != S_OK) return false;
	//m_flash_interface_p->StopPlay();

	Resize(0, 0, 800, 600);

	mState = STATE_IDLE;	
	return true;
}
bool _flash_player::play()
{
	if (m_flash_interface_p->Play() != S_OK) return false;

	mState = STATE_PLAYING;
	return true;
}

bool _flash_player::pause()
{
	if (m_flash_interface_p->StopPlay() != S_OK) return false;

	mState = STATE_IDLE;
	return true;
}

bool _flash_player::stop()
{
	if (m_flash_interface_p->Stop() != S_OK) return false;

	mState = STATE_STOPPED;
	return true;
}

bool _flash_player::draw(HDC _hdc)
{
	//for (int i = 0; i < 5; ++i)
	//{
	//	BSTR l_val[MAX_PATH];
	//	HRESULT l_res = m_flash_interface_p->Put_F(L"root.name", l_val);
	//	int a=0;
	//}

	HRESULT l_res;
	{
		RECT l_rect = {0,0,800, 600};
		this->m_windowless_object_p->SetObjectRects(&l_rect, &l_rect);
		//FillRect(_hdc, &l_rect, (HBRUSH)GetStockObject(GRAY_BRUSH));
		l_res = OleDraw(m_flash_interface_p, DVASPECT_CONTENT, _hdc, &l_rect);
	}
	//IViewObject* aViewObject = NULL;
	//l_res = m_flash_interface_p->QueryInterface(IID_IViewObject, (LPVOID*) &aViewObject);
	//if (l_res == S_OK && aViewObject != NULL)
	//{
	//	RECTL aRect = {0, 0, 100/*mWidth*/, 100/*mHeight*/};

	//	//Point anAbsPos = GetAbsPos();

	//	//HRGN aRgn = CreateRectRgn(mDirtyRect.mX - anAbsPos.mX, mDirtyRect.mY - anAbsPos.mY, 
	//	//	mDirtyRect.mX + mDirtyRect.mWidth - anAbsPos.mX, 
	//	//	mDirtyRect.mY + mDirtyRect.mHeight - anAbsPos.mY);
	//	//SelectClipRgn(aDC, aRgn);
	//	//DeleteObject(aRgn);

	//	l_res = aViewObject->Draw(DVASPECT_CONTENT, 1, NULL, NULL, NULL, _hdc, &aRect, NULL, NULL, 0);

	//	aViewObject->Release();
	//}

	return l_res == S_OK;
}

bool _flash_player::mouse(int _x, int _y, bool _pressed)
{
	HRESULT l_hres = S_OK;
	LRESULT l_lres;
	bool m_button = (m_pressed != _pressed);
	bool m_motion = (m_mouse_x != _x || m_mouse_y != _y);
	m_pressed = _pressed;
	m_mouse_x = _x; m_mouse_y = _y;
	if (m_button)
	{
		if (m_pressed)
			l_hres = m_windowless_object_p->OnWindowMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(m_mouse_x, m_mouse_y), &l_lres);
		else
			l_hres = m_windowless_object_p->OnWindowMessage(WM_LBUTTONUP, 0, MAKELPARAM(m_mouse_x, m_mouse_y), &l_lres);
	}
	if (m_motion)
	{
		if (m_pressed)
			l_hres = m_windowless_object_p->OnWindowMessage(WM_MOUSEMOVE, MK_LBUTTON, MAKELPARAM(m_mouse_x, m_mouse_y), &l_lres);
		else
			l_hres = m_windowless_object_p->OnWindowMessage(WM_MOUSEMOVE, 0, MAKELPARAM(m_mouse_x, m_mouse_y), &l_lres);
	}
	return l_hres == S_OK;
}

bool _flash_player::key(unsigned int _key, unsigned int _flags)
{
	HRESULT l_hres;
	LRESULT l_lres;
	bool l_pressed = (_flags & (1<<31)) == 0;
	if (l_pressed)
	{
		l_hres = m_windowless_object_p->OnWindowMessage(WM_KEYDOWN, (WPARAM)_key, (LPARAM)_flags, &l_lres);
		TCHAR l_char = (TCHAR)MapVirtualKeyEx(_key, 2, ::GetKeyboardLayout(0));
		if (l_char)
		{
			l_hres = m_windowless_object_p->OnWindowMessage(WM_CHAR, (WPARAM)l_char, (LPARAM)_flags, &l_lres);
		}
	}
	else
	{
		l_hres = m_windowless_object_p->OnWindowMessage(WM_KEYUP, (WPARAM)_key, (LPARAM)_flags, &l_lres);
		//TCHAR l_char = (TCHAR)MapVirtualKeyEx(_key, 2, ::GetKeyboardLayout(0));
		//l_hres = m_windowless_object_p->OnWindowMessage(WM_DEADCHAR, (WPARAM)l_char, (LPARAM)_flags, &l_lres);
	}
	return l_hres == S_OK;
}

bool _flash_player::message(UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	HRESULT l_hres;
	LRESULT l_lres;
	l_hres = m_windowless_object_p->OnWindowMessage(_msg, _wparam, _lparam, &l_lres);
	return l_hres == S_OK;
}

void _flash_player::SetQuality(int theQuality)
{
	static char* aQualityNames[3] = {"Low", "Medium", "High"};
	
	_bstr_t aNewStr = aQualityNames[theQuality];
	m_flash_interface_p->put_Quality2(aNewStr);
}

void _flash_player::Pause()
{
	mPauseCount++;

	if (mState != STATE_STOPPED)
		mState = STATE_IDLE;

	if ((mPauseCount == 1) && (m_flash_interface_p != NULL) && (mState != STATE_STOPPED))
		m_flash_interface_p->StopPlay();
}

void _flash_player::Unpause()
{
	mPauseCount--;
	if ((mPauseCount == 0) && (m_flash_interface_p != NULL) && (mState != STATE_STOPPED))
	{
		mState = STATE_PLAYING;
		m_flash_interface_p->Play();
	}
}

void _flash_player::Rewind()
{
	if (m_flash_interface_p != NULL)
	{
		m_flash_interface_p->Rewind();
		m_flash_interface_p->Play();
	}
}

void _flash_player::GotoFrame(int theFrameNum)
{
	if (m_flash_interface_p != NULL)
	{
		m_flash_interface_p->GotoFrame(theFrameNum);
		m_flash_interface_p->Play();
	}
}

void _flash_player::Back()
{
	if (m_flash_interface_p != NULL)
	{
		m_flash_interface_p->Back();
		m_flash_interface_p->Play();
	}
}

void _flash_player::Forward()
{
	if (m_flash_interface_p != NULL)
	{
		m_flash_interface_p->Forward();
		m_flash_interface_p->Play();
	}
}

bool _flash_player::IsPlaying()
{
	VARIANT_BOOL aBool = 0;
	if (m_flash_interface_p != NULL)
		m_flash_interface_p->IsPlaying(&aBool);
	return aBool != 0;
}

int _flash_player::GetCurrentFrame()
{	
	long aCurrentFrame = -1;
	if (m_flash_interface_p != NULL)
		m_flash_interface_p->CurrentFrame(&aCurrentFrame);
	return aCurrentFrame;
}

//std::string _flash_player::GetCurrentLabel(const std::string& theTimeline)
//{
//	BSTR aBStr = L"";
//	if (m_flash_interface_p != NULL)
//		m_flash_interface_p->TCurrentLabel(_bstr_t(theTimeline.c_str()), &aBStr);
//	return (const char*) _bstr_t(aBStr);
//}

//void _flash_player::CallFrame(const std::string& theTimeline, int theFrameNum)
//{
//	if (m_flash_interface_p != NULL)
//		m_flash_interface_p->TCallFrame(_bstr_t(theTimeline.c_str()), theFrameNum);
//}

//void _flash_player::CallLabel(const std::string& theTimeline, const std::string& theLabel)
//{
//	if (m_flash_interface_p != NULL)
//		m_flash_interface_p->TCallLabel(_bstr_t(theTimeline.c_str()), _bstr_t(theLabel.c_str()));
//}

//std::string _flash_player::GetVariable(const std::string& theName)
//{
//	BSTR aBStr = L"";
//	if (m_flash_interface_p != NULL)
//		m_flash_interface_p->GetVariable(_bstr_t(theName.c_str()), &aBStr);
//	return (const char*) _bstr_t(aBStr);
//}

//void _flash_player::SetVariable(const std::string& theName, const std::string& theValue)
//{
//	if (m_flash_interface_p != NULL)
//		m_flash_interface_p->SetVariable(_bstr_t(theName.c_str()), _bstr_t(theValue.c_str()));
//}

void _flash_player::Update()
{
	//if (mAutoPause)
	//{
	//	if (!gSexyAppBase->mHasFocus)
	//	{
	//		if (!mHasLostFocus)
	//		{
	//			if (mAutoPause)
	//				Pause();
	//			mHasLostFocus = true;
	//		}

	//		return;
	//	}
	//	else
	//	{
	//		if (mHasLostFocus)
	//		{
	//			if (mAutoPause)
	//				Unpause();
	//			mHasLostFocus = false;
	//		}
	//	}
	//}

	if (mState == STATE_PLAYING)
	{
		VARIANT_BOOL isPlaying = 0;
		m_flash_interface_p->IsPlaying(&isPlaying);	
		if (!isPlaying)
		{
			mState = STATE_STOPPED;
			//if ((mFlashListener != NULL) && (mPauseCount == 0))
			//	mFlashListener->FlashAnimEnded(mId);
		}
	}

	//if (mFlashDirty)
	//	MarkDirty();
}

void _flash_player::Resize(int theX, int theY, int theWidth, int theHeight)
{
	if (m_windowless_object_p)
	{
		RECT l_rect = {100,100};
		m_windowless_object_p->SetObjectRects(&l_rect, &l_rect);
	}
	//Widget::Resize(theX, theY, theWidth, theHeight);

	//mDirtyRect = Rect(theX, theY, theWidth, theHeight);	

	//RebuildImages();

	//IOleInPlaceObject* anInPlaceObject = NULL;	
	//mOleObject->QueryInterface(__uuidof(IOleInPlaceObject), (LPVOID*) &anInPlaceObject);			

	//if (anInPlaceObject != NULL)
	//{
	//	RECT aRect = {100,100};//GetRect().ToRECT();
	//	anInPlaceObject->SetObjectRects(&aRect, &aRect);
	//	anInPlaceObject->Release();
	//}
}

//void _flash_player::Draw(Graphics* g)
//{	
//	if (mFlashDirty)
//	{
//		Graphics anImageG(mImage);	
//		DrawFlashBackground(&anImageG);	
//
//		LPDIRECTDRAWSURFACE aSurface = mImage->GetSurface();
//		if (aSurface == NULL)
//			return;
//
//		HDC aDC = NULL;
//		if (aSurface->GetDC(&aDC) != S_OK)
//			return;	
//
//		IViewObject* aViewObject = NULL;
//		m_flash_interface_p->QueryInterface(IID_IViewObject, (LPVOID*) &aViewObject);
//		if (aViewObject != NULL)
//		{
//			RECTL aRect = {0, 0, mWidth, mHeight};
//
//			Point anAbsPos = GetAbsPos();
//
//			HRGN aRgn = CreateRectRgn(mDirtyRect.mX - anAbsPos.mX, mDirtyRect.mY - anAbsPos.mY, 
//				mDirtyRect.mX + mDirtyRect.mWidth - anAbsPos.mX, 
//				mDirtyRect.mY + mDirtyRect.mHeight - anAbsPos.mY);
//			SelectClipRgn(aDC, aRgn);
//			DeleteObject(aRgn);
//
//			aViewObject->Draw(DVASPECT_CONTENT, 1,
//				NULL, NULL, NULL, aDC, &aRect, NULL, NULL,
//				0);
//
//			aViewObject->Release();
//		}
//
//		aSurface->ReleaseDC(aDC);
//
//		mFlashDirty = false;
//	}
//	
//	g->DrawImage(mImage, 0, 0);
//}

void _flash_player::MouseMove(int x, int y)
{	
//	Widget::MouseMove(x, y);

	//LRESULT aResult;
	//Point anAbsPos = GetAbsPos();
	//m_windowless_object_p->OnWindowMessage(WM_MOUSEMOVE, 0, MAKELPARAM(x + anAbsPos.mX, y + anAbsPos.mY), &aResult);

	//if (mIsOver)
	//	CheckCursor();
}

void _flash_player::MouseDown(int x, int y, int theBtnNum, int theClickCount)
{
	//if (theBtnNum == 0)
	//{
	//	LRESULT aResult;
	//	Point anAbsPos = GetAbsPos();
	//	m_windowless_object_p->OnWindowMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x + anAbsPos.mX, y + anAbsPos.mY), &aResult);
	//	CheckCursor();
	//}
}

void _flash_player::MouseUp(int x, int y, int theBtnNum, int theClickCount)
{
	//if (theBtnNum == 0)
	//{
	//	LRESULT aResult;
	//	Point anAbsPos = GetAbsPos();
	//	m_windowless_object_p->OnWindowMessage(WM_LBUTTONUP, 0, MAKELPARAM(x + anAbsPos.mX, y + anAbsPos.mY), &aResult);
	//	CheckCursor();
	//}
}

void _flash_player::MouseDrag(int x, int y)
{
	//if (mWidgetManager->IsLeftButtonDown())
	//{
	//	LRESULT aResult;
	//	Point anAbsPos = GetAbsPos();
	//	m_windowless_object_p->OnWindowMessage(WM_MOUSEMOVE, MK_LBUTTON, MAKELPARAM(x + anAbsPos.mX, y + anAbsPos.mY), &aResult);
	//	CheckCursor();
	//}
}

void _flash_player::MouseLeave()
{
	//Widget::MouseLeave();

	//// To prevent Flash control from setting our cursor if it thinks 
	//// our mouse is still over something
	//MouseMove(-1, -1);

	//gSexyAppBase->mOverrideCursor = NULL;
	//gSexyAppBase->SetCursor(CURSOR_POINTER);	
}

void _flash_player::SysColorChanged()
{
	//mFlashDirty = true;
	//mDirtyRect = GetRect();

	//MarkDirty();
}

namespace ipf { // --------------------------------------------------------------------------------

static const unsigned int max_player_count = 100;
static _flash_player* sg_players[max_player_count] = {0};
static unsigned int sg_player_count = 0;
static player_ID sg_free_IDs[max_player_count];
static unsigned int sg_free_ID_count = 0;

//
player_ID create_player()
{
	player_ID l_ID;
	if (sg_free_ID_count)
	{
		l_ID = sg_free_IDs[--sg_free_ID_count];
	}
	else
	{
		if (sg_player_count < max_player_count)
		{
			l_ID = sg_player_count++;
		}
		else
		{
			return player_ID(-1);
		}
	}

	sg_players[l_ID] = new _flash_player(l_ID);

	return l_ID;
}

//
void destroy_player(player_ID _ID)
{
	if (sg_players[_ID] != 0)
	{
		delete sg_players[_ID];
		sg_free_IDs[sg_free_ID_count++] = _ID;
		sg_players[_ID] = 0;
	}
}

//
bool player_load(player_ID _ID, char* _movie)
{
	_flash_player &l_player = * sg_players[_ID];
	char l_path[MAX_PATH] = {0};
	DWORD l_length = GetCurrentDirectoryA(MAX_PATH, l_path);
	l_path[l_length++] = '/';
	strcpy_s(l_path + l_length, MAX_PATH - l_length, _movie);
	return l_player.load(l_path);
}

//
bool player_play(player_ID _ID)
{
	_flash_player &l_player = * sg_players[_ID];
	return l_player.play();
}

//
bool player_pause(player_ID _ID)
{
	_flash_player &l_player = * sg_players[_ID];
	return l_player.pause();
}

//
bool player_stop(player_ID _ID)
{
	_flash_player &l_player = * sg_players[_ID];
	return l_player.stop();
}

//
bool player_draw(player_ID _ID, HDC _hdc)
{
	_flash_player &l_player = * sg_players[_ID];
	return l_player.draw(_hdc);
}

//
bool player_mouse(player_ID _ID, int _x, int _y, bool _pressed)
{
	_flash_player &l_player = * sg_players[_ID];
	return l_player.mouse(_x, _y, _pressed);
}

//
bool player_key(player_ID _ID, unsigned int _key, unsigned int _flags)
{
	_flash_player &l_player = * sg_players[_ID];
	return l_player.key(_key, _flags);
}

//
bool player_message(player_ID _ID, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	_flash_player &l_player = * sg_players[_ID];
	return l_player.message(_msg, _wparam, _lparam);
}

} // namespace ipf --------------------------------------------------------------------------------