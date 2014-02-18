

#include <windows.h>


#define ME_START 0x0E00
#define MAKE_ME(n) MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, ME_START + (n))


/*
    E_ABORT         0x80004004 The operation was aborted because of an unspecified error. 
    E_ACCESSDENIED  0x80070005 A general access-denied error. 
    E_FAIL          0x80004005 An unspecified failure has occurred. 
    E_HANDLE        0x80070006 An invalid handle was used. 
    E_INVALIDARG    0x80070057 One or more arguments are invalid. 
    E_NOINTERFACE   0x80004002 The QueryInterface method did not recognize the requested interface. The interface is not supported. 
    E_NOTIMPL       0x80004001 The method is not implemented. 
    E_OUTOFMEMORY   0x8007000E The method failed to allocate necessary memory. 
    E_PENDING       0x8000000A The data necessary to complete the operation is not yet available. 
    E_POINTER       0x80004003 An invalid pointer was used. 
    E_UNEXPECTED    0x8000FFFF A catastrophic failure has occurred. 
    S_FALSE         0x00000001 The method succeeded and returned the boolean value FALSE. 
    S_OK            0x00000000 The method succeeded. If a boolean return value is expected, the returned value is TRUE
*/
#define MIX_S_OK                 S_OK
#define MIX_E_FAIL               E_FAIL
#define MIX_E_NOTFOUND           MAKE_ME(1)
#define MIX_E_WRONGTYPE          MAKE_ME(2)// The specified call failed because this object's type isn't compatible with the operation.
#define MIX_E_MIXERERROR         MAKE_ME(3)// A call to a mixer API resulted in an unknown error.
#define MIX_E_NOTENABLED         MAKE_ME(4)// "driver failed enable"
#define MIX_E_ALLOCATED          MAKE_ME(5)// "device already allocated"
#define MIX_E_NODRIVER           MAKE_ME(7)// no device driver present
#define MIX_E_BUSY               MAKE_ME(8)// handle being used
#define MIX_E_INVALIDALIAS       MAKE_ME(9)// who knows
#define MIX_E_BADDB              MAKE_ME(10)// bad registry database
#define MIX_E_KEYNOTFOUND        MAKE_ME(11)// registry key not found
#define MIX_E_READERROR          MAKE_ME(12)// registry read error
#define MIX_E_WRITEERROR         MAKE_ME(13)// registry write error
#define MIX_E_DELETEERROR        MAKE_ME(14)// registry delete error
#define MIX_E_NODRIVERCB         MAKE_ME(15)// driver does not call DriverCallback
#define MIX_E_NOSUPPORT          MAKE_ME(16)// driver does not support the requested operation.

#define MIX_E_XMLERR             MAKE_ME(17)// Unknown XML error.
#define MIX_E_NOXML              MAKE_ME(18)// Could not create an XML object for saving/loading.